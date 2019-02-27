
#include <iostream>
#include <fstream>
#include <strstream>

#include "tiffreader.h"
#include "tiff2raw.h"


void StatisticSeriesTiffs(const std::vector<std::string> & names)
{
	tiff::Tiff2Raw series(names, cv::IMREAD_GRAYSCALE);

	const auto size = series.DataSize();

	const auto blockSize = tiff::Size3{ 32,32,32 };

	const auto blockDim = tiff::Size3{ size.x / blockSize.x ,size.y/blockSize.y,size.z/blockSize.z};

	int leftTh = 10, rightTh = 255;
	
	const auto totalBlocks = blockDim.x * blockDim.y * blockDim.z;

	
	double ratio = 0.05;


	std::vector<std::vector<std::vector<int>>> tables(blockDim.z, std::vector<std::vector<int>>(blockDim.y, std::vector<int>(blockDim.x)));

	for(int z = 0 ;z<size.z;z++)
	{
		tiff::TiffObject tif(names[z],cv::IMREAD_GRAYSCALE);

		std::unique_ptr<uchar[]> buf(new uchar[size.x*size.y]);

		tif.ReadData(buf.get());

		for (int by = 0; by < blockDim.y; by++)
		{
			for (int bx = 0; bx < blockDim.x; bx++)
			{
				for(int y = 0;y<blockSize.y;y++)
				{
					for(int x = 0;x<blockSize.x;x++)
					{
						const auto linear = tiff::Linear({bx*blockSize.x + x,by*blockSize.y + y}, size.x);
						if(buf[linear] >= leftTh && buf[linear]<=rightTh)
							tables[z / blockSize.z][by][bx]++;
					}
				}
			}
		}
	}


	//
	const auto blockCount = blockSize.x*blockSize.y*blockSize.z *ratio;
	std::size_t validBlocks = 0;
	for (int bz = 0; bz < blockDim.z; bz++) 
	{
		for (int by = 0; by < blockDim.y; by++)
		{
			for (int bx = 0; bx < blockDim.x; bx++)
			{
				if (tables[bz][by][bx] >= blockCount)
					validBlocks++;
			}
		}
	}

	std::cout << validBlocks << " of " << totalBlocks << ":" << 1.0*validBlocks / totalBlocks << std::endl;
}

int main(int argc, char ** argv)
{
	//tiff::TiffObject reader(R"(C:\data\test_07712.tif)",cv::IMREAD_GRAYSCALE);
	//if(reader.IsOpened())
	//{
	//	std::cout <<	"Read Success\n";
	//	std::cout << reader.ImageSize();
	//	const auto image1 = reader.Resize({ 1000,1000 }, tiff::TiffObject::Area);
	//	const auto image2 = reader.Resize(0.01, 0.01, tiff::TiffObject::Area);
	//	//image1.SaveAsImage(R"(D:\\test1.png)");
	//	//image2.SaveAsImage(R"(D:\\test2.png)");
	//	reader.ROI({reader.Width()/4,reader.Height()/4},{3968,3968}).SaveAsImage(R"(D:\\test3.png)");
	//}

	std::vector<std::string> names;
	for(int i = 0 ; i<3968;i++)
	{
		std::stringstream ss;
		ss << i;
		std::string index;
		ss >> index;
		std::string name = R"(H:\14193\z\test_0)";
		name += index + ".tif";
		names.push_back(name);
	}

	tiff::Tiff2Raw rawConverter(names,cv::IMREAD_GRAYSCALE);
	rawConverter.SaveAsRaw(R"(E:\data\mouseneuron\data_set.raw)", tiff::Vec3i( rawConverter.DataSize().x/4,rawConverter.DataSize().y/4,200), {3968,3968,3968 });
	
	return 0;
}




