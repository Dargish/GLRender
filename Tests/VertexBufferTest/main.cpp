#include <GLRender/Game.h>
#include <GLRender/Graphics/GlBuffer.h>

using namespace glr;

#include <iostream>

struct Vertex
{
	Vector3 position;
	Vector2 uv;
	Vector3 normal;
	Vector3 tangent;
	Vector3 binormal;

	static void Enable(VertexEnabler& handler)
	{
		std::cerr << "Enabling" << std::endl;
		handler
			.attrib<Vector3>()
			.attrib<Vector2>()
			.attrib<Vector3>()
			.attrib<Vector3>()
			.attrib<Vector3>();
	}

	static void Disable(VertexDisabler& handler)
	{
		std::cerr << "Enabling" << std::endl;
		handler
			.attrib<Vector3>()
			.attrib<Vector2>()
			.attrib<Vector3>()
			.attrib<Vector3>()
			.attrib<Vector3>();
	}
};

typedef VertexBuffer<Vertex> MyVertexBuffer;

int main()
{
	Game game;
	game.showWindow(1280, 720, "VertexBufferTest");

	MyVertexBuffer vertexBuffer(3);
	vertexBuffer[0].position = Vector3(0.5, 0.0, 0.0);
	vertexBuffer[1].position = Vector3(0.0, 1.0, 0.0);
	vertexBuffer[2].position = Vector3(1.0, 1.0, 0.0);
	vertexBuffer.copyToGPU();

	return 0;
}
