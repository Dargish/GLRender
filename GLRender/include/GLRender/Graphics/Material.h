#pragma once

#include <GLRender/DataTypes.h>

namespace glr
{
	class GLRENDERAPI Material
	{
	public:
		Material();
		Material(const string& path);

		void load(const string& path);
	};
}