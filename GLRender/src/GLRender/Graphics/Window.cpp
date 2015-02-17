#include <GLRender/Graphics/Window.h>

// SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Glew
#include <GL/glew.h>

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

	void Window::create(uint width, uint height, string title /*= "GLRender"*/)
	{
		sf::VideoMode videoMode(width, height);
		sf::ContextSettings contextSettings(32, 0, 4, 4, 5);
		m_internal.reset(new sf::RenderWindow(videoMode, title, sf::Style::Default, contextSettings));
	}

	void Window::create(WindowHandle handle)
	{
		sf::WindowHandle wHandle = (sf::WindowHandle)handle;
		sf::ContextSettings contextSettings(32, 0, 4, 4, 5);
		m_internal.reset(new sf::RenderWindow(wHandle, contextSettings));
	}

	bool Window::isOpen() const
	{
		if (m_internal.get() != NULL)
		{
			return m_internal->isOpen();
		}
		return false;
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

	void Window::pollEvents()
	{
		if (m_internal.get() != NULL)
		{
			sf::Event event;
			while (m_internal->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					destroy();
				}
				else if (event.type == sf::Event::Resized)
				{
					// adjust the viewport when the window is resized
					glViewport(0, 0, event.size.width, event.size.height);
					//world->camera()->updateProjectionMatrix(event.size.width, event.size.height);
				}
			}
		}
	}
}