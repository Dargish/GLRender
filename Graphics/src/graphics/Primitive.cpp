#include "Primitive.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace graphics
{
	Primitive::Primitive()
	{
	}

	Primitive::~Primitive()
	{

	}

	VertexBuffer_Ptr Primitive::vertexBuffer()
	{
		return m_vertexBuffer;
	}

	VertexBuffer_Const_Ptr Primitive::vertexBuffer() const
	{
		return m_vertexBuffer;
	}

	IndexBuffer_Ptr Primitive::indexBuffer()
	{
		return m_indexBuffer;
	}

	IndexBuffer_Const_Ptr Primitive::indexBuffer() const
	{
		return m_indexBuffer;
	}

	void Primitive::draw(float deltaTime)
	{
		m_vertexBuffer->bind();
		m_indexBuffer->bind();
		glDrawElements(GL_TRIANGLES, m_indexBuffer->data().size(), GL_UNSIGNED_INT, 0);
		m_indexBuffer->unbind();
		m_vertexBuffer->unbind();
	}
}