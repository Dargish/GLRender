#include "Cube.h"
#include <json/json.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace serialisation;

namespace graphics
{
	Cube::Cube(float size /*= 1.0f*/, bool smooth /*= false*/ ) :
		m_size(size), m_smooth(smooth)
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

	void Cube::setSmooth(bool smooth)
	{
		m_smooth = smooth;
		createVertices();
		createIndices();
	}

	void Cube::createVertices()
	{
		m_vertexBuffer.reset(new VertexPositionNormalBuffer());
		if (m_smooth)
		{
			createSmoothVertices();
		}
		else
		{
			createFlatVertices();
		}
		m_vertexBuffer->dirty();
	}

	void Cube::createSmoothVertices()
	{
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
		}
	}

	void Cube::createFlatVertices()
	{
		VertexPositionNormalBuffer_Ptr vBuffer = boost::dynamic_pointer_cast<VertexPositionNormalBuffer>(m_vertexBuffer);
		VertexPositionNormalBuffer::BufferType& buffer = vBuffer->data();
		if (buffer.size() != 24)
		{
			buffer.resize(24);
		}
		size_t i = 0;
		Vector3 normal;
		float halfSize = m_size * 0.5f;

		// -X
		normal = Vector3(-1, 0, 0);
		buffer[i].position = Vector3(-halfSize, -halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(-halfSize, halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(-halfSize, -halfSize, halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(-halfSize, halfSize, halfSize);
		buffer[i++].normal = normal;

		// +X
		normal = Vector3(1, 0, 0);
		buffer[i].position = Vector3(halfSize, -halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, -halfSize, halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, halfSize, halfSize);
		buffer[i++].normal = normal;

		// -Y
		normal = Vector3(0, -1, 0);
		buffer[i].position = Vector3(-halfSize, -halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, -halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(-halfSize, -halfSize, halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, -halfSize, halfSize);
		buffer[i++].normal = normal;

		// +Y
		normal = Vector3(0, 1, 0);
		buffer[i].position = Vector3(-halfSize, halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(-halfSize, halfSize, halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, halfSize, halfSize);
		buffer[i++].normal = normal;

		// -Z
		normal = Vector3(0, 0, -1);
		buffer[i].position = Vector3(-halfSize, -halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, -halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(-halfSize, halfSize, -halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, halfSize, -halfSize);
		buffer[i++].normal = normal;

		// +Z
		normal = Vector3(0, 0, 1);
		buffer[i].position = Vector3(-halfSize, -halfSize, halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, -halfSize, halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(-halfSize, halfSize, halfSize);
		buffer[i++].normal = normal;
		buffer[i].position = Vector3(halfSize, halfSize, halfSize);
		buffer[i++].normal = normal;
	}

	void Cube::createIndices()
	{
		m_indexBuffer.reset(new IndexBuffer());
		if (m_smooth)
		{
			createSmoothIndices();
		}
		else
		{
			createFlatIndices();
		}
		m_indexBuffer->dirty();
	}

	void Cube::createSmoothIndices()
	{
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
	}

	void Cube::createFlatIndices()
	{
		IndexBuffer::BufferType& buffer = m_indexBuffer->data();
		if (buffer.size() != 36)
		{
			buffer.resize(36);
		}
		size_t i = 0;

		// -X
		buffer[i++] = 0;
		buffer[i++] = 2;
		buffer[i++] = 1;
		buffer[i++] = 2;
		buffer[i++] = 3;
		buffer[i++] = 1;

		// +X
		buffer[i++] = 4;
		buffer[i++] = 5;
		buffer[i++] = 6;
		buffer[i++] = 6;
		buffer[i++] = 5;
		buffer[i++] = 7;

		// -Y
		buffer[i++] = 8;
		buffer[i++] = 9;
		buffer[i++] = 10;
		buffer[i++] = 10;
		buffer[i++] = 9;
		buffer[i++] = 11;

		// +Y
		buffer[i++] = 12;
		buffer[i++] = 14;
		buffer[i++] = 13;
		buffer[i++] = 14;
		buffer[i++] = 15;
		buffer[i++] = 13;

		// -Z
		buffer[i++] = 16;
		buffer[i++] = 18;
		buffer[i++] = 17;
		buffer[i++] = 18;
		buffer[i++] = 19;
		buffer[i++] = 17;

		// +Z
		buffer[i++] = 20;
		buffer[i++] = 21;
		buffer[i++] = 22;
		buffer[i++] = 22;
		buffer[i++] = 21;
		buffer[i++] = 23;
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
		data["smooth"] = m_smooth;
		return data;
	}

	void Cube::deserialise(const Json::Value& data)
	{
		m_size = (float)data["size"].asDouble();
		m_smooth = data["smooth"].asBool();
		createVertices();
		createIndices();
	}
}
