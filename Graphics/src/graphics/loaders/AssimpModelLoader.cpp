#include "AssimpModelLoader.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace graphics
{
	AssimpModelLoader::~AssimpModelLoader()
	{
	}

	void AssimpModelLoader::load(const std::string& filePath, VertexBuffer_Ptr& vertexBuffer, IndexBuffer_Ptr& indexBuffer) const
	{
		vertexBuffer.reset(new VertexPositionUVNormalTangentBiNormalBuffer());
		VertexPositionUVNormalTangentBiNormalBuffer::BufferType& vBuffer = boost::dynamic_pointer_cast<VertexPositionUVNormalTangentBiNormalBuffer>(vertexBuffer)->data();
		vBuffer.clear();

		indexBuffer.reset(new IndexBuffer());
		IndexBuffer::BufferType& iBuffer = indexBuffer->data();

		iBuffer.clear();
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(
			filePath,
			aiProcess_GenSmoothNormals |
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_SortByPType);

		if (!scene)
		{
			throw std::runtime_error("Error loading file");
		}

		uint totalVertices = 0;
		uint totalIndices = 0;
		for (uint m = 0; m < scene->mNumMeshes; ++m)
		{
			aiMesh* mesh = scene->mMeshes[m];
			totalVertices += mesh->mNumVertices;
			totalIndices += mesh->mNumFaces * 3;
		}

		vBuffer.resize(totalVertices);
		iBuffer.resize(totalIndices);

		uint vertexOffset = 0;
		uint indexOffset = 0;
		for (uint m = 0; m < scene->mNumMeshes; ++m)
		{
			aiMesh* mesh = scene->mMeshes[m];
			bool hasPositions = mesh->HasPositions();
			bool hasNormals = mesh->HasNormals();
			bool hasTangents = mesh->HasTangentsAndBitangents();
			bool hasTexCoords = mesh->HasTextureCoords(0);

			for (uint v = 0; v < mesh->mNumVertices; ++v)
			{
				if (hasPositions)
				{
					aiVector3D& position = mesh->mVertices[v];
					vBuffer[vertexOffset + v].position = Vector3(position.x, position.y, position.z);
				}
				if (hasNormals)
				{
					aiVector3D& normal = mesh->mNormals[v];
					vBuffer[vertexOffset + v].normal = Vector3(normal.x, normal.y, normal.z);
				}
				if (hasTangents)
				{
					aiVector3D& tangent = mesh->mTangents[v];
					aiVector3D& binormal = mesh->mBitangents[v];
					vBuffer[vertexOffset + v].tangent = Vector3(tangent.x, tangent.y, tangent.z);
					vBuffer[vertexOffset + v].binormal = Vector3(binormal.x, binormal.y, binormal.z);
				}
				if (hasTexCoords)
				{
					aiVector3D& uvw = mesh->mTextureCoords[0][v];
					vBuffer[vertexOffset + v].uv = Vector2(uvw.x, -uvw.y);
				}
			}

			for (uint f = 0; f < mesh->mNumFaces; ++f)
			{
				aiFace* face = &mesh->mFaces[f];

				uint baseIndex = indexOffset + (f * 3);
				iBuffer[baseIndex] = vertexOffset + face->mIndices[0];
				iBuffer[baseIndex + 1] = vertexOffset + face->mIndices[1];
				iBuffer[baseIndex + 2] = vertexOffset + face->mIndices[2];
			}
			vertexOffset += mesh->mNumVertices;
			indexOffset += mesh->mNumFaces * 3;
		}

		vertexBuffer->dirty();
		indexBuffer->dirty();
	}
}
