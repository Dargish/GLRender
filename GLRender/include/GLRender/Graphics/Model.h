#pragma once

#include <GLRender/DataTypes.h>

namespace glr
{
	struct Vertex
	{
		Vector3 position;
		Vector2 uv;
		Vector3 normal;
		Vector3 tangent;
		Vector3 binormal;
	};

	class Model
	{
	public:
		typedef Mesh<Vertex> MeshType;
		Model();

	private:
		MeshType m_mesh;
	};
}