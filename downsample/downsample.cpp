#include "../src/utils.h"
#include "opencv2/opencv.hpp"
#include "../src/tiffreader.h"

int main(int argc, char ** argv)
{

	//std::string prefix;
	//int count, minTh, maxTh;

	//tiff::Size3 size;
	//double ratio;

	//std::cout << "[prefix(str), count(int), ratio(double), sizex(int), sizey(int), sizez(int), minvalue(int), maxvalue(int)]\n";
	//std::cin >> prefix >> count >> ratio >> size.x >> size.y >> size.z >> minTh >> maxTh;


	tifftool::TiffObject image(R"(C:\data\test_02606.tif)",cv::IMREAD_GRAYSCALE);
	 image.ROI({ 11216,13019 }, { 2048,2048 }).SaveAsImage(R"(D:\sub_02606.png)");

	return 0;
}
