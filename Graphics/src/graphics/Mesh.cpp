#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace graphics
{
	Mesh::Mesh() :
		m_isDirty(true)
	{
	}

	Mesh::~Mesh()
	{

	}

	VertexBuffer_Ptr Mesh::vertexBuffer()
	{
		return m_vertexBuffer;
	}

	VertexBuffer_Const_Ptr Mesh::vertexBuffer() const
	{
		return m_vertexBuffer;
	}

	IndexBuffer_Ptr Mesh::indexBuffer()
	{
		return m_indexBuffer;
	}

	IndexBuffer_Const_Ptr Mesh::indexBuffer() const
	{
		return m_indexBuffer;
	}

	void Mesh::draw(float deltaTime)
	{
		checkDirty();
		if (m_vertexBuffer->empty() || m_indexBuffer->empty())
		{
			return;
		}
		m_vertexBuffer->bind();
		m_indexBuffer->bind();
		glDrawElements(geometryType(), m_indexBuffer->data().size(), GL_UNSIGNED_INT, 0);
		m_indexBuffer->unbind();
		m_vertexBuffer->unbind();
	}

	void Mesh::dirty()
	{
		m_isDirty = true;
	}

	void Mesh::checkDirty()
	{
		if (m_isDirty)
		{
			createMesh();
			m_isDirty = false;
		}
	}

	uint Mesh::geometryType()
	{
		return GL_TRIANGLES;
	}
}