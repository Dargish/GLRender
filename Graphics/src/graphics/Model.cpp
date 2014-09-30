#include "Model.h"
#include <json/json.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace graphics
{
	std::string Model::ModelPath(const std::string& modelName)
	{
		return "Content/Models/" + modelName;
	}

	Model::Model(const std::string& filePath /*= ""*/) :
		m_filePath(filePath)
	{
	}

	Model::Model(const Model& other) :
		m_filePath(other.m_filePath)
	{
	}

	Model::~Model()
	{

	}

	Model& Model::operator=(const Model& other)
	{
		m_filePath = other.m_filePath;
		dirty();
		return *this;
	}

	std::string Model::TypeName()
	{
		return "Model";
	}

	std::string Model::typeName() const
	{
		return Model::TypeName();
	}

	serialisation::Serialisable* Model::clone() const
	{
		return new Model(*this);
	}

	Json::Value Model::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		data["filePath"] = m_filePath;
		return data;
	}

	void Model::deserialise(const Json::Value& data)
	{
		m_filePath = data["filePath"].asString();
		createMesh();
	}

	const std::string& Model::filePath() const
	{
		return m_filePath;
	}

	void Model::setFilePath(const std::string& filePath)
	{
		if (filePath != m_filePath)
		{
			m_filePath = filePath;
			dirty();
		}
	}

	void Model::createMesh()
	{
		m_vertexBuffer.reset(new VertexPositionUVNormalBuffer());
		VertexPositionUVNormalBuffer::BufferType& vBuffer = boost::dynamic_pointer_cast<VertexPositionUVNormalBuffer>(m_vertexBuffer)->data();
		vBuffer.clear();

		m_indexBuffer.reset(new IndexBuffer());
		IndexBuffer::BufferType& iBuffer = m_indexBuffer->data();
		iBuffer.clear();

		Assimp::Importer importer;

		std::string fullPath = ModelPath(m_filePath);

		const aiScene* scene = importer.ReadFile(
			fullPath,
			aiProcess_GenSmoothNormals |
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_SortByPType );

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
			if (mesh->HasPositions() && mesh->HasNormals() && mesh->HasTextureCoords(0))
			{
				for (uint v = 0; v < mesh->mNumVertices; ++v)
				{
					aiVector3D& position = mesh->mVertices[v];
					aiVector3D& normal = mesh->mNormals[v];
					aiVector3D& uvw = mesh->mTextureCoords[0][v];
					vBuffer[vertexOffset + v].position = Vector3(position.x, position.y, position.z);
					vBuffer[vertexOffset + v].normal = Vector3(normal.x, normal.y, normal.z);
					vBuffer[vertexOffset + v].uv = Vector2(uvw.x, uvw.y);
				}
			}
			else if (mesh->HasPositions() && mesh->HasNormals())
			{
				for (uint v = 0; v < mesh->mNumVertices; ++v)
				{
					aiVector3D& position = mesh->mVertices[v];
					aiVector3D& normal = mesh->mNormals[v];
					vBuffer[vertexOffset + v].position = Vector3(position.x, position.y, position.z);
					vBuffer[vertexOffset + v].normal = Vector3(normal.x, normal.y, normal.z);
				}
			}
			else if (mesh->HasPositions())
			{
				for (uint v = 0; v < mesh->mNumVertices; ++v)
				{
					aiVector3D& position = mesh->mVertices[v];
					vBuffer[vertexOffset + v].position = Vector3(position.x, position.y, position.z);
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

		m_vertexBuffer->dirty();
		m_indexBuffer->dirty();
	}
}
