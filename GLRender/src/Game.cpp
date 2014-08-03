#include "Game.h"
#include <GL/glew.h>
#include <boost/format.hpp>
#include <io/InputManager.h>
#include <serialisation/Serialiser.h>
#include <ecs/World.h>
#include <ecs/Component.h>
#include <ecs/ComponentContainer.h>
#include <systems/RenderSystem.h>
#include <components/TransformComponent.h>
#include <components/MeshComponent.h>
#include <components/MaterialComponent.h>
#include <graphics/Window.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>
#include <graphics/Transform.h>
#include <graphics/Camera.h>
#include <graphics/Cube.h>
#include "FreeCamera.h"

#define FRAMETIME_LIMIT 16666 // in usec (60fps)

using namespace io;
using namespace ecs;
using namespace graphics;
using namespace components;
using namespace systems;
using namespace serialisation;

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
	registerSerialisables();
}

void Game::registerSerialisables()
{
	Serialiser::RegisterSerialisable<MaterialComponent>();
	Serialiser::RegisterSerialisable<MeshComponent>();
	Serialiser::RegisterSerialisable<TransformComponent>();
	Serialiser::RegisterSerialisable<Cube>();
	Serialiser::RegisterSerialisable<Transform>();
	Serialiser::RegisterSerialisable<Material>();
	Serialiser::RegisterSerialisable<FloatValue>();
	Serialiser::RegisterSerialisable<Vector3Value>();
	Serialiser::RegisterSerialisable<ComponentContainer>();
}

sf::RenderWindow_Ptr Game::createWindow()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 0;

	Window::Init(sf::VideoMode(1280, 720), "OpenGL Renderer", sf::Style::Default, settings);
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

	World_Ptr world(new World);
	world->createSystem<RenderSystem>();
	world->setCamera(Camera_Ptr(new FreeCamera));

	//for (size_t i = 0; i < 8; ++i)
	//{
	//	EntityID cubeID = world->createEntity();
	//	TransformComponent_Ptr transformComponent(new TransformComponent);
	//	transformComponent->transform->position.x = (i & 1) == 0 ? -1.0f : 1.0f;
	//	transformComponent->transform->position.y = (i & 2) == 0 ? -1.0f : 1.0f;
	//	transformComponent->transform->position.z = (i & 4) == 0 ? -1.0f : 1.0f;
	//	MeshComponent_Ptr cubeComponent(new MeshComponent);
	//	cubeComponent->mesh.reset(new Cube(1.0f));
	//	MaterialComponent_Ptr MaterialComponent(new MaterialComponent);
	//	MaterialComponent->material.reset(new Material);
	//	if ((i & 1) == 0)
	//	{
	//		MaterialComponent->material->load("Red");
	//	}
	//	else if ((i & 2) == 0)
	//	{
	//		MaterialComponent->material->load("Green");
	//	}
	//	else if ((i & 4) == 0)
	//	{
	//		MaterialComponent->material->load("Blue");
	//	}
	//	else
	//	{
	//		MaterialComponent->material->setShader(Shader::Load("Generic"));
	//	}
	//	world->addComponent(cubeID, transformComponent);
	//	world->addComponent(cubeID, cubeComponent);
	//	world->addComponent(cubeID, MaterialComponent);
	//}

	//world->save("Test");
	world->load("Test");

	world->saveEntity(StrToEntityID("2bd83bc7-e04b-4fdd-a2a1-dbefe4fd4b1c"), "Cube");

	EntityID entityID = StrToEntityID("2bd83bc7-e04b-4fdd-a2a1-dbefe4fd4b1c");

	MaterialComponent_Ptr material = world->component<MaterialComponent>(entityID);
	material->material->setValue("color", Vector3(1, 1, 1));

	//Component_Ptr materialComponent;
	//world->getComponent(StrToEntityID("18945b89-d78d-459d-bd13-ae469705e207"), MaterialComponent::TypeName(), materialComponent);
	//MaterialComponent_Ptr typedMaterialComponent = boost::dynamic_pointer_cast<MaterialComponent>(materialComponent);
	//typedMaterialComponent->material->load("Blue");
	//typedMaterialComponent->material->setValue("color", Vector3(1, 0, 0));

	//world->save("Test");


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
		glEnable(GL_DEPTH_TEST);

		world->draw(deltaTime);

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
