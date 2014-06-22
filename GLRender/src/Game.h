#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "core/fwd.h"

class Game
{
public:
	Game();
	~Game();

	void start();

private:
	sf::RenderWindow_Ptr createWindow();
	void initGlew();
	void setupInputManager();

	sf::Clock m_clock;
	sf::Event m_event;
	sf::Font m_font;
};

