#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/Graphics/Mesh.h>

namespace glr
{
	struct PUNTBVertex
	{
		Vector3 position;
		Vector2 uv;
		Vector3 normal;
		Vector3 tangent;
		Vector3 binormal;

		static void Enable()
		{
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PUNTBVertex), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(PUNTBVertex), (void*)offsetof(PUNTBVertex, uv));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(PUNTBVertex), (void*)offsetof(PUNTBVertex, normal));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(PUNTBVertex), (void*)offsetof(PUNTBVertex, tangent));
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(PUNTBVertex), (void*)offsetof(PUNTBVertex, binormal));
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

	class GLRENDERAPI Model
	{
	public:
		typedef Mesh<PUNTBVertex> MeshType;
		typedef std::vector<MeshType> Meshes;

		Model();
		Model(const string& path);

		void load(const string& path);

		void draw() const;

	private:
		Meshes m_meshes;
	};
}