#include "Torus.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include <json/json.h>
#include <core/MathUtils.h>

using namespace serialisation;

namespace graphics
{
	namespace primitives
	{
		Torus::Torus(float size /*= 1.0f*/, float radius /*= 0.25f*/, uint rings /*= 16*/, uint segments /*= 32*/) :
			m_size(size), m_radius(radius), m_rings(rings), m_segments(segments)
		{
		}

		Torus::Torus(const Torus& other) :
			m_size(other.m_size), m_radius(other.m_radius), m_segments(other.m_segments), m_rings(other.m_rings)
		{
		}

		Torus::~Torus()
		{
		}

		Torus& Torus::operator= (const Torus& other)
		{
			m_size = other.m_size;
			m_radius = other.m_radius;
			m_segments = other.m_segments;
			m_rings = other.m_rings;
			dirty();
			return *this;
		}

		float Torus::size() const
		{
			return m_size;
		}

		float Torus::radius() const
		{
			return m_radius;
		}

		uint Torus::rings() const
		{
			return m_rings;
		}

		uint Torus::segments() const
		{
			return m_segments;
		}

		void Torus::setSize(float size)
		{
			if (size != m_size)
			{
				m_size = size;
				dirty();
			}
		}

		void Torus::setRadius(float radius)
		{
			if (radius != m_radius)
			{
				m_radius = radius;
				dirty();
			}
		}

		void Torus::setRings(uint rings)
		{
			if (rings != m_rings)
			{
				m_rings = rings;
				dirty();
			}
		}

		void Torus::setSegments(uint segments)
		{
			if (segments != m_segments)
			{
				m_segments = segments;
				dirty();
			}
		}

		uint Torus::indexOf(uint ring, uint segment) const
		{
			return ring * (m_segments + 1) + segment;
		}

		void Torus::createMesh()
		{
			m_vertexBuffer.reset(new VertexPositionUVNormalBuffer());
			VertexPositionUVNormalBuffer::BufferType& vBuffer = boost::dynamic_pointer_cast<VertexPositionUVNormalBuffer>(m_vertexBuffer)->data();
			vBuffer.resize((m_segments + 1) * (m_rings + 1));

			m_indexBuffer.reset(new IndexBuffer());
			IndexBuffer::BufferType& iBuffer = m_indexBuffer->data();
			iBuffer.resize(m_segments * m_rings * 6);

			size_t idx = 0;

			float size = m_size - m_radius;

			// http://gamedev.stackexchange.com/questions/16845/how-do-i-generate-a-torus-mesh
			for (uint r = 0; r <= m_rings; ++r)
			{
				for (uint s = 0; s <= m_segments; ++s)
				{
					uint v0 = indexOf(r, s);

					vBuffer[v0].uv.x = float(r) / float(m_rings);
					vBuffer[v0].uv.y = float(s) / float(m_segments);

					float u = vBuffer[v0].uv.x * PI2;
					float v = vBuffer[v0].uv.y * PI2;

					vBuffer[v0].uv.x = 1.0f - vBuffer[v0].uv.x;
					vBuffer[v0].uv.y = 1.0f - vBuffer[v0].uv.y;

					Vector3 W(std::cosf(u), 0, std::sinf(u));
					vBuffer[v0].normal = m_radius * std::cosf(v) * W + Vector3(0, m_radius * std::sinf(v), 0);
					vBuffer[v0].position = W * size + vBuffer[v0].normal;
					vBuffer[v0].normal = glm::normalize(vBuffer[v0].normal);

					if (r < m_rings && s < m_segments)
					{
						uint v1 = indexOf(r + 1, s);
						uint v2 = indexOf(r + 1, s + 1);
						uint v3 = indexOf(r, s + 1);
						iBuffer[idx++] = v0;
						iBuffer[idx++] = v2;
						iBuffer[idx++] = v1;

						iBuffer[idx++] = v2;
						iBuffer[idx++] = v0;
						iBuffer[idx++] = v3;
					}
				}
			}

			m_vertexBuffer->dirty();
			m_indexBuffer->dirty();
		}

		std::string Torus::TypeName()
		{
			return "Torus";
		}

		std::string Torus::typeName() const
		{
			return Torus::TypeName();
		}

		Serialisable* Torus::clone() const
		{
			return new Torus(*this);
		}

		Json::Value Torus::serialise() const
		{
			Json::Value data = Serialisable::serialise();
			data["size"] = m_size;
			data["radius"] = m_radius;
			data["rings"] = m_rings;
			data["segments"] = m_segments;
			return data;
		}

		void Torus::deserialise(const Json::Value& data)
		{
			m_size = (float)data["size"].asDouble();
			m_radius = (float)data["radius"].asDouble();
			m_rings = data["rings"].asUInt();
			m_segments = data["segments"].asUInt();
			dirty();
		}
	}
}