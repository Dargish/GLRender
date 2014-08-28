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
#include <graphics/Plane.h>
#include <graphics/Texture.h>
#include <graphics/TextureFile.h>
#include "FreeCamera.h"

#define FRAMETIME_LIMIT 16666 // in usec (60fps)

using namespace io;
using namespace ecs;
using namespace graphics;
using namespace components;
using namespace systems;
using namespace serialisation;

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
	Serialiser::RegisterSerialisable<Plane>();
	Serialiser::RegisterSerialisable<Transform>();
	Serialiser::RegisterSerialisable<Material>();
	Serialiser::RegisterSerialisable<FloatValue>();
	Serialiser::RegisterSerialisable<Vector3Value>();
	Serialiser::RegisterSerialisable<TextureValue>();
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
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
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
	RenderSystem_Ptr renderSystem = world->createSystem<RenderSystem>();
	world->setCamera(Camera_Ptr(new FreeCamera));

	//for (size_t i = 0; i < 8; ++i)
	//{
	//	EntityID cubeID = world->createEntity("Cube");
	//	Transform_Ptr transform = world->component<TransformComponent>(cubeID)->transform;
	//	transform->position.x = (i & 1) == 0 ? -3.0f : 3.0f;
	//	transform->position.y = (i & 2) == 0 ? -3.0f : 3.0f;
	//	transform->position.z = (i & 4) == 0 ? -3.0f : 3.0f;
	//	Material_Ptr material = world->component<MaterialComponent>(cubeID)->material;
	//	if ((i & 1) == 0)
	//	{
	//		material->load("Red");
	//	}
	//	else if ((i & 2) == 0)
	//	{
	//		material->load("Green");
	//	}
	//	else if ((i & 4) == 0)
	//	{
	//		material->load("Blue");
	//	}
	//}

	//world->save("Test2");
	//world->load("Test2");

	//EntityID entityID1 = StrToEntityID("28852923-dc75-4b0e-9fd0-f6ab9deb02cd");
	//world->component<MaterialComponent>(entityID1)->material->load("Textured");

	//EntityID entityID2 = StrToEntityID("6094aacb-0394-49b1-a46f-27e282ac64b6");
	//world->component<MaterialComponent>(entityID2)->material->setShader(Shader::Load("ShowNormal"));
	//world->component<MeshComponent>(entityID2)->meshAs<Cube>()->setSmooth(true);

	//EntityID planeID = world->createEntity();
	//world->addComponent(planeID, TransformComponent_Ptr(new TransformComponent()));
	//MeshComponent_Ptr meshComponent(new MeshComponent());
	//meshComponent->mesh.reset(new Plane());
	//world->addComponent(planeID, meshComponent);
	//MaterialComponent_Ptr materialComponent(new MaterialComponent());
	//materialComponent->material->load("Textured");
	//world->addComponent(planeID, materialComponent);

	world->load("Test2");

	if (!m_font.loadFromFile("Content/Fonts/SourceSansPro-Regular.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}

	sf::Vector2u windowSize = window->getSize();
	renderSystem->resetFrameBufferSize(Point2(windowSize.x, windowSize.y));
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

		world->draw(deltaTime);

		window->pushGLStates();
		sf::Text text((boost::format("DirectionX: %s, DirectionY %s") % world->camera()->direction().x % world->camera()->direction().y).str(), m_font);
		text.setPosition(0.5f, 0.5f);
		text.setColor(sf::Color::Red);
		text.setCharacterSize(16);
		window->draw(text);
		window->popGLStates();

		window->display();

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
