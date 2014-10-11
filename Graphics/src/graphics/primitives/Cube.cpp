#include "Cube.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include <json/json.h>

using namespace serialisation;

namespace graphics
{
	namespace primitives
	{
		Cube::Cube(float size /*= 1.0f*/, bool smooth /*= false*/) :
			m_size(size), m_smooth(smooth)
		{
		}

		Cube::Cube(const Cube& other) :
			m_size(other.m_size), m_smooth(other.m_smooth)
		{
		}

		Cube::~Cube()
		{
		}

		Cube& Cube::operator= (const Cube& other)
		{
			m_size = other.m_size;
			m_smooth = other.m_smooth;
			dirty();
			return *this;
		}

		float Cube::size() const
		{
			return m_size;
		}

		bool Cube::smooth() const
		{
			return m_smooth;
		}

		void Cube::setSize(float size)
		{
			if (size != m_size)
			{
				m_size = size;
				dirty();
			}
		}

		void Cube::setSmooth(bool smooth)
		{
			if (smooth != m_smooth)
			{
				m_smooth = smooth;
				dirty();
			}
		}

		void createFace(
			VertexPositionUVNormalBuffer::BufferType& vBuffer,
			IndexBuffer::BufferType& iBuffer,
			const Vector3& normal,
			float size)
		{
			size_t indexOffset = vBuffer.size();

			Vector3 up(0.0f, 1.0f, 0.0f);
			if (normal == up || normal == -up)
			{
				up = Vector3(1.0f, 0.0f, 0.0f);
			}
			Vector3 side = glm::cross(normal, up);

			Vector3 front = normal * size;
			up *= size;
			side *= size;

			// Vertex 0:
			VertexPositionUVNormal v0;
			v0.position = front - side - up;
			v0.uv = Vector2(0.999f, 0.999f);
			v0.normal = normal;
			vBuffer.push_back(v0);

			// Vertex 1:
			VertexPositionUVNormal v1;
			v1.position = front - side + up;
			v1.uv = Vector2(0.999f, 0.001f);
			v1.normal = normal;
			vBuffer.push_back(v1);

			// Vertex 2:
			VertexPositionUVNormal v2;
			v2.position = front + side - up;
			v2.uv = Vector2(0.001f, 0.999f);
			v2.normal = normal;
			vBuffer.push_back(v2);

			// Vertex 3:
			VertexPositionUVNormal v3;
			v3.position = front + side + up;
			v3.uv = Vector2(0.001f, 0.001f);
			v3.normal = normal;
			vBuffer.push_back(v3);

			// Bottom Right Triangle
			iBuffer.push_back(indexOffset + 0);
			iBuffer.push_back(indexOffset + 1);
			iBuffer.push_back(indexOffset + 2);

			// Top Left Triangle
			iBuffer.push_back(indexOffset + 2);
			iBuffer.push_back(indexOffset + 1);
			iBuffer.push_back(indexOffset + 3);
		}

		void Cube::createMesh()
		{
			m_vertexBuffer.reset(new VertexPositionUVNormalBuffer());
			VertexPositionUVNormalBuffer::BufferType& vBuffer = boost::dynamic_pointer_cast<VertexPositionUVNormalBuffer>(m_vertexBuffer)->data();
			vBuffer.clear();

			m_indexBuffer.reset(new IndexBuffer());
			IndexBuffer::BufferType& iBuffer = m_indexBuffer->data();
			iBuffer.clear();

			createFace(vBuffer, iBuffer, Vector3(-1, 0, 0), m_size);
			createFace(vBuffer, iBuffer, Vector3(1, 0, 0), m_size);
			createFace(vBuffer, iBuffer, Vector3(0, -1, 0), m_size);
			createFace(vBuffer, iBuffer, Vector3(0, 1, 0), m_size);
			createFace(vBuffer, iBuffer, Vector3(0, 0, -1), m_size);
			createFace(vBuffer, iBuffer, Vector3(0, 0, 1), m_size);

			if (m_smooth)
			{
				VertexPositionUVNormalBuffer::BufferType::iterator it = vBuffer.begin();
				for (; it != vBuffer.end(); ++it)
				{
					it->normal = glm::normalize(it->position);
				}
			}

			m_vertexBuffer->dirty();
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
			data["smooth"] = m_smooth;
			return data;
		}

		void Cube::deserialise(const Json::Value& data)
		{
			m_size = (float)data["size"].asDouble();
			m_smooth = data["smooth"].asBool();
			dirty();
		}
	}
}