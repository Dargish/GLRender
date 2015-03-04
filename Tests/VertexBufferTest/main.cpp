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

	static void Enable()
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, binormal));
	}

	static void Disable()
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
	}
};

typedef BaseVertexBuffer<Vertex> VertexBuffer;

int main()
{
	Game game;
	game.showWindow(1280, 720, "VertexBufferTest");

	VertexBuffer vertexBuffer(3);
	vertexBuffer[0].position = Vector3(0.5, 0.0, 0.0);
	vertexBuffer[1].position = Vector3(0.0, 1.0, 0.0);
	vertexBuffer[2].position = Vector3(1.0, 1.0, 0.0);
	vertexBuffer.copyToGPU();

	return 0;
}
