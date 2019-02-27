
#include "../src/utils.h"
#include "../src/tiff2raw.h"

#include "opencv2/opencv.hpp"


int main(int argc, char ** argv)
{

	tiff::Size3 size;
	tiff::Vec3i start;
	std::string prefix, outputdir;
	int count;
	std::cout << "[prefix(str), count(int), startx(int), starty(int), startz(int), sizex(int), sizey(int), sizez(int), outputdir(str)]\n";
	std::cin >> prefix >> start.x >> start.y >> start.z >> size.x >> size.y >> size.z >> outputdir;
	

	std::vector<std::string> names;
	for (int i = 0; i < size.z; i++)
	{
		std::stringstream ss;
		ss << start.z+i;
		std::string index;
		ss >> index;
		std::string name = prefix + index;
		name += index + ".tif";
		names.push_back(name);
	}

	tiff::Tiff2Raw rawConverter(names, cv::IMREAD_GRAYSCALE);
	rawConverter.SaveAsRaw(outputdir, start,size);

	return 0;
}
