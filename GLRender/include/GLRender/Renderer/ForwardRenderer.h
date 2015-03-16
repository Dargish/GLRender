#pragma once

#include <GLRender/Renderer/Renderer.h>
#include <GLRender/Graphics/Shader.h>

namespace glr
{
	class GLRENDERAPI ForwardRenderer : public Renderer
	{
	public:
		ForwardRenderer();

		virtual void draw(World& world, float /*deltaTime*/);

	private:
		Shader m_shader;
	};
}