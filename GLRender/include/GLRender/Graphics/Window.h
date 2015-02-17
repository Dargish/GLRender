#pragma once

#include <GLRender\DataTypes.h>

namespace sf
{
	class RenderWindow;
}

namespace glr
{
	class GLRENDERAPI Window
	{
	public:

		Window();
		virtual ~Window();

		void create(uint width, uint height, string title = "GLRender");
		void create(WindowHandle handle);

		bool isOpen() const;
		void show();
		void hide();
		void destroy();

		void pollEvents();

	private:
		std::unique_ptr<sf::RenderWindow> m_internal;
	};
}