#include <GLRender/Game.h>

using namespace glr;

struct MyComponent : public Component
{
	float v;
};

int main()
{
	Game game;

	World& world = game.world();

	Entity& entity = world.createEntity("Entity1");

	std::shared_ptr<MyComponent> comp = entity.addComponent<MyComponent>();

	comp->v = 1.4f;

	assert(entity.name() == "Entity1");

	Entity& found = world.entity("Entity1");

	assert(entity.name() == found.name());

	std::shared_ptr<MyComponent> foundComp = found.component<MyComponent>();

	assert(foundComp);

	assert(comp.get() == foundComp.get());

	ComponentVector foundComps = found.components<MyComponent>();

	assert(foundComps.size() == 1);

	assert(foundComps[0].get() == comp.get());

	return 0;
}
