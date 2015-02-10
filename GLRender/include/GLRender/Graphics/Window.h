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

		void create(
			uint width,
			uint height,
			string title = "GLRender");

		void show();
		void hide();
		void destroy();

		void registerCallbacks();

	private:
		std::unique_ptr<sf::RenderWindow> m_internal;
	};
}