#include <GLRender/Game.h>

#include <GL/glew.h>

#include <SFML/Graphics.hpp>

namespace glr
{
	// Public

	Game::Game() :
		m_frameTimeLimit(16666)
	{
		m_window.create(1280, 720, "GLRender");
		glewExperimental = true;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			throw std::runtime_error(string("glewInit() failed: ") + string((char*)glewGetErrorString(err)));
		}
	}

	Game::~Game()
	{
		
	}

	int Game::run()
	{
		sf::Clock clock;
		while (m_window.isOpen())
		{
			// Calculate frame time
			float deltaTime = clock.getElapsedTime().asSeconds();
			//elapsedTime += deltaTime;
			clock.restart();

			// Handle events
			m_window.pollEvents();

			update(deltaTime);

			draw(deltaTime);

			m_window.display();

			// Sleep for excess time
			sf::Int64 frameTime = clock.getElapsedTime().asMicroseconds();
			if (frameTime < m_frameTimeLimit)
			{
				sf::sleep(sf::microseconds(m_frameTimeLimit - frameTime));
			}
		}
		return 0;
	}

	Window& Game::window()
	{
		return m_window;
	}

	const Window& Game::window() const
	{
		return m_window;
	}

	long Game::frameTimeLimit() const
	{
		return m_frameTimeLimit;
	}

	void Game::setFrameTimeLimit(long frameTimeLimit)
	{
		m_frameTimeLimit = frameTimeLimit;
	}


	// Protected

	void Game::update(float /*deltaTime*/)
	{
		
	}

	void Game::draw(float /*deltaTime*/)
	{
		
	}
}