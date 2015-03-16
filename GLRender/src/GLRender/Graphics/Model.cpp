#include <GLRender/Graphics/Model.h>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace glr
{
	Model::Model()
	{
		
	}

	Model::Model(const string& path)
	{
		load(path);
	}

	Model::Model(const MeshType& mesh)
	{
		addMesh(mesh);
	}

	void Model::load(const string& path)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(
			path,
			aiProcess_GenSmoothNormals |
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_SortByPType);

		if (!scene)
		{
			throw std::runtime_error("Error loading file");
		}

		m_meshes.resize(scene->mNumMeshes);

		for (uint m = 0; m < scene->mNumMeshes; ++m)
		{
			MeshType::VertexBuffer& vertexBuffer = m_meshes[m].vertexBuffer();
			IndexBuffer& indexBuffer = m_meshes[m].indexBuffer();

			aiMesh* mesh = scene->mMeshes[m];
			vertexBuffer.resize(mesh->mNumVertices);
			indexBuffer.resize(mesh->mNumFaces * 3);

			bool hasPositions = mesh->HasPositions();
			bool hasNormals = mesh->HasNormals();
			bool hasTangents = mesh->HasTangentsAndBitangents();
			bool hasTexCoords = mesh->HasTextureCoords(0);

			for (uint v = 0; v < mesh->mNumVertices; ++v)
			{
				if (hasPositions)
				{
					aiVector3D& position = mesh->mVertices[v];
					vertexBuffer[v].position = Vector3(position.x, position.y, position.z);
				}
				if (hasNormals)
				{
					aiVector3D& normal = mesh->mNormals[v];
					vertexBuffer[v].normal = Vector3(normal.x, normal.y, normal.z);
				}
				if (hasTangents)
				{
					aiVector3D& tangent = mesh->mTangents[v];
					aiVector3D& binormal = mesh->mBitangents[v];
					vertexBuffer[v].tangent = Vector3(tangent.x, tangent.y, tangent.z);
					vertexBuffer[v].binormal = Vector3(binormal.x, binormal.y, binormal.z);
				}
				if (hasTexCoords)
				{
					aiVector3D& uvw = mesh->mTextureCoords[0][v];
					vertexBuffer[v].uv = Vector2(uvw.x, -uvw.y);
				}
			}

			vertexBuffer.copyToGPU();

			for (uint f = 0; f < mesh->mNumFaces; ++f)
			{
				aiFace* face = &mesh->mFaces[f];

				uint baseIndex = (f * 3);
				indexBuffer[baseIndex] = face->mIndices[0];
				indexBuffer[baseIndex + 1] = face->mIndices[1];
				indexBuffer[baseIndex + 2] = face->mIndices[2];
			}
			
			indexBuffer.copyToGPU();
		}
	}

	void Model::addMesh(const MeshType& mesh)
	{
		m_meshes.push_back(mesh);
	}

	void Model::draw() const
	{
		for (Meshes::const_iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		{
			it->draw();
		}
	}
}