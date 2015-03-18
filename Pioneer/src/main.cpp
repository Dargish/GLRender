#include <GLRender/Game.h>
#include <GLRender/World/World.h>
#include <GLRender/Renderer/ForwardRenderer.h>
#include <GLRender/System/CameraSystem.h>
#include <GLRender/Component/TransformComponent.h>
#include <GLRender/Component/CameraComponent.h>

using namespace glr;

class MySystem : public System
{
public:
	MySystem(Entity& camera) :
		m_camera(camera), m_totalTime(0.0f)
	{

	}

	virtual void update(World& /*world*/, float deltaTime)
	{
		m_totalTime += deltaTime * 5;
		m_camera.component<TransformComponent>()->rotation.x = std::sin(m_totalTime) * 3.14;
		//m_camera.component<TransformComponent>()->rotation.y = std::sin(m_totalTime);
		//m_camera.component<TransformComponent>()->rotation.z = std::sin(m_totalTime);
	}

private:
	Entity& m_camera;
	float m_totalTime;
};

class MyGame : public Game
{
public:
	MyGame() :
		Game(), m_world(), m_camera(m_world.addCamera("camera")), m_mySystem(m_camera)
	{
		window().setTitle("Pioneer");

		m_camera.component<TransformComponent>()->position = Vector3(25, -25, 0);
		m_camera.component<CameraComponent>()->viewportSize = Vector2(1280, 720);
		m_world.addModel("cerberus", "data/models/cerberus.fbx");
	}

protected:
	virtual void update(float deltaTime)
	{
		m_cameraSystem.update(m_world, deltaTime);
		m_mySystem.update(m_world, deltaTime);
	}

	virtual void draw(float deltaTime)
	{
		m_renderer.draw(m_camera, m_world, deltaTime);
	}

private:
	World m_world;
	Entity& m_camera;

	CameraSystem m_cameraSystem;
	MySystem m_mySystem;
	ForwardRenderer m_renderer;
};

int main()
{
	return MyGame().run();
}