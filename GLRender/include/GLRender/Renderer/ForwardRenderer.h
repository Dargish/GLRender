#pragma once

#include <GLRender/Renderer/Renderer.h>

namespace glr
{
	class GLRENDERAPI ForwardRenderer : public Renderer
	{
	public:
		virtual void draw(World& world, float deltaTime);
	};
}