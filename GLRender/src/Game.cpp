#include "Game.h"
#include <GL/glew.h>
#include <boost/format.hpp>
#include "core/TypeDefs.h"
#include "core/io/InputManager.h"
#include "ecs/World.h"
#include "ecs/Entity.h"
#include "ecs/systems/RenderSystem.h"
#include "ecs/components/TransformComponent.h"
#include "ecs/components/MeshComponent.h"
#include "core/Window.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "graphics/FreeCamera.h"
#include "graphics/Cube.h"

#define FRAMETIME_LIMIT 16666 // in usec (60fps)

using namespace io;
using namespace ecs;
using namespace graphics;

void checkGlError()
{
	GLenum err = glGetError();
	switch (err)
	{
	case GL_INVALID_ENUM:
		throw std::runtime_error("An unacceptable value is specified for an enumerated argument.The offending command is ignored and has no other side effect than to set the error flag.");
	case GL_INVALID_VALUE:
		throw std::runtime_error("A numeric argument is out of range.The offending command is ignored and has no other side effect than to set the error flag.");
	case GL_INVALID_OPERATION:
		throw std::runtime_error("The specified operation is not allowed in the current state.The offending command is ignored and has no other side effect than to set the error flag.");
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		throw std::runtime_error("The framebuffer object is not complete.The offending command is ignored and has no other side effect than to set the error flag.");
	case GL_OUT_OF_MEMORY:
		throw std::runtime_error("There is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");
	case GL_STACK_UNDERFLOW:
		throw std::runtime_error("An attempt has been made to perform an operation that would cause an internal stack to underflow.");
	case GL_STACK_OVERFLOW:
		throw std::runtime_error("An attempt has been made to perform an operation that would cause an internal stack to overflow.");
	case GL_NO_ERROR:
	default:
		return;
	}
}

Game::Game()
{

}

sf::RenderWindow_Ptr Game::createWindow()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 0;

	Window::Init(sf::VideoMode(1280, 720), "Flight Sim", sf::Style::Default, settings);
	return Window::GetWindow();
}

void Game::initGlew()
{
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		throw std::runtime_error((boost::format("glewInit() failed: %s") % glewGetErrorString(err)).str());
	}
}

void Game::setupInputManager()
{
	InputManager::AddInput("Escape", sf::Keyboard::Escape);
	InputManager::SetMouseLocked(true);
}

void Game::start()
{
	sf::RenderWindow_Ptr window = createWindow();

	initGlew();
	
	setupInputManager();
	
	Shader_Ptr shader(new Shader);
	shader->load("Content/Shaders/Generic.xml");

	World_Ptr world(new World);
	world->setCamera(Camera_Ptr(new FreeCamera));
	world->createSystem<RenderSystem>();

	for (size_t i = 0; i < 8; ++i)
	{
		Entity_Ptr cubeEntity = world->createEntity();
		TransformComponent_Ptr transformComponent = cubeEntity->createComponent<TransformComponent>();
		transformComponent->position.x = (i & 1) == 0 ? -1.0f : 1.0f;
		transformComponent->position.y = (i & 2) == 0 ? -1.0f : 1.0f;
		transformComponent->position.z = (i & 4) == 0 ? -1.0f : 1.0f;
		MeshComponent_Ptr cubeComponent = cubeEntity->createComponent<MeshComponent>();
		cubeComponent->mesh = Cube::Create(1.0f);
	}

	if (!m_font.loadFromFile("Content/Fonts/SourceSansPro-Regular.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}

	sf::Vector2u windowSize = window->getSize();
	glViewport(0, 0, windowSize.x, windowSize.y);
	world->camera()->updateProjectionMatrix(windowSize.x, windowSize.y);
	m_clock.restart();
	while (window->isOpen())
	{
		// Calculate frame time
		float deltaTime = m_clock.getElapsedTime().asSeconds();
		m_clock.restart();

		// Handle events
		while (window->pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
			{
				window->close();
			}
			else if (m_event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, m_event.size.width, m_event.size.height);
				world->camera()->updateProjectionMatrix(m_event.size.width, m_event.size.height);
			}
		}

		// Update
		InputManager::Update();
		if (InputManager::IsDown("Escape"))
		{
			window->close();
			break;
		}
		world->update(deltaTime);

		// Draw
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Shader::Enable(shader);
		shader->setValue("world", Matrix4());
		shader->setValue("proj", world->camera()->projMatrix());
		shader->setValue("view", world->camera()->viewMatrix());
		world->draw(deltaTime);
		Shader::Disable(shader);

		window->pushGLStates();
		sf::Text text((boost::format("DirectionX: %s, DirectionY %s") % world->camera()->direction().x % world->camera()->direction().y).str(), m_font);
		text.setPosition(0.5f, 0.5f);
		text.setColor(sf::Color::Red);
		text.setCharacterSize(16);
		window->draw(text);
		window->popGLStates();

		window->display();

		checkGlError();

		// Sleep for excess time
		sf::Int64 frameTime = m_clock.getElapsedTime().asMicroseconds();
		if (frameTime < FRAMETIME_LIMIT)
		{
			sf::sleep(sf::microseconds(FRAMETIME_LIMIT - frameTime));
		}
	}
}

Game::~Game()
{
}
