#include "Sphere.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <json/json.h>
#include <core/MathUtils.h>

using namespace serialisation;

namespace graphics
{
	Sphere::Sphere(float size /*= 1.0f*/, uint rings /*= 16*/, uint segments /*= 32*/) :
		m_size(size), m_rings(rings), m_segments(segments)
	{
	}

	Sphere::Sphere(const Sphere& other) :
		m_size(other.m_size), m_segments(other.m_segments), m_rings(other.m_rings)
	{
	}

	Sphere::~Sphere()
	{
	}

	Sphere& Sphere::operator= (const Sphere& other)		
	{
		m_size = other.m_size;
		m_segments = other.m_segments;
		m_rings = other.m_rings;
		dirty();
		return *this;
	}

	float Sphere::size() const
	{
		return m_size;
	}

	uint Sphere::rings() const
	{
		return m_rings;
	}

	uint Sphere::segments() const
	{
		return m_segments;
	}

	void Sphere::setSize(float size)
	{
		if (size != m_size)
		{
			m_size = size;
			dirty();
		}
	}

	void Sphere::setRings(uint rings)
	{
		if (rings != m_rings)
		{
			m_rings = rings;
			dirty();
		}
	}

	void Sphere::setSegments(uint segments)
	{
		if (segments != m_segments)
		{
			m_segments = segments;
			dirty();
		}
	}

	uint Sphere::indexOf(uint ring, uint segment) const
	{
		uint segmentOffset = 0;
		if (ring > 0)
		{
			segmentOffset = (ring * (m_segments + 1)) - 1;
		}
		return segmentOffset + segment;
	}

	void Sphere::createMesh()
	{
		m_vertexBuffer.reset(new VertexPositionUVNormalBuffer());
		VertexPositionUVNormalBuffer::BufferType& vBuffer = boost::dynamic_pointer_cast<VertexPositionUVNormalBuffer>(m_vertexBuffer)->data();
		vBuffer.resize((m_rings + 1) * (m_segments + 1) - 2);

		m_indexBuffer.reset(new IndexBuffer());
		IndexBuffer::BufferType& iBuffer = m_indexBuffer->data();
		iBuffer.resize((m_rings - 1) * m_segments * 6);

		size_t idx = 0;

		float halfSegmentU = 0.5f / m_segments;

		float deltaTheta = PI / m_rings;
		float deltaPhi = PI2 / m_segments;

		for (uint r = 0; r <= m_rings; ++r)
		{
			float theta = deltaTheta * r;
			for (uint s = 0; s <= m_segments; ++s)
			{
				float phi = deltaPhi * s;
				float uOffset = 0;
				if ((r == 0 || r == m_rings))
				{
					if (s == m_segments)
					{
						break;
					}
					uOffset = halfSegmentU;
				}
				uint v0 = indexOf(r, s);
				vBuffer[v0].normal.x = sin(theta) * cos(phi);
				vBuffer[v0].normal.z = sin(theta) * sin(phi);
				vBuffer[v0].normal.y = cos(theta);
				vBuffer[v0].normal = glm::normalize(vBuffer[v0].normal);
				vBuffer[v0].position = vBuffer[v0].normal * m_size;
				vBuffer[v0].uv.x = 1.0f - ( float(s) / m_segments + uOffset );
				vBuffer[v0].uv.y = float(r) / m_rings;

				if (r < m_rings && s < m_segments)
				{
					if (r == 0)
					{
						uint v1 = indexOf(r + 1, s + 1);
						uint v2 = indexOf(r + 1, s);
						iBuffer[idx++] = v0;
						iBuffer[idx++] = v1;
						iBuffer[idx++] = v2;
					}
					else if (r == m_rings - 1)
					{
						uint v1 = indexOf(r, s + 1);
						uint v2 = indexOf(r + 1, s);
						iBuffer[idx++] = v0;
						iBuffer[idx++] = v1;
						iBuffer[idx++] = v2;
					}
					else
					{
						uint v1 = indexOf(r, s + 1);
						uint v2 = indexOf(r + 1, s);
						uint v3 = indexOf(r + 1, s + 1);
						iBuffer[idx++] = v0;
						iBuffer[idx++] = v1;
						iBuffer[idx++] = v2;
						iBuffer[idx++] = v1;
						iBuffer[idx++] = v3;
						iBuffer[idx++] = v2;
					}
				}
			}
		}
		
		m_vertexBuffer->dirty();
		m_indexBuffer->dirty();
	}

	std::string Sphere::TypeName()
	{
		return "Sphere";
	}

	std::string Sphere::typeName() const
	{
		return Sphere::TypeName();
	}

	Serialisable* Sphere::clone() const
	{
		return new Sphere(*this);
	}

	Json::Value Sphere::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		data["size"] = m_size;
		data["rings"] = m_rings;
		data["segments"] = m_segments;
		return data;
	}

	void Sphere::deserialise(const Json::Value& data)
	{
		m_size = (float)data["size"].asDouble();
		m_rings = data["rings"].asUInt();
		m_segments = data["segments"].asUInt();
		dirty();
	}
}
