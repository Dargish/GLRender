#pragma once
#include "fwd.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace graphics
{
	class Window
	{
	public:
		static Window_Ptr Instance();
		~Window();

		void init(sf::VideoMode mode, const std::string& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

		sf::RenderWindow_Ptr& getWindow();

		static void Init(sf::VideoMode mode, const std::string& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

		static sf::RenderWindow_Ptr& GetWindow();

	private:
		Window();

		static Window_Ptr s_instance;
		sf::RenderWindow_Ptr m_window;
	};
}

