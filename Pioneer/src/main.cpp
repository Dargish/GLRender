#include <GLRender/Game.h>
#include <GLRender/World/World.h>
#include <GLRender/Renderer/ForwardRenderer.h>
#include <GLRender/System/CameraSystem.h>
#include <GLRender/Component/CameraComponent.h>

using namespace glr;

class MyGame : public Game
{
public:
	MyGame() :
		Game(), m_cameraName("camera")
	{
		showWindow(1280, 720, "Pioneer");
		Entity& camera = world().addCamera(m_cameraName);
		camera.component<CameraComponent>()->viewportSize = Vector2(1280, 720);
		world().addModel("cerberus", "data/models/cerberus.fbx");
		addSystem<CameraSystem>();
		setRenderer<ForwardRenderer>();
	}

protected:
	virtual const string& activeCamera() const
	{
		return m_cameraName;
	}

private:
	string m_cameraName;
};

int main()
{
	return MyGame().run();
}