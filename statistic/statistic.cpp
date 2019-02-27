
#include "../src/utils.h"
#include "../src/tiff2raw.h"

#include "opencv2/opencv.hpp"
#include "../src/tiffreader.h"


void StatisticSeriesTiffs(const std::vector<std::string> & names, double ratio, int leftTh, int rightTh, const tiff::Size3 & blockSize)
{
	tiff::Tiff2Raw series(names, cv::IMREAD_GRAYSCALE);

	const auto size = series.DataSize();

	const auto blockDim = tiff::Size3{ size.x / blockSize.x ,size.y / blockSize.y,size.z / blockSize.z };

	const auto totalBlocks = blockDim.x * blockDim.y * blockDim.z;

	std::vector<std::vector<std::vector<int>>> tables(blockDim.z, std::vector<std::vector<int>>(blockDim.y, std::vector<int>(blockDim.x)));
#pragma parallel for
	for (int z = 0; z < size.z; z++)
	{
		tiff::TiffObject tif(names[z], cv::IMREAD_GRAYSCALE);

		std::unique_ptr<uchar[]> buf(new uchar[size.x*size.y]);

		tif.ReadData(buf.get());

		for (int by = 0; by < blockDim.y; by++)
		{
			for (int bx = 0; bx < blockDim.x; bx++)
			{
				for (int y = 0; y < blockSize.y; y++)
				{
					for (int x = 0; x < blockSize.x; x++)
					{
						const auto linear = tiff::Linear(tiff::Vec2i( bx*blockSize.x + x,by*blockSize.y + y ), size.x);
						if (buf[linear] >= leftTh && buf[linear] <= rightTh)
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

	std::string prefix;
	int count,minTh,maxTh;
	tiff::Size3 size;
	double ratio;

	std::cout << "[prefix(str), count(int), ratio(double), sizex(int), sizey(int), sizez(int), minvalue(int), maxvalue(int)]\n";
	std::cin >> prefix >> count >> ratio >> size.x >> size.y >> size.z >> minTh >> maxTh;

	std::vector<std::string> names;
	for (int i = 0; i < count; i++)
	{
		std::stringstream ss;
		ss << i;
		std::string index;
		ss >> index;
		std::string name = prefix + index;
		name += index + ".tif";
		names.push_back(name);
	}
	StatisticSeriesTiffs(names, ratio, minTh, maxTh, size);
	return 0;
}
