#include <GLRender/Game.h>
#include <GLRender/Graphics/Shader.h>

using namespace glr;

int main()
{
	Game game;
	game.showWindow(1280, 720, "LoadShaderTest");

	Shader shader;
	shader.addSubShader("data/shaders/basic.vert");
	shader.addSubShader("data/shaders/basic.frag");
	shader.link();

	return 0;
}
