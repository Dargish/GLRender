#include "Primitive.h"
#include <GL/glew.h>

namespace graphics
{
	Primitive::Primitive() :
		m_vertexBufferDirty(true),
		m_indexBufferDirty(true)
	{
	}

	Primitive::~Primitive()
	{

	}

	std::vector<Vector3>& Primitive::vertices()
	{
		return m_vertices;
	}

	const std::vector<Vector3>& Primitive::vertices() const
	{
		return m_vertices;
	}

	std::vector<sf::Uint32>& Primitive::indices()
	{
		return m_indices;
	}

	const std::vector<sf::Uint32>& Primitive::indices() const
	{
		return m_indices;
	}

	void Primitive::draw(float deltaTime)
	{
		if (m_vertexBufferDirty)
		{
			rebuildVertexBuffer();
		}
		if (m_indexBufferDirty)
		{
			rebuildIndexBuffer();
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferVertices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIndices);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
		glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_INT, (GLvoid*)(8 * sizeof(sf::Uint32)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);
	}

	void Primitive::dirtyVertexBuffer()
	{
		m_vertexBufferDirty = true;
	}

	void Primitive::dirtyIndexBuffer()
	{
		m_indexBufferDirty = true;
	}

	void Primitive::rebuildVertexBuffer()
	{
		glGenBuffers(1, &m_bufferVertices);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferVertices);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vector3), &m_vertices.front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Primitive::rebuildIndexBuffer()
	{
		glGenBuffers(1, &m_bufferIndices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferIndices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(sf::Uint32), &m_indices.front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}