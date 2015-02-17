#include <GLRender/Game.h>

#include <GL/glew.h>

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
		sf::Event event;
		sf::Clock clock;
		while (m_window->isOpen())
		{
			// Calculate frame time
			float deltaTime = clock.getElapsedTime().asSeconds();
			//elapsedTime += deltaTime;
			clock.restart();

			// Handle events
			while (m_window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window->close();
				}
				else if (event.type == sf::Event::Resized)
				{
					// adjust the viewport when the window is resized
					glViewport(0, 0, event.size.width, event.size.height);
					//world->camera()->updateProjectionMatrix(event.size.width, event.size.height);
				}
			}

			world->update(deltaTime);

			world->draw(deltaTime);

			m_window->display();

			// Sleep for excess time
			sf::Int64 frameTime = clock.getElapsedTime().asMicroseconds();
			if (frameTime < FRAMETIME_LIMIT)
			{
				sf::sleep(sf::microseconds(FRAMETIME_LIMIT - frameTime));
			}
			fps = int(1000000.0f / (float(clock.getElapsedTime().asMicroseconds())));
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
		if (!m_glewInitted)
		{
			initGlew();
		}
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

	long Game::frameTimeLimit() const
	{
		return m_frameTimeLimit;
	}

	void Game::setFrameTimeLimit(long frameTimeLimit)
	{
		m_frameTimeLimit = frameTimeLimit;
	}


	// Private

	void Game::initGlew()
	{		
		glewExperimental = true;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			throw std::runtime_error((boost::format("glewInit() failed: %s") % glewGetErrorString(err)).str());
		}
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		m_glewInitted = true;
	}
}