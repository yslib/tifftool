
#include "../src/utils.h"
#include "../src/tiff2raw.h"

#include "opencv2/opencv.hpp"

int main(int argc, char ** argv)
{

	tifftool::Size3 size;
	tifftool::Vec3i start;
	std::string prefix, outputdir;
	int count,offset;
	std::cout << "[prefix(str), startx(int), starty(int), startz(int), sizex(int), sizey(int), sizez(int), offset(int) ,layers(int),outputdir(str),]\n";
	std::cin >> prefix >> start.x >> start.y >> start.z >> size.x >> size.y >> size.z >>offset>> count>>outputdir;
	std::vector<std::string> names;

	for (int i=0;i<count;i++) 
	{
		std::stringstream ss;
		ss << std::setw(5)<<std::setfill('0')<<i + offset;
		std::string index;
		ss >> index;
		std::string name = prefix + index +".tif";
		names.push_back(name);
		std::cout << name << std::endl;
	}
	
	tifftool::Tiff2Raw rawConverter(names, cv::IMREAD_GRAYSCALE);
	rawConverter.SaveAsRaw(outputdir, start,size);
	return 0;
}
