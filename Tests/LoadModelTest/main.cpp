#include <GLRender/Game.h>

#include <GLRender/System/ControlSystem.h>

using namespace glr;

int main()
{
	Game game;

	World& world = game.world();

	/*Entity& model = */world.addModel("Model1", "data/models/cerberus.fbx");

	return 0;
}
