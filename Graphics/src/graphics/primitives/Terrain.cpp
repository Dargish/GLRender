#include "Terrain.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include <json/json.h>

namespace graphics
{
	namespace primitives
	{
		Terrain::Terrain(int subdivision /*= 4*/) :
			m_subdivision(subdivision)
		{
		}

		Terrain::Terrain(const Terrain& other) :
			m_subdivision(other.m_subdivision)
		{
		}

		Terrain::~Terrain()
		{

		}

		Terrain& Terrain::operator=(const Terrain& other)
		{
			if (m_subdivision != other.m_subdivision)
			{
				m_subdivision = other.m_subdivision;
				dirty();
			}
			return *this;
		}

		std::string Terrain::TypeName()
		{
			return "Terrain";
		}

		std::string Terrain::typeName() const
		{
			return Terrain::TypeName();
		}

		serialisation::Serialisable* Terrain::clone() const
		{
			return new Terrain(*this);
		}

		Json::Value Terrain::serialise() const
		{
			Json::Value data = Serialisable::serialise();
			data["subdivision"] = m_subdivision;
			return data;
		}

		void Terrain::deserialise(const Json::Value& data)
		{
			m_subdivision = (uint)data["subdivision"].asUInt();
			dirty();
		}
		
		void Terrain::createMesh()
		{
			uint size = uint(std::pow(2, m_subdivision) + 1);
			uint vertCount = size * size;
			uint indexCount = size * size + (size - 1) * (size - 2);

			m_vertexBuffer.reset(new VertexPositionUVNormalBuffer());
			VertexPositionUVNormalBuffer::BufferType& vBuffer = boost::dynamic_pointer_cast<VertexPositionUVNormalBuffer>(m_vertexBuffer)->data();
			vBuffer.resize(vertCount);

			m_indexBuffer.reset(new IndexBuffer());
			IndexBuffer::BufferType& iBuffer = m_indexBuffer->data();
			iBuffer.resize(indexCount);

			int i = 0;
			float worldSize = 25.0f;
			float tiling = 25.0f;
			float delta = 1.0f / float(size);
			for (uint row = 0; row<size; row++)
			{
				for (uint col = 0; col<size; col++)
				{
					VertexPositionUVNormal& vertex = vBuffer[i++];
					
					vertex.uv.x = (float)col / float(size);
					vertex.uv.y = (float)row / float(size);

					vertex.position.x = vertex.uv.x * worldSize;
					vertex.position.y = heightAt(vertex.uv.x, vertex.uv.y);
					vertex.position.z = vertex.uv.y * worldSize;

					float hL = heightAt(vertex.uv.x - delta, vertex.uv.y);
					float hR = heightAt(vertex.uv.x + delta, vertex.uv.y);
					float hD = heightAt(vertex.uv.x, vertex.uv.y - delta);
					float hU = heightAt(vertex.uv.x, vertex.uv.y + delta);

					// deduce terrain normal
					vertex.normal.x = hL - hR;
					vertex.normal.y = 2.0f;
					vertex.normal.z = hD - hU;
					vertex.normal = glm::normalize(vertex.normal);

					vertex.uv.x *= tiling;
					vertex.uv.y *= tiling;
				}
			}

			i = 0;
			for (uint row = 0; row < size - 1; row++)
			{
				if ((row & 1) == 0)
				{
					// even rows
					for (uint col = 0; col < size; col++)
					{
						iBuffer[i++] = (col + row * size);
						iBuffer[i++] = (col + (row + 1) * size);
					}
				}
				else
				{
					// odd rows
					for (uint col = size - 1; col > 0; col--)
					{
						iBuffer[i++] = (col + (row + 1) * size);
						iBuffer[i++] = (col - 1 + row * size);
					}
				}
			}
			if ((size & 1) && size > 2)
			{
				iBuffer[i++] = (size - 1) * size;
			}

			m_vertexBuffer->dirty();
			m_indexBuffer->dirty();
		}

		int Terrain::subdivision() const
		{
			return m_subdivision;
		}

		void Terrain::setSubdivision(int subdivision)
		{
			if (subdivision != m_subdivision)
			{
				m_subdivision = subdivision;
				dirty();
			}
		}

		uint Terrain::geometryType()
		{
			return GL_TRIANGLE_STRIP;
		}

		float Terrain::heightAt(float x, float y) const
		{
			return (std::sinf(x * 50.0f) + std::cosf(y * 25.0f) + std::sinf(y * x * 75.0f)) * 0.25f;
		}
	}
}
