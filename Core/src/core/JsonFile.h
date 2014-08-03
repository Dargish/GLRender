#pragma once
#include "fwd.h"
#include <json/json.h>

namespace core
{
	class JsonFile
	{
	public:
		static Json::Value Load(const std::string& filePath);
		static void Save(const std::string& filePath, const Json::Value& data);
	};
}

