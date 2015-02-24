#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/Graphics/GlBuffer.h>

namespace glr
{
	template<class VERTEX_TYPE>
	class Mesh
	{
	public:
		typedef GlBuffer<VERTEX_TYPE> VertexBuffer;

		VertexBuffer& vertexBuffer()
		{
			return m_vertexBuffer;
		}

		IndexBuffer& IndexBuffer()
		{
			return m_indexBuffer;
		}

	private:
		VertexBuffer m_vertexBuffer;
		IndexBuffer m_indexBuffer;
	};
}