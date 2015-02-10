#include <GLRender/Graphics/Window.h>

// SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace glr
{
	Window::Window()
	{

	}

	Window::~Window()
	{
		if (m_internal.get() != NULL)
		{
			m_internal->close();
		}
	}

	void Window::create(
		uint width,
		uint height,
		string title /*= "GLRender"*/)
	{
		sf::VideoMode videoMode(width, height);
		sf::ContextSettings contextSettings(24, 8, 4, 4, 5);
		m_internal.reset(new sf::RenderWindow(videoMode, title, sf::Style::Default, contextSettings));
	}

	void Window::show()
	{
		if (m_internal.get() != NULL)
		{
			m_internal->setVisible(true);
		}
	}

	void Window::hide()
	{
		if (m_internal.get() != NULL)
		{
			m_internal->setVisible(false);
		}
	}

	void Window::destroy()
	{
		if (m_internal.get() != NULL)
		{
			m_internal->close();
		}
	}

	void Window::registerCallbacks()
	{
		if (m_internal.get() != NULL)
		{
		}
	}
}