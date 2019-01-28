

#include "tiffreader.h"
#include <iostream>
#include <cassert>

namespace tiff
{
	TiffReader::TiffReader(const std::string& fileName):TiffReader()
	{
		try
		{
			Init(fileName);
		}
		catch (std::runtime_error & e)
		{
			std::cerr << e.what();

		}
	
	}

	TiffReader::TiffReader(TiffReader&& other)
	{
	}

	TiffReader& TiffReader::operator=(TiffReader&& other)
	{
	}

	TiffReader::~TiffReader()
	{
		if (tifHandler)
		{
			TIFFClose(tifHandler);
			tifHandler = nullptr;
		}
	}

	int TiffReader::ChennelBits() const
	{
		uint16 sample, bits;
		assert(tifHandler);
		TIFFGetField(tifHandler, TIFFTAG_BITSPERSAMPLE, &bits);
		TIFFGetField(tifHandler, TIFFTAG_SAMPLESPERPIXEL, &sample);
		return sample * bits;
	}


	bool TiffReader::IsTiled() const
	{
		assert(tifHandler);
		return TIFFIsTiled(tifHandler);
	}

	void TiffReader::ReadTile()
	{
		assert(TIFFIsTiled(tifHandler));

	}

	int TiffReader::Width() const
	{
		return tifSize.x;
	}

	int TiffReader::Height() const
	{
		return tifSize.y;
	}

	Size2 TiffReader::ImageSize() const
	{
		return tifSize;
	}

	void TiffReader::ReadData(void* data)
	{

	}

	void TiffReader::ReadSubData(const Vec2i& start, const Size2& size, void* data)
	{

	}

	TiffReader::TiffReader():tifHandler(nullptr)
	{
	}

	void TiffReader::Init(const std::string& fileName)
	{
		tifHandler = TIFFOpen(fileName.c_str(), "r");
		if (tifHandler)
			throw std::runtime_error("Tiff image cannot be loaded.\n");

		uint32 h, w;
		TIFFGetField(tifHandler, TIFFTAG_IMAGELENGTH, &h);
		w = TIFFScanlineSize(tifHandler);
		tifSize = Size2{ w,h };
	}
}
