#include "Cube.h"
#include <json/json.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

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
		m_vertexBuffer.reset(new VertexPositionNormalBuffer());
		VertexPositionNormalBuffer_Ptr vBuffer = boost::dynamic_pointer_cast<VertexPositionNormalBuffer>(m_vertexBuffer);
		VertexPositionNormalBuffer::BufferType& buffer = vBuffer->data();
		if (buffer.size() != 8)
		{
			buffer.resize(8);
		}
		float halfSize = m_size * 0.5f;
		for (size_t i = 0; i < 8; ++i)
		{
			buffer[i].position = Vector3(i & 1 ? -halfSize : halfSize, i & 2 ? -halfSize : halfSize, i & 4 ? -halfSize : halfSize);
			buffer[i].normal = glm::normalize(buffer[i].position);
			//glm::normalize(buffer[i].normal);
		}
		m_vertexBuffer->dirty();
	}

	void Cube::createIndices()
	{
		m_indexBuffer.reset(new IndexBuffer());
		IndexBuffer::BufferType& buffer = m_indexBuffer->data();
		if (buffer.size() != 36)
		{
			buffer.resize(36);
		}
		size_t i = 0;

		// -X
		buffer[i++] = 4;
		buffer[i++] = 0;
		buffer[i++] = 6;
		buffer[i++] = 6;
		buffer[i++] = 0;
		buffer[i++] = 2;

		// +X
		buffer[i++] = 1;
		buffer[i++] = 5;
		buffer[i++] = 3;
		buffer[i++] = 3;
		buffer[i++] = 5;
		buffer[i++] = 7;

		// -Y
		buffer[i++] = 0;
		buffer[i++] = 1;
		buffer[i++] = 2;
		buffer[i++] = 2;
		buffer[i++] = 1;
		buffer[i++] = 3;

		// +Y
		buffer[i++] = 5;
		buffer[i++] = 4;
		buffer[i++] = 7;
		buffer[i++] = 7;
		buffer[i++] = 4;
		buffer[i++] = 6;

		// -Z
		buffer[i++] = 2;
		buffer[i++] = 3;
		buffer[i++] = 6;
		buffer[i++] = 6;
		buffer[i++] = 3;
		buffer[i++] = 7;

		// +Z
		buffer[i++] = 5;
		buffer[i++] = 1;
		buffer[i++] = 0;
		buffer[i++] = 0;
		buffer[i++] = 4;
		buffer[i++] = 5;

		m_indexBuffer->dirty();
	}

	std::string Cube::TypeName()
	{
		return "Cube";
	}

	std::string Cube::typeName() const
	{
		return Cube::TypeName();
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
