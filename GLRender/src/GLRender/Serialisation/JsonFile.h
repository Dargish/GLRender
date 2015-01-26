#pragma once

#include <GLRender/DataTypes.h>

#include <json/json.h>

namespace glrender
{
namespace serialisation
{
	class JsonFile
	{
	public:
		static Json::Value Load(const string& filePath);
		static void Save(const string& filePath, const Json::Value& data);
	};
}
}
