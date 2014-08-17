#pragma once
#include "fwd.h"
namespace graphics
{
	class Image
	{
	public:
		Image();
		Image(const std::string& filePath);
		~Image();

		bool open();
		bool open(const std::string& filePath);

	private:
		std::string m_filePath;
	};
}
