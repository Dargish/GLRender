#pragma once

#include <GLRender/System/System.h>

namespace glr
{
	class GLRENDERAPI ControlSystem
	{
		virtual void update(World& world, float deltaTime);
	};
}