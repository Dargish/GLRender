#pragma once

#include <GLRender/World/World.h>
#include <GLRender/World/Entity.h>

#include <vector>

namespace glr
{
	class GLRENDERAPI System
	{
	public:
		virtual void update(World& world, float deltaTime) = 0;
	};
}