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
};

typedef GlBuffer<Vertex> VertexBuffer;

int main()
{
	VertexBuffer vertexBuffer;

	std::cerr << vertexBuffer.size() << std::endl;
	std::cerr << vertexBuffer.Stride << std::endl;

	return 0;
}
