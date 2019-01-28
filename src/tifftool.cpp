
#include "tiffio.h"
#include <iostream>
#include <fstream>
#include <strstream>

int main(int argc, char ** argv)
{
	//TIFF* tif = TIFFOpen(argv[1], "r");

	TIFF* tif = TIFFOpen(R"(C:\data\test_02606.tif)", "r");

	if (tif) {
		uint32 imageHeight,imageWidth;
		tdata_t buf;
		uint32 row;

		uint16 bps,imageCompression,imagePhotoMetric,
		imageSamplePerPixel,ResolutUnit,
		imagePlanarConfig, Orientation;
		uint32 imageRowsPerStrip;

		float X_Resolut, Y_Resolut;





		TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &imageWidth);
		TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imageHeight);
		//std::cout << "Image width and length" << imageWidth << imageLength;
		TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);
		TIFFGetField(tif, TIFFTAG_COMPRESSION, &imageCompression);
		TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &imagePhotoMetric);

		TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &imageSamplePerPixel);
		TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &imageRowsPerStrip);
		if (imageRowsPerStrip != 1)
		{
			std::cout<< "Rows Each Strip Is Not 1!";
			//return;
		}

		TIFFGetField(tif, TIFFTAG_XRESOLUTION, &X_Resolut);
		TIFFGetField(tif, TIFFTAG_YRESOLUTION, &Y_Resolut);
		TIFFGetField(tif, TIFFTAG_RESOLUTIONUNIT, &ResolutUnit);

		TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &imagePlanarConfig);
		TIFFGetField(tif, TIFFTAG_ORIENTATION, &Orientation);

		std::cout << "Image width and length: " << imageWidth << " " << imageWidth << std::endl;
		std::cout << "bps: " << bps << std::endl;
		std::cout << "imageCompression: " << imageCompression << std::endl;
		std::cout << "imagePhotoMetric: " << imagePhotoMetric << std::endl;
		std::cout << "imageSamplePerPixel: " << imageSamplePerPixel << std::endl;
		std::cout << "imageRowsPerStrip: " << imageRowsPerStrip << std::endl;
		std::cout << "X_Resolut: " << X_Resolut << std::endl;
		std::cout << "Y_Resolut: " << Y_Resolut << std::endl;
		std::cout << "ResolutUnit: " << ResolutUnit << std::endl;
		std::cout << "imagePlanarConfig: " << imagePlanarConfig << std::endl;
		std::cout << "Orientation: " << Orientation << std::endl;


		buf = _TIFFmalloc(TIFFScanlineSize(tif));
		for (row = 0; row < imageHeight; row++)
			TIFFReadScanline(tif, buf, row);
		_TIFFfree(buf);
		TIFFClose(tif);
	}

	std::ifstream fileIn("");
	std::strstream::pos_type a;

	system("pause");

	return 0;
}
