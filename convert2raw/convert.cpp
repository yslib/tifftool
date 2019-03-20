
#include "../src/utils.h"
#include "../src/tiff2raw.h"
#include "opencv2/opencv.hpp"

int main(int argc, char ** argv)
{
	std::string prefix, outputdir,outprefix;
	int count, offset;
	std::cout << "[prefix(str),offset(int) ,layers(int),outputdir(str), outputfilenameprefix]\n";
	std::cin >> prefix >> offset >> count >> outputdir >> outprefix;
	std::vector<std::string> names;

	for (int i = 0; i < count; i++)
	{
		std::stringstream ss;
		ss << std::setw(5) << std::setfill('0') << i + offset;
		std::string index;
		ss >> index;
		std::string name = prefix + index + ".tif";
		names.push_back(name);
		//std::cout << name << std::endl;
	}

	tifftool::Tiff2Raw rawConverter(names, cv::IMREAD_GRAYSCALE);
	const auto sze = rawConverter.DataSize();

	const auto slices = 256;
	int leftSlices = sze.z;
	int patches = std::ceil(1.0*sze.z/slices);
	int left = 0;
	for(int i = 0 ; i < patches;i++)
	{
		std::stringstream ss;
		ss << i;
		std::string index;
		ss >> index;

		auto s = 0;
		if (leftSlices > slices)
			s = slices;
		else
			s = leftSlices % slices;
		std::cout << "Convert from:" << i * slices << " to " << (i + 1)*slices << std::endl;
		std::cout << "Patch:" << i << " Start At:" << tifftool::Vec3i(i*slices, 0, 0) << ", Size:" << tifftool::Size3(sze.x, sze.y, s) << " " << outputdir + outprefix + "_" + index + ".raw" << std::endl;
		rawConverter.SaveAsRaw(outputdir+outprefix+"_" + index + ".raw",tifftool::Vec3i(i*slices,0,0),tifftool::Size3(sze.x,sze.y,s));
		leftSlices -= slices;
		// Debug
	}
	return 0;
}
