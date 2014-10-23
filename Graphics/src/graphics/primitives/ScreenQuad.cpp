#include "ScreenQuad.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../Camera.h"
#include <json/json.h>

namespace graphics
{
	namespace primitives
	{
		ScreenQuad::ScreenQuad()
		{
		}

		ScreenQuad::ScreenQuad(const ScreenQuad& other)
		{
		}

		ScreenQuad::~ScreenQuad()
		{

		}

		ScreenQuad& ScreenQuad::operator=(const ScreenQuad& other)
		{
			return *this;
		}

		std::string ScreenQuad::TypeName()
		{
			return "ScreenQuad";
		}

		std::string ScreenQuad::typeName() const
		{
			return ScreenQuad::TypeName();
		}

		serialisation::Serialisable* ScreenQuad::clone() const
		{
			return new ScreenQuad(*this);
		}

		Json::Value ScreenQuad::serialise() const
		{
			Json::Value data = Serialisable::serialise();
			return data;
		}

		void ScreenQuad::deserialise(const Json::Value& data)
		{

		}

		void ScreenQuad::createMesh()
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
			v0.position = Vector3(-1.0f, -1.0f, 0);
			v0.uv = Vector2(0.0f, 0.0f);
			v0.normal = normal;
			vBuffer.push_back(v0);

			// Vertex 1:
			VertexPositionUVNormal v1;
			v1.position = Vector3(1.0f, -1.0f, 0);
			v1.uv = Vector2(1.0f, 0.0f);
			v1.normal = normal;
			vBuffer.push_back(v1);

			// Vertex 2:
			VertexPositionUVNormal v2;
			v2.position = Vector3(-1.0f, 1.0f, 0);
			v2.uv = Vector2(0.0f, 1.0f);
			v2.normal = normal;
			vBuffer.push_back(v2);

			// Vertex 3:
			VertexPositionUVNormal v3;
			v3.position = Vector3(1.0f, 1.0f, 0);
			v3.uv = Vector2(1.0f, 1.0f);
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

		void ScreenQuad::setEyeVec(const Camera_Ptr& camera)
		{
			checkDirty();
			VertexPositionUVNormalBuffer::BufferType& vBuffer = boost::dynamic_pointer_cast<VertexPositionUVNormalBuffer>(m_vertexBuffer)->data();
			Frustum frustum = camera->frustum();
			for (size_t i = 0; i < 4; ++i)
			{
				vBuffer[i].position = frustum.corners[i];// +(frustum.corners[i + 4] - frustum.corners[i]) * 0.001f;
			}
			m_vertexBuffer->dirty();
		}
	}
}