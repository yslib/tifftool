
#include "tiff2raw.h"
#include "tiffreader.h"
#include <fstream>

tifftool::Tiff2Raw::Tiff2Raw(const std::vector<std::string>& fileNames, int flags):tiffFileNames(fileNames),flags(flags)
{
	if(fileNames.size())
	{
		TiffObject reader(fileNames[0],flags);
		const auto s = reader.ImageSize();
		size = { s.x,s.y,fileNames.size() };
		channels = reader.Chennels();
	}
}

void tifftool::Tiff2Raw::ReadData(void * data)
{
	const auto s = size.x*size.y*channels;
	
	for(int i =0;i < tiffFileNames.size();i++)
	{
		TiffObject reader(tiffFileNames[i], flags);
		reader.ReadData(((uchar*)(data) + i * s));
	}
}

void tifftool::Tiff2Raw::ReadSubData(const Vec3i& start, const Size3 & size, void* data)
{
	auto s = size.x*size.y*channels;
	if (s == 0)
		s = this->size.x * this->size.y*channels;


	for (int i = start.z; i < tiffFileNames.size() && i-start.z< size.z; i++)
	{
		TiffObject reader(tiffFileNames[i], flags);
		if(reader.IsOpened() == false)
		{
			std::cout << tiffFileNames[i] << " can not be opened\n";
			continue;
		}
		reader.ReadSubData({ start.x,start.y }, {size.x,size.y}, ((uchar*)(data) + (i-start.z) * s));
		std::cout << tiffFileNames[i] << " has been read\n";
	}
}


void tifftool::Tiff2Raw::SaveAsRaw(const std::string& fileName, const Vec3i& start, const Size3& size)
{
	std::ofstream of(fileName, std::ofstream::binary);
	if(of.is_open())
	{
		auto sliceBytes = size.x * size.y * channels;

		//auto s = size.x * size.y * size.z * channels;
		constexpr std::size_t sliceCount = 5;

	//	std::cout << "Bytes:" << s << std::endl;
	//	if(s == 0)
	//		s = tiffFileNames.size() * this->size.x*this->size.y;

		std::unique_ptr<uchar> buf(new uchar[sliceBytes*sliceCount]);

		for(int i = 0 ; i<size.z;i+=sliceCount)
		{
			std::size_t slice;
			if(i + sliceCount >= size.z)
				slice = size.z - i;
			else
				slice = sliceCount;
			const auto subStart = Vec3i(start.x, start.y, start.z + i);
			const auto subSize = Size3(size.x,size.y,slice);
			ReadSubData(subStart,subSize, buf.get());
			of.write(reinterpret_cast<const char*>(buf.get()), sliceBytes*slice);
			std::cout << sliceBytes * slice << std::endl;
			std::cout << "Writing Substart:" << subStart << " subSize:" << subSize << " finished" << std::endl;
		}

	}
}

tifftool::Size3 tifftool::Tiff2Raw::DataSize() const
{
	return size;
}
