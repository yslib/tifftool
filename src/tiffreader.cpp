

#include "tiffreader.h"
#include <iostream>
#include <cassert>



namespace tiff
{
	TiffObject::TiffObject(const std::string& fileName, int flags) :flags(flags)
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
		//const auto channels = image.channels();
		//const auto subWidth= std::min(size.x,std::size_t(image.cols - start.x)) * channels;

		////const auto subBegin = std::min(start.x, image.cols)*channels;

		//const auto scanLine = image.channels()*size.x;
		//for (auto i = 0; i < image.rows; i++)
		//	memcpy((uchar*)data + scanLine*i, image.ptr<uchar>(i) + channels * start.x, subWidth);
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
