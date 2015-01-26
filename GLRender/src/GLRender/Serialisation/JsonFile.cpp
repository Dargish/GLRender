#include "JsonFile.h"
#include <fstream>

namespace glrender
{
namespace serialisation
{
		Json::Value JsonFile::Load(const std::string& filePath)
	{
		Json::Value data;
		Json::Reader reader;
		std::ifstream myfile(filePath);
		if (myfile.is_open())
		{
			std::string fileString;
			std::string line;
			while (std::getline(myfile, line))
			{
				fileString += line;
			}
			myfile.close();
			if (reader.parse(fileString, data))
			{
				return data;
			}
			else
			{
				std::cerr << "Error loading file" << std::endl;
			}
		}
		else
		{
			std::cerr << "Couldn't open file " << filePath << std::endl;
		}
	}

	void JsonFile::Save(const std::string& filePath, const Json::Value& data)
	{
		Json::StyledWriter writer;
		std::ofstream myfile;
		myfile.open(filePath);
		myfile << writer.write(data);
		myfile.close();
	}
}
}
