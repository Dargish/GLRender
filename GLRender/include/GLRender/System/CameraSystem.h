#pragma once

#include <GLRender/System/System.h>

namespace glr
{
	class GLRENDERAPI CameraSystem
	{
		virtual void update(World& world, float deltaTime);
	};
}