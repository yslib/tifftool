
#ifndef _TIFF2RAW_H_
#define _TIFF2RAW_H_

#include  <vector>
#include "utils.h"

namespace tifftool
{
	class Tiff2Raw
	{
	public:
		Tiff2Raw(const std::vector<std::string> & fileNames, int flags);
		void ReadData(void * data);
		void ReadSubData(const Vec3i & start, const Size3 & size, void * data);
		void SaveAsRaw(const std::string & fileName, const Vec3i & start = {0,0,0}, const Size3 & size = {0,0,0});
		Size3 DataSize()const;

	private:
		std::vector<std::string> tiffFileNames;
		Size3 size;
		int channels;
		int flags;
	};



}


#endif