#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/Graphics/GlBuffer.h>

namespace glr
{
	class GLRENDERAPI BaseMesh
	{
	public:
		virtual ~BaseMesh();

		IndexBuffer& indexBuffer();

	protected:
		IndexBuffer m_indexBuffer;
	};

	template<class VERTEX_TYPE>
	class GLRENDERAPI Mesh : public BaseMesh
	{
	public:
		typedef GlBuffer<VERTEX_TYPE> VertexBuffer;

		VertexBuffer& vertexBuffer();

	protected:
		VertexBuffer m_vertexBuffer;
	};

	template<class VERTEX_TYPE>
	typename Mesh<VERTEX_TYPE>::VertexBuffer& Mesh<VERTEX_TYPE>::vertexBuffer()
	{
		return m_vertexBuffer;
	}
}