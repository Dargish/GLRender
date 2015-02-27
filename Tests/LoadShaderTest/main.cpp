#include <GLRender/Graphics/Shader.h>

using namespace glr;

int main()
{
	Shader shader;
	shader.addSubShader("data/shaders/basic.vert");
	shader.addSubShader("data/shaders/basic.frag");
	shader.link();

	return 0;
}
