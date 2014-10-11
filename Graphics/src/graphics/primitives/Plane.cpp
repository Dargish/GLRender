#include "Plane.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include <json/json.h>

namespace graphics
{
	namespace primitives
	{
		Plane::Plane(float size /*= 1.0f*/) :
			m_size(size)
		{
		}

		Plane::Plane(const Plane& other) :
			m_size(other.m_size)
		{
		}

		Plane::~Plane()
		{

		}

		Plane& Plane::operator=(const Plane& other)
		{
			m_size = other.m_size;
			dirty();
			return *this;
		}

		std::string Plane::TypeName()
		{
			return "Plane";
		}

		std::string Plane::typeName() const
		{
			return Plane::TypeName();
		}

		serialisation::Serialisable* Plane::clone() const
		{
			return new Plane(*this);
		}

		Json::Value Plane::serialise() const
		{
			Json::Value data = Serialisable::serialise();
			data["size"] = m_size;
			return data;
		}

		void Plane::deserialise(const Json::Value& data)
		{
			m_size = (float)data["size"].asDouble();
			dirty();
		}

		float Plane::size() const
		{
			return m_size;
		}

		void Plane::setSize(float size)
		{
			if (size != m_size)
			{
				m_size = size;
				dirty();
			}
		}

		void Plane::createMesh()
		{
			m_vertexBuffer.reset(new VertexPositionUVNormalBuffer());
			VertexPositionUVNormalBuffer::BufferType& vBuffer = boost::dynamic_pointer_cast<VertexPositionUVNormalBuffer>(m_vertexBuffer)->data();
			vBuffer.clear();

			m_indexBuffer.reset(new IndexBuffer());
			IndexBuffer::BufferType& iBuffer = m_indexBuffer->data();
			iBuffer.clear();

			Vector3 normal(0.0f, 1.0f, 0.0f);

			// Vertex 0:
			VertexPositionUVNormal v0;
			v0.position = Vector3(-m_size, m_size, 0);
			v0.uv = Vector2(0.001f, 0.001f);
			v0.normal = normal;
			vBuffer.push_back(v0);

			// Vertex 1:
			VertexPositionUVNormal v1;
			v1.position = Vector3(-m_size, -m_size, 0);
			v1.uv = Vector2(0.001f, 0.999f);
			v1.normal = normal;
			vBuffer.push_back(v1);

			// Vertex 2:
			VertexPositionUVNormal v2;
			v2.position = Vector3(m_size, m_size, 0);
			v2.uv = Vector2(0.999f, 0.001f);
			v2.normal = normal;
			vBuffer.push_back(v2);

			// Vertex 3:
			VertexPositionUVNormal v3;
			v3.position = Vector3(m_size, -m_size, 0);
			v3.uv = Vector2(0.999f, 0.999f);
			v3.normal = normal;
			vBuffer.push_back(v3);

			// Bottom Right Triangle
			iBuffer.push_back(0);
			iBuffer.push_back(1);
			iBuffer.push_back(2);

			// Top Left Triangle
			iBuffer.push_back(2);
			iBuffer.push_back(1);
			iBuffer.push_back(3);

			m_vertexBuffer->dirty();
			m_indexBuffer->dirty();
		}
	}
}