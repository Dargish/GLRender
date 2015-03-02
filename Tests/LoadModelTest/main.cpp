#include <GLRender/Game.h>

#include <GLRender/System/ControlSystem.h>

#include <iostream>

using namespace glr;

int main()
{
	try
	{
		Game game;

		World& world = game.world();

		/*Entity& model = */world.addModel("Model1", "data/models/cerberus.fbx");
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		throw e;
	}
	return 0;
}
