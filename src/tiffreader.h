
#ifndef _TIFFREADER_H_
#define _TIFFREADER_H_
#include <string>
#include "utils.h"
#include <opencv2/opencv.hpp>



namespace tiff
{

	class TiffObject
	{
	public:

		enum ImageType{Depth8UI,Depth8I,Depth16UI,Depth16I,Depth32I,Depth32UI,Depth32F,Depth64F};
		enum ResizeType
		{
			Nearest = cv::INTER_NEAREST,
			Linear = cv::INTER_LINEAR,
			Cubic = cv::INTER_CUBIC,
			Area = cv::INTER_AREA,
			Max = cv::INTER_MAX,
		};

		TiffObject(const std::string & fileName,int flags);
	/*	TiffObject(const TiffObject &)=delete;
		TiffObject & operator=(const TiffObject &)=delete;
		TiffObject(TiffObject && other)noexcept;
		TiffObject & operator=(TiffObject && other)noexcept;*/

		~TiffObject();

		int Chennels() const;
		bool IsTiled()const;
		bool IsOpened()const;
		void ReadTile();
		int Width()const;
		int Height()const;
		Size2 ImageSize()const;
		void ReadData(uchar* data)const;
		void ReadSubData(const Vec2i & start, const Size2 & size, uchar* data)const;

		void SaveAsImage(const std::string & fileName)const;

		TiffObject Resize(const Size2& size, int type)const;

		TiffObject Resize(double fx, double fy, int type)const;

		TiffObject ROI(const Vec2i & start, const Size2 & size)const;

	private:
		TiffObject();		// delegate constructor
		//Size2 tifSize;
		cv::Mat image;
		int flags;
		bool valid;
	};

}



#endif
