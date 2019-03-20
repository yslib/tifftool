

#include <iostream>
#include "../src/tiffreader.h"

int main()
{

	tifftool::TiffObject image(R"(C:\data\test_02606.tif)",cv::IMREAD_GRAYSCALE);
	std::unique_ptr<uchar[]> buf(new uchar[1984*1984]);
	image.ReadSubData({11216,13019}, {1984,1984}, buf.get());

	return 0;
}
