#include <GLRender/Game.h>

#include <GLRender/Systems/ControlSystem.h>

using namespace glr;

struct MyComponent : public Component
{
	float v;
};

int main()
{
	Game game;

	World& world = game.world();

	Entity& model = world.addModel("Model1", "cerberus.fbx");

	Camera camera = world.addCamera("Camera1");

	std::shared_ptr<ControlSystem> controlSystem = game.addSystem<ControlSystem>();

	return 0;
}
