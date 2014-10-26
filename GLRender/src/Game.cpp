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
#include <components/LightComponent.h>
#include <graphics/Window.h>
#include <graphics/Shader.h>
#include <graphics/ShaderValue.h>
#include <graphics/lights/DirectionalLight.h>
#include <graphics/Material.h>
#include <graphics/Model.h>
#include <graphics/Transform.h>
#include <graphics/Camera.h>
#include <graphics/primitives/Cube.h>
#include <graphics/primitives/Plane.h>
#include <graphics/primitives/Sphere.h>
#include <graphics/primitives/Torus.h>
#include <graphics/Texture.h>
#include <graphics/TextureFile.h>
#include "FreeCamera.h"

#define FRAMETIME_LIMIT 16666 // in usec (60fps)

using namespace io;
using namespace ecs;
using namespace graphics;
using namespace graphics::lights;
using namespace graphics::primitives;
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
	Serialiser::RegisterSerialisable<LightComponent>();
	Serialiser::RegisterSerialisable<DirectionalLight>();
	Serialiser::RegisterSerialisable<Model>();
	Serialiser::RegisterSerialisable<Cube>();
	Serialiser::RegisterSerialisable<Plane>();
	Serialiser::RegisterSerialisable<Sphere>();
	Serialiser::RegisterSerialisable<Torus>();
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

	for (size_t r = 0; r <= 10; ++r)
	{
		for (size_t m = 0; m <= 10; ++m)
		{
			EntityID s = world->createEntity("Sphere");
			float rf = r / 10.0f;
			float mf = m / 10.0f;
			world->component<MaterialComponent>(s)->material->setValue("v_color", Vector3(rf, 0, mf));
			world->component<MaterialComponent>(s)->material->setValue("v_roughness", rf);
			world->component<MaterialComponent>(s)->material->setValue("v_metallicity", mf);
			world->component<TransformComponent>(s)->transform->position.x = r * 2.5f;
			world->component<TransformComponent>(s)->transform->position.z = m * 2.5f;
		}
	}

	{
		EntityID lightID = world->createEntity();
		LightComponent_Ptr lightComponent(new LightComponent);
		lightComponent->light.reset(new DirectionalLight(Vector3(-1.0f, -0.75f, -0.75f), Vector3(1.0f, 0.9f, 0.8f), 1.0f));
		world->addComponent(lightID, lightComponent);
	}

	//{
	//	EntityID lightID = world->createEntity();
	//	LightComponent_Ptr lightComponent(new LightComponent);
	//	lightComponent->light.reset(new DirectionalLight(Vector3(1, -0.75f, -0.75f), Vector3(1.0f, 1.0f, 1.0f), 0.02f));
	//	world->addComponent(lightID, lightComponent);
	//}

	//{
	//	EntityID lightID = world->createEntity();
	//	LightComponent_Ptr lightComponent(new LightComponent);
	//	lightComponent->light.reset(new DirectionalLight(Vector3(0.25f, 0.75f, 0.25f), Vector3(1.0f, 1.0f, 1.0f), 0.01f));
	//	world->addComponent(lightID, lightComponent);
	//}

	//world->load("primTest");

	if (!m_font.loadFromFile("Content/Fonts/SourceSansPro-Regular.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}

	sf::Vector2u windowSize = window->getSize();
	renderSystem->resetFrameBufferSize(Point2(windowSize.x, windowSize.y));
	glViewport(0, 0, windowSize.x, windowSize.y);
	world->camera()->updateProjectionMatrix(windowSize.x, windowSize.y);
	m_clock.restart();
	float frameTimeF = 0.0f;
	int fps = 0;
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

		world->draw(deltaTime);

		window->pushGLStates();
		frameTimeF = float(m_clock.getElapsedTime().asMicroseconds()) / 1000.0f;
		Frustum frustum = world->camera()->frustum();
		sf::Text text((boost::format("FrameTime: %.04fms, FPS: %dfps, Target: %dfps\nFrustum: (%.04f, %.04f, %.04f)->(%.04f, %.04f, %.04f)") % 
			frameTimeF % fps % (1000000 / FRAMETIME_LIMIT) % frustum.corners[0].x % frustum.corners[0].y % frustum.corners[0].z % frustum.corners[7].x % frustum.corners[7].y % frustum.corners[7].z).str(), m_font);
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
		fps = int(1000000.0f / (float(m_clock.getElapsedTime().asMicroseconds())));
	}
}

Game::~Game()
{
}
