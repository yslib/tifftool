
#ifndef _TIFFREADER_H_
#define _TIFFREADER_H_
#include <string>
#include "utils.h"

#include "tiffio.h"

namespace tiff
{

	class TiffReader
	{
	public:
		TiffReader(const std::string & fileName);
		TiffReader(const TiffReader &)=delete;
		TiffReader & operator=(const TiffReader &)=delete;
		TiffReader(TiffReader && other);
		TiffReader & operator=(TiffReader && other);
		~TiffReader();

		int ChennelBits()const;
		bool IsTiled()const;
		void ReadTile();
		int Width()const;
		int Height()const;
		Size2 ImageSize()const;
		void ReadData(void * data);
		void ReadSubData(const Vec2i & start,const Size2 & size,void * data);

	private:
		TiffReader();		// delegate constructor
		void Init(const std::string & fileName);
		TIFF * tifHandler;
		Size2 tifSize;
		std::unique_ptr<void*> buf;
	};

}



#endif
