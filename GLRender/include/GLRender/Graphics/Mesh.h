#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/Graphics/GlBuffer.h>
#include <GL/glew.h>

namespace glr
{
	class GLRENDERAPI BaseMesh
	{
	public:
		virtual ~BaseMesh();

		virtual void draw() const = 0;

		IndexBuffer& indexBuffer();

	protected:
		IndexBuffer m_indexBuffer;
	};

	template<class VERTEX_TYPE>
	class Mesh : public BaseMesh
	{
	public:
		typedef BaseVertexBuffer<VERTEX_TYPE> VertexBuffer;

		virtual void draw() const;

		VertexBuffer& vertexBuffer();

	protected:
		VertexBuffer m_vertexBuffer;
	};

	template<class VERTEX_TYPE>
	void Mesh<VERTEX_TYPE>::draw() const
	{
		m_vertexBuffer.bind();
		m_indexBuffer.bind();
		glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
		m_indexBuffer.unbind();
		m_vertexBuffer.unbind();
	}

	template<class VERTEX_TYPE>
	typename Mesh<VERTEX_TYPE>::VertexBuffer& Mesh<VERTEX_TYPE>::vertexBuffer()
	{
		return m_vertexBuffer;
	}
}