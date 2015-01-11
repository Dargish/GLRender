#include "Cone.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include <json/json.h>
#include <core/MathUtils.h>

namespace graphics
{
	namespace primitives
	{
		Cone::Cone(float size /*= 1.0f*/, float angle /*= 45.0f*/, uint segments /*= 32*/) :
			m_size(size), m_angle(angle), m_segments(segments)
		{
		}

		Cone::Cone(const Cone& other) :
			m_size(other.m_size), m_angle(other.m_angle), m_segments(other.m_segments)
		{
		}

		Cone::~Cone()
		{

		}

		Cone& Cone::operator=(const Cone& other)
		{
			m_size = other.m_size;
			m_angle = other.m_angle;
			m_segments = other.m_segments;
			dirty();
			return *this;
		}

		std::string Cone::TypeName()
		{
			return "Cone";
		}

		std::string Cone::typeName() const
		{
			return Cone::TypeName();
		}

		serialisation::Serialisable* Cone::clone() const
		{
			return new Cone(*this);
		}

		Json::Value Cone::serialise() const
		{
			Json::Value data = Serialisable::serialise();
			data["size"] = m_size;
			data["angle"] = m_angle;
			data["segments"] = m_segments;
			return data;
		}

		void Cone::deserialise(const Json::Value& data)
		{
			m_size = (float)data["size"].asDouble();
			m_angle = (float)data["angle"].asDouble();
			m_segments = data["segments"].asUInt();
			dirty();
		}

		float Cone::size() const
		{
			return m_size;
		}

		float Cone::angle() const
		{
			return m_angle;
		}

		uint Cone::segments() const
		{
			return m_segments;
		}

		void Cone::setSize(float size)
		{
			if (size != m_size)
			{
				m_size = size;
				dirty();
			}
		}

		void Cone::setAngle(float angle)
		{
			if (angle != m_angle)
			{
				m_angle = angle;
				dirty();
			}
		}

		void Cone::setSegments(uint segments)
		{
			if (segments != m_segments)
			{
				m_segments = segments;
				dirty();
			}
		}

		void Cone::createMesh()
		{
			m_vertexBuffer.reset(new VertexPositionUVNormalBuffer());
			VertexPositionUVNormalBuffer::BufferType& vBuffer = boost::dynamic_pointer_cast<VertexPositionUVNormalBuffer>(m_vertexBuffer)->data();
			vBuffer.resize((m_segments) + (m_segments + 1));

			m_indexBuffer.reset(new IndexBuffer());
			IndexBuffer::BufferType& iBuffer = m_indexBuffer->data();
			iBuffer.resize(m_segments * 6);			

			uint vBottom = vBuffer.size() - 1;
			vBuffer[vBottom].position = Vector3(0.0f, 0.0f, m_size);
			vBuffer[vBottom].normal = Vector3(0.0f, 0.0f, 1.0f);
			vBuffer[vBottom].uv = Vector2(0.5f, 0.5f);
			
			float deltaPhi = PI2 / m_segments;
			float halfDeltaPhi = deltaPhi / 2.0;
			
			uint vTop = 0;
			vBuffer[vTop].normal = Vector3(0.0f, 0.0f, -1.0f);
			vBuffer[vTop].position = Vector3(0.0f, 0.0f, 0.0f);
			vBuffer[vTop].uv = Vector2(0.5f, 0.5f);

			float angleRads = degreesToRadians(m_angle);
			float radius = tan(angleRads);
			float theta = sin(angleRads);

			for (size_t s = 0; s < m_segments; ++s)
			{
				uint v1 = s + 1;
				float phi1 = deltaPhi * s;
				float x1 = cos(phi1);
				float z1 = sin(phi1);
				vBuffer[v1].normal.x = theta * x1;
				vBuffer[v1].normal.y = theta * z1;
				vBuffer[v1].normal.z = -theta;
				vBuffer[v1].normal = glm::normalize(vBuffer[v1].normal);
				vBuffer[v1].position.x = x1 * radius;
				vBuffer[v1].position.y = z1 * radius ;
				vBuffer[v1].position.z = m_size;
				vBuffer[v1].uv.x = (x1 + 1.0f) / 2.0f;
				vBuffer[v1].uv.y = (z1 + 1.0f) / 2.0f;
				
				uint v2 = (s == m_segments - 1) ? 1 : v1 + 1;

				uint v3 = v1 + m_segments;
				vBuffer[v3].position = vBuffer[v1].position;
				vBuffer[v3].normal = Vector3(0.0f, 0.0f, 1.0f);
				vBuffer[v3].uv = vBuffer[v1].uv;

				uint v4 = v2 + m_segments;

				uint i0 = s * 3;
				uint i1 = i0 + 1;
				uint i2 = i0 + 2;
				uint i3 = (m_segments + s) * 3;
				uint i4 = i3 + 1;
				uint i5 = i3 + 2;

				iBuffer[i0] = vTop;
				iBuffer[i1] = v2;
				iBuffer[i2] = v1;
				iBuffer[i3] = vBottom;
				iBuffer[i4] = v3;
				iBuffer[i5] = v4;
			}

			m_vertexBuffer->dirty();
			m_indexBuffer->dirty();
		}
	}
}