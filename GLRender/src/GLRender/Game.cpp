#include <GLRender/Game.h>

namespace glr
{
	Game::Game()
	{

	}

	Game::~Game()
	{

	}

	void Game::createWindow(Window& window, uint width, uint height, string title /*= "GLRender"*/)
	{
		window.create(width, height, title);
		registerWindow(window);
	}

	void Game::registerWindow(Window& window)
	{
		// Todo: Expand on this.
		window.registerCallbacks();
	}
}