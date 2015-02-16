#pragma once

#include <GLRender/DataTypes.h>

#include <vector>

namespace glr
{
	struct GLRENDERAPI Component
	{
		virtual ~Component() { };
	};

	typedef std::vector<std::shared_ptr<Component>> ComponentVector;
}