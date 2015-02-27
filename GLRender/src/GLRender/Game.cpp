#include <GLRender/Game.h>

#include <GL/glew.h>

#include <SFML/Graphics.hpp>

namespace glr
{
	// Public

	Game::Game() :
		m_glewInitted(false),
		m_frameTimeLimit(16666)
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
		initGlew();
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

	long Game::frameTimeLimit() const
	{
		return m_frameTimeLimit;
	}

	void Game::setFrameTimeLimit(long frameTimeLimit)
	{
		m_frameTimeLimit = frameTimeLimit;
	}


	// Private

	void Game::update(float deltaTime)
	{
		SystemVector::iterator it = m_systems.begin();
		for (; it != m_systems.end(); ++it)
		{
			(*it)->update(m_world, deltaTime);
		}
	}

	void Game::draw(float deltaTime)
	{
		if (m_renderer.get())
		{
			m_renderer->draw(m_world, deltaTime);
		}
	}

	void Game::initGlew()
	{
		if (!m_glewInitted)
		{
			glewExperimental = true;
			GLenum err = glewInit();
			if (err != GLEW_OK)
			{
				throw std::runtime_error(string("glewInit() failed: ") + string((char*)glewGetErrorString(err)));
			}
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			m_glewInitted = true;
		}
	}
}