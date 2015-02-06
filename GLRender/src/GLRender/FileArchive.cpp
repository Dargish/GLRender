#include <GLRender/FileArchive.h>

namespace glr
{
	FileOArchive::FileOArchive(const string& filePath) :
		m_fs(filePath.c_str()), archive(m_fs)
	{

	}


	FileIArchive::FileIArchive(const string& filePath) :
		m_fs(filePath.c_str()), archive(m_fs)
	{

	}
}