#pragma once

#include <GLRender/System/System.h>

namespace glr
{
	class GLRENDERAPI CameraSystem : public System
	{
	public:
		virtual void update(World& world, float deltaTime);
	};
}