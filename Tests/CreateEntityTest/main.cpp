#include <GLRender/Game.h>

using namespace glr;

int main()
{
	Game game;

	World& world = game.world();

	Entity& entity = world.createEntity("Entity1");

	assert(entity.name() == "Entity1");

	Entity& found = world.entity("Entity1");

	assert(entity == found);

	return 0;
}
