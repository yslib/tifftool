

#include "tiffreader.h"
#include <iostream>
#include <cassert>

#include "tiffio.h"

namespace tifftool
{
	TiffObject::TiffObject(const std::string& fileName, int flags) :flags(flags),fileName(fileName)
	{
		image = cv::imread(fileName, flags);
		valid = !image.empty();
	}
	//TiffObject::TiffObject(TiffObject&& other)noexcept
	//{
	//	image = std::move(other.image);
	//	ImageSize() = other.ImageSize();
	//}

	//TiffObject& TiffObject::operator=(TiffObject&& other)noexcept
	//{
	//	if (this != &other)
	//	{
	//		image = std::move(other.image);
	//		ImageSize() = other.ImageSize();
	//	}
	//	return *this;
	//}


	TiffObject::~TiffObject()
	{

	}
	int TiffObject::Chennels() const
	{
		return image.channels();
	}

	bool TiffObject::IsTiled() const
	{
		return false;
	}

	bool TiffObject::IsOpened() const
	{
		return valid;
	}

	void TiffObject::ReadTile()
	{
		std::cout << "The function is empty so far.\n";
	}
	int TiffObject::Width() const
	{
		return image.size().width;
	}

	int TiffObject::Height() const
	{
		return image.size().height;
	}

	Size2 TiffObject::ImageSize() const
	{
		return { (std::size_t)Width(),(std::size_t)Height() };
	}

	void TiffObject::ReadData(uchar* data)const
	{
		if (image.isContinuous())
		{
			memcpy(data, image.datastart, image.dataend - image.datastart);
		}
		else
		{
			const auto scanLine = image.cols * image.channels();
			for (auto i = 0; i < image.rows; i++)
			{
				memcpy(data + scanLine * i, image.ptr<uchar>(i), scanLine);
			}
		}
	}

	void TiffObject::ReadSubData(const Vec2i& start, const Size2& size, uchar* data)const
	{
		if (start.x >= Width() || start.y >= Height())
			return;

		if(size.x * size.y != 0)
		{
			const auto tiff = ROI(start, size);
			tiff.ReadData(data);
		}else
		{
			const auto tiff = ROI(start, Size2(Width()-start.x,Height()-start.y));
			tiff.ReadData(data);
		}


		//TIFF * tif = TIFFOpen(fileName.c_str(),"r");
		//int imageWidth, imageLength,imageRowsPerStrip;
		//TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &imageWidth);
		//TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imageLength);
		//TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &imageRowsPerStrip);
		//long long stripSize = TIFFStripSize(tif);
		//long long stripsNumber = TIFFNumberOfStrips(tif);
		//std::cout << imageWidth << " " << imageLength << " " << imageRowsPerStrip << " " << stripSize << " " << stripsNumber << std::endl;
		////1. find the row range from start to end
		//int realStartRow = 0, realEndRow = 0;
		//realStartRow = start.y;
		//realEndRow = start.y + size.y;

		//const int realStripStart = realStartRow / imageRowsPerStrip;
		//const int realStripEnd = realEndRow / imageRowsPerStrip;

		//const int startStripRow = realStartRow % imageRowsPerStrip;
		//const int endStripRow = realEndRow % imageRowsPerStrip;

		////if (buf) {
		////	free(buf);
		////}

		//int localStartRow = 0, localEndRow = 0;

		//int curIndex = 0;
		//std::unique_ptr<unsigned char[]> buf (new unsigned char[stripSize]);

		//for (int strip = realStripStart; strip < realStripEnd; strip++) {
		//	
		//	TIFFReadEncodedStrip(tif, strip, buf.get(), (tsize_t)-1);

		//	if (strip == realStripStart) 
		//	{
		//		localStartRow = startStripRow;
		//	}
		//	else
		//	{
		//		localStartRow = 0;
		//	}
		//	if (strip == realStripEnd - 1) 
		//	{
		//		localEndRow = endStripRow;
		//	}
		//	else 
		//	{
		//		localEndRow = imageRowsPerStrip - 1;
		//	}
		//	for (int i = localStartRow; i < localEndRow && curIndex < size.y; i++) 
		//	{
		//		for (int j = 0; j < size.x; j++) 
		//		{
		//			data[curIndex*size.x + j] = (buf[3 * (i*imageWidth + (int)(start.x) + j)] & 0xff);
		//			//data[curIndex*size.x + j] += (buf[3 * (i*imageWidth + (int)(start.x) + j) + 1] & 0xff) << 8;
		//			//data[curIndex*size.x + j] += (buf[3 * (i*imageWidth + (int)(start.x) + j) + 2] & 0xff) << 16;
		//		}
		//		curIndex++;
		//	}
		//}
		//TIFFClose(tif);
	}

	void TiffObject::SaveAsImage(const std::string& fileName)const
	{
		cv::imwrite(cv::String(fileName), image);
	}

	TiffObject TiffObject::Resize(const Size2& size, int type)const
	{
		auto newImage(*this);
		cv::resize(image, newImage.image,cv::Size(size.x,size.y),0.0,0.0, type);
		return newImage;
	}

	TiffObject TiffObject::Resize(double fx, double fy, int type)const
	{
		auto newImage(*this);
		cv::resize(image, newImage.image, cv::Size(), fx,fy, type);
		return newImage;
	}

	TiffObject TiffObject::ROI(const Vec2i& start, const Size2& size)const
	{
		auto newImage(*this);
		newImage.image = cv::Mat(image, cv::Rect(start.x,start.y,size.x,size.y));
		return newImage;
	}

	TiffObject::TiffObject():flags(-1),valid(false)
	{

	}
}
