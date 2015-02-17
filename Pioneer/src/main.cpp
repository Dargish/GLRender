#include <GLRender/Game.h>
#include <GLRender/World/World.h>

using namespace glr;

int main()
{
	Game game;

	game.showWindow(1280, 720, "CreateWindowTest");

	World& world = game.world();

	world.addModel("cerberus", "data/models/cerberus.fbx");

	return game.run();
}