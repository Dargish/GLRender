#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/World/World.h>

namespace glr
{
	class GLRENDERAPI Renderer
	{
	public:
		virtual ~Renderer();

		virtual void draw(World& world, float deltaTime) = 0;
	};
}