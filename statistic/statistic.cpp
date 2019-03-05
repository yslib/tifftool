#include "omp.h"
#include "../src/utils.h"
#include "../src/tiff2raw.h"

#include "opencv2/opencv.hpp"
#include "../src/tiffreader.h"

#include <fstream>


int sum = 0;


void StatisticSeriesTiffs(const std::vector<std::string> & names, double ratio, int leftTh, int rightTh, const tifftool::Size3 & blockSize)
{
	//int n = omp_get_num_threads();
	//omp_set_num_threads(5);

	//tiff::Tiff2Raw series(names, cv::IMREAD_GRAYSCALE);

	//const auto size = series.DataSize();
	const auto size = tifftool::Size3{28452,21866,4834};


	std::cout << "DataSize:" << size << std::endl;

	const auto blockDim = tifftool::Size3{ size.x / blockSize.x ,size.y / blockSize.y,size.z / blockSize.z };

	const auto totalBlocks = blockDim.x * blockDim.y * blockDim.z;

	const auto blockCount = blockSize.x*blockSize.y*blockSize.z *ratio;
	const int bins = 256;

	std::vector<std::vector<std::vector<std::vector<std::size_t>>>> tables(blockDim.z, std::vector<std::vector<std::vector<std::size_t>>>(blockDim.y, std::vector<std::vector<std::size_t>>(blockDim.x,std::vector<std::size_t>(bins))));
	
	//std::ofstream res(R"(rrrrrrrrrrrr.csv)");

	const auto slice = size.z / blockSize.z * blockSize.z;

	//for (int z = 0; z < slice; z++)
	//{
	//	tiff::TiffObject tif(names[z], cv::IMREAD_GRAYSCALE);
	//	std::unique_ptr<uchar[]> buf(new uchar[size.x*size.y]);
	//	tif.ReadData(buf.get());
	//	std::cout << " Counting " << names[z] << std::endl;

	//	for (int by = 0; by < blockDim.y; by++)
	//	{
	//		for (int bx = 0; bx < blockDim.x; bx++)
	//		{
	//			for (int y = 0; y < blockSize.y; y++)
	//			{
	//				for (int x = 0; x < blockSize.x; x++)
	//				{
	//					const auto linear = tiff::Linear(tiff::Vec2i(bx*blockSize.x + x, by*blockSize.y + y), size.x);
	//					//if (buf[linear] >= leftTh && buf[linear] <= rightTh)
	//					tables[z / blockSize.z][by][bx][buf[linear]]++;
	//				}
	//			}
	//		}
	//	}

	//	if(z%blockSize.z==0 && z)
	//	{
	//		int zCount = z / blockSize.z;

	//		std::stringstream ss;
	//		ss << zCount;
	//		std::string index;
	//		ss >> index;
	//		std::string fileName = "intermediateresult_" + index + ".txt";
	//		std::ofstream res(fileName);

	//		for(int d = 0 ;d<zCount;d++)
	//		{
	//			for (int by = 0; by < blockDim.y; by++)
	//			{
	//				for (int bx = 0; bx < blockDim.x; bx++)
	//				{
	//					for (int b = 0; b < bins; b++)
	//						res << tables[d][by][bx][b] << ",";
	//					std::cout << std::endl;
	//				}
	//			}
	//		}

	//	}
	//	
	//}

	FILE * f = freopen(R"(D:\intermediateresult.txt)", "r", stdin);
	//std::ofstream binfile("statistic_result", std::ostream::binary);
	std::cout << "Total of zb:" << blockDim.z << std::endl;
	for (int zb = 0; zb < blockDim.z; zb++)
	{
		for (int by = 0; by < blockDim.y; by++)
		{
			for (int bx = 0; bx < blockDim.x; bx++)
			{
				for (int b = 0; b < bins; b++)
				{
					int n;
					scanf("%d,", &tables[zb][by][bx][b]);
				}
				//binfile.write((const char*)tables[zb][by][bx].data(), sizeof(std::size_t)*bins);
			}
		}
		std::cout << "zb:" << zb << std::endl;
	}
	std::cout << "Read finished\n";

	fclose(f);


	int arr[10] = { 10,20,30,40,50,60,70,80,90,100 };
	for(int k = 0;k<10;k++)
	{
		std::size_t validBlocks = 0;
		for (int zb = 0; zb < blockDim.z; zb++)
		{
			for (int by = 0; by < blockDim.y; by++)
			{
				for (int bx = 0; bx < blockDim.x; bx++)
				{
					int s = arr[k];
					std::size_t count = 0;
					for (int b = s; b < bins; b++)
					{
						count += tables[zb][by][bx][b];
					}

					if (count > 0)
						validBlocks++;

					//binfile.write((const char*)tables[zb][by][bx].data(), sizeof(std::size_t)*bins);
				}
			}
			//std::cout << "zb:" << zb << std::endl;
		}
		std::cout << arr[k] << " " << 1.0*validBlocks / totalBlocks << std::endl;
	}

	
	



/*	const auto totalVoxels = size.x*size.y*size.z;
	for (int b = 0; b < bins; b++)
	{
		res << histogram[b] << "\t";
		std::cout << histogram[b] << "\t";
	}
	res << std::endl;
	std::cout << std::endl;

	for (int b = 0; b < bins; b++)
	{
		res << 1.0* histogram[b] / totalVoxels << "\t";
		std::cout << 1.0*histogram[b] / totalVoxels << "\t";
	}
	res << std::endl;
	std::cout << std::endl*/;

	//std::cout << validBlocks << " of " << totalBlocks << ":" << 1.0 * validBlocks / totalBlocks << std::endl;
	//std::ofstream ofs(R"(countingresult.txt)");
	//ofs << validBlocks << " of " << totalBlocks << ":" << 1.0 * validBlocks / totalBlocks << std::endl;
}


int main(int argc, char ** argv)
{

	std::string prefix;
	int count, minTh, maxTh;
	tifftool::Size3 size = {128,128,128};
	double ratio;

	//std::cout << "[prefix(str), count(int), ratio(double), sizex(int), sizey(int), sizez(int), minvalue(int), maxvalue(int)]\n";
	//std::cin >> prefix >> count >> ratio >> size.x >> size.y >> size.z >> minTh >> maxTh;

	//std::cout << prefix << " " << count << " " << ratio << " " << size << " " << minTh << " " << maxTh << std::endl;

	std::vector<std::string> names;

	//for (int i = 1; i <= count; i++)
	//{
	//	std::stringstream ss;
	//	ss << std::setw(5) << std::setfill('0') << i;
	//	std::string index;
	//	ss >> index;
	//	std::string name = prefix + index + ".tif";
	//	names.push_back(name);
	//}


	StatisticSeriesTiffs(names, ratio, minTh, maxTh, size);


	//tiff::TiffObject image(R"(C:\data\test_07712.tif)", cv::IMREAD_GRAYSCALE);

	//const auto bytes = image.ImageSize().x * image.ImageSize().y;
	//std::unique_ptr<uchar[]> buf(new uchar[bytes]);

	//image.ReadData(buf.get());
	//std::vector<std::size_t> hist(256);
	//for (int i = 0; i < bytes; i++)
	//	hist[buf[i]]++;

	//for (int i = 0; i < 256; i++)
	//	std::cout << i << ":" << hist[i] << std::endl;



	system("pause");


	return 0;
}
