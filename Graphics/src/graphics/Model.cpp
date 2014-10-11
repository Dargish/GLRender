#include "Model.h"
#include <json/json.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "loaders/AssimpModelLoader.h"

using namespace graphics::loaders;

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
		dirty();
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
		AssimpModelLoader loader;
		loader.load(ModelPath(m_filePath), m_vertexBuffer, m_indexBuffer);
	}
}
