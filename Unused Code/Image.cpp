#include "Image.h"
#include <png.h>
#include <fstream>

#define PNGSIGSIZE 8

namespace graphics
{
	Image::Image()
	{

	}

	Image::Image(const std::string& filePath) :
		m_filePath(filePath)
	{

	}

	Image::~Image()
	{
	}

	bool Image::open()
	{
		if (m_filePath.empty())
		{
			return false;
		}
		std::ifstream file;
		file.open(m_filePath, std::ifstream::in | std::ifstream::binary);
		if (!file.is_open())
		{
			return false;
		}
		png_byte pngsig[PNGSIGSIZE];
		file.read((char*)pngsig, PNGSIGSIZE);

		if (!png_sig_cmp(pngsig, 0, PNGSIGSIZE))
		{
			return false;
		}

		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr)
		{
			return false;
		}

		png_infop info_ptr = png_create_info_struct(png_ptr);

		if (!info_ptr)
		{
			return false;
		}

		file.close();
		return true;
	}

	bool Image::open(const std::string& filePath)
	{
		m_filePath = filePath;
		return open();
	}
}