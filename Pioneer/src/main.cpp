#include <GLRender/Game.h>
#include <GLRender/World/World.h>
#include <GLRender/Renderer/ForwardRenderer.h>

using namespace glr;

int main()
{
	Game game;

	game.showWindow(1280, 720, "CreateWindowTest");

	World& world = game.world();

	world.addModel("cerberus", "data/models/cerberus.fbx");

	/*std::shared_ptr<ForwardRenderSystem> renderSystem = */game.setRenderer<ForwardRenderer>();

	return game.run();
}