#include <GLRender/Graphics/VertexBuffer.h>

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

typedef VertexBuffer<Vertex> MyVertexBuffer;

int main()
{
	MyVertexBuffer vBuffer;

	std::cerr << vBuffer.size() << std::endl;
	std::cerr << vBuffer.Stride << std::endl;

	return 0;
}
