#include "Window.h"

Window_Ptr Window::s_instance;

Window_Ptr Window::Instance()
{
	if (!s_instance.get())
	{
		s_instance.reset(new Window);
	}
	return s_instance;
}

Window::Window()
{
}

Window::~Window()
{
}

void Window::init(sf::VideoMode mode, const std::string& title, sf::Uint32 style, const sf::ContextSettings& settings)
{
	m_window.reset( new sf::RenderWindow(mode, title, style, settings));
}

sf::RenderWindow_Ptr& Window::getWindow()
{
	return m_window;
}

void Window::Init(sf::VideoMode mode, const std::string& title, sf::Uint32 style, const sf::ContextSettings& settings)
{
	Instance()->init(mode, title, style, settings);
}

sf::RenderWindow_Ptr& Window::GetWindow()
{
	return Instance()->getWindow();
}