#include "Cube.h"
#include <json/json.h>

using namespace serialisation;

namespace graphics
{
	Cube::Cube(float size /*= 1.0f*/) :
		m_size(size)
	{
		createVertices();
		createIndices();
	}

	Cube::Cube(const Cube& other) :
		m_size(other.m_size)
	{
		createVertices();
		createIndices();
	}

	Cube::~Cube()
	{
	}

	Cube& Cube::operator= (const Cube& other)		
	{
		resize(other.m_size);
		return *this;
	}

	void Cube::resize(float size)
	{
		if (size != m_size)
		{
			m_size = size;
			createVertices();
		}
	}

	void Cube::createVertices()
	{
		if (m_vertices.size() != 8)
		{
			m_vertices.resize(8);
		}
		float halfSize = m_size * 0.5f;
		for (size_t i = 0; i < 8; ++i)
		{
			m_vertices[i] = Vector3(i & 1 ? -halfSize : halfSize, i & 2 ? -halfSize : halfSize, i & 4 ? -halfSize : halfSize);
		}
		dirtyVertexBuffer();
	}

	void Cube::createIndices()
	{
		if (m_indices.size() != 16)
		{
			m_indices.resize(16);
		}
		m_indices[0] = 7;
		m_indices[1] = 5;
		m_indices[2] = 6;
		m_indices[3] = 4;
		m_indices[4] = 2;
		m_indices[5] = 0;
		m_indices[6] = 3;
		m_indices[7] = 1;
		m_indices[8] = 0;
		m_indices[9] = 4;
		m_indices[10] = 1;
		m_indices[11] = 5;
		m_indices[12] = 3;
		m_indices[13] = 7;
		m_indices[14] = 2;
		m_indices[15] = 6;
		dirtyIndexBuffer();
	}

	std::string Cube::typeName() const
	{
		return "Cube";
	}

	Serialisable* Cube::clone() const
	{
		return new Cube(*this);
	}

	Json::Value Cube::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		data["size"] = m_size;
		return data;
	}

	void Cube::deserialise(const Json::Value& data)
	{
		resize((float)data["size"].asDouble());
	}
}
