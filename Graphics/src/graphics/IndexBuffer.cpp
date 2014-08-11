#include "IndexBuffer.h"
#include <GL/glew.h>

namespace graphics
{
	void IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer());
		if (isDirty())
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.size() * sizeof(uint), &m_data.front(), GL_STATIC_DRAW);
			clean();
		}
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::BufferType& IndexBuffer::data()
	{
		return m_data;
	}

	const IndexBuffer::BufferType& IndexBuffer::data() const
	{
		return m_data;
	}
}