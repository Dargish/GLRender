#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/Graphics/Window.h>
#include <GLRender/World/World.h>

namespace glr
{
	class GLRENDERAPI Game
	{
	public:
		World& world();
		const World& world() const;

		Window& showWindow(uint width, uint height, string title = "GLRender");
		Window& showWindow(WindowHandle handle);

		Window& window();
		const Window& window() const;

		template<class T>
		std::shared_ptr<T> addSystem()
		{
			return std::shared_ptr<T>(new T);
		}

	private:
		World m_world;
		Window m_window;
	};
}