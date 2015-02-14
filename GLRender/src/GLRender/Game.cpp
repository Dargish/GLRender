#include <GLRender/Game.h>

namespace glr
{
	World& Game::world()
	{
		return m_world;
	}

	const World& Game::world() const
	{
		return m_world;
	}

	Window& Game::showWindow(uint width, uint height, string title /*= "GLRender"*/)
	{
		m_window.create(width, height, title);
		return m_window;
	}

	Window& Game::showWindow(WindowHandle handle)
	{
		m_window.create(handle);
		return m_window;
	}

	Window& Game::window()
	{
		return m_window;
	}

	const Window& Game::window() const
	{
		return m_window;
	}
}