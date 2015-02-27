#include <GLRender/Game.h>
#include <GLRender/World/World.h>
#include <GLRender/Renderer/ForwardRenderer.h>
#include <GLRender/Graphics/Shader.h>

using namespace glr;

int main()
{
	Game game;

	game.showWindow(1280, 720, "CreateWindowTest");

	World& world = game.world();

	world.addModel("cerberus", "data/models/cerberus.fbx");

	/*std::shared_ptr<ForwardRenderSystem> renderSystem = */game.setRenderer<ForwardRenderer>();

	Shader shader;
	shader.addSubShader("data/shaders/basic.vert");
	shader.addSubShader("data/shaders/basic.frag");
	shader.link();

	return game.run();
}