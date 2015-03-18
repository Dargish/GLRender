#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/Graphics/Window.h>
#include <GLRender/World/World.h>
#include <GLRender/System/System.h>
#include <GLRender/Renderer/Renderer.h>

namespace glr
{
	class GLRENDERAPI Game
	{
	public:
		Game();
		virtual ~Game();

		int run();

		Window& window();
		const Window& window() const;

		long frameTimeLimit() const;
		void setFrameTimeLimit(long frameTimeLimit);

	protected:
		virtual void update(float deltaTime);
		virtual void draw(float deltaTime);

	private:
		Window m_window;

		long m_frameTimeLimit;
	};
}