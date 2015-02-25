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

		int run();

		World& world();
		const World& world() const;

		Window& showWindow(uint width, uint height, string title = "GLRender");
		Window& showWindow(WindowHandle handle);

		Window& window();
		const Window& window() const;

		template<class T>
		std::shared_ptr<T> addSystem()
		{
			std::shared_ptr<T> ptr(new T);
			m_systems.push_back(ptr);
			return ptr;
		}

		template<class T>
		std::shared_ptr<T> setRenderer()
		{
			m_renderer.reset(new T);
			return std::dynamic_pointer_cast<T>(m_renderer);
		}

		long frameTimeLimit() const;
		void setFrameTimeLimit(long frameTimeLimit);

	private:
		void update(float deltaTime);
		void draw(float deltaTime);

		void initGlew();
		bool m_glewInitted;

		typedef std::vector<std::shared_ptr<System>> SystemVector;
		SystemVector m_systems;

		std::shared_ptr<Renderer> m_renderer;

		World m_world;
		Window m_window;

		long m_frameTimeLimit;
	};
}