#include <GLRender/Graphics/GlBuffer.h>

namespace glr
{
	BaseGlBuffer::BaseGlBuffer() :
		m_buffer(0)
	{
		glGenBuffers(1, &m_buffer);
	}

	BaseGlBuffer::~BaseGlBuffer()
	{
		glDeleteBuffers(1, &m_buffer);
	}

	void BaseGlBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	}

	void BaseGlBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}