#pragma once

#include <GLRender/DataTypes.h>

// STL
#include <fstream>

// BOOST
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace boost
{
	namespace serialization
	{
		class access;
	}
}

namespace glr
{
	class GLRENDERAPI FileOArchive
	{
	public:
		FileOArchive(const string& filePath);
	private:
		std::ofstream m_fs;
	public:
		boost::archive::text_oarchive archive;
	};

	class GLRENDERAPI FileIArchive
	{
	public:
		FileIArchive(const string& filePath);
	private:
		std::ifstream m_fs;
	public:
		boost::archive::text_iarchive archive;
	};
}