#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/Graphics/Mesh.h>

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

	class GLRENDERAPI Model
	{
	public:
		typedef Mesh<Vertex> MeshType;
		typedef std::vector<MeshType> Meshes;

		Model();
		Model(const string& path);

		void load(const string& path);

	private:
		Meshes m_meshes;
	};
}