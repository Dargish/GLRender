#include "GLBuffer.h"
#include <GL/glew.h>

namespace graphics
{
	GLBuffer::GLBuffer() :
		m_buffer(0), m_dirty(true)
	{
		
	}

	GLBuffer::~GLBuffer()
	{
	}

	uint GLBuffer::buffer()
	{
		if (m_buffer == 0)
		{
			m_buffer = generateBuffer();
		}
		return m_buffer;
	}

	uint GLBuffer::generateBuffer()
	{
		uint buf = 0;
		glGenBuffers(1, &buf);
		return buf;
	}

	void GLBuffer::deleteBuffer()
	{
		glDeleteBuffers(1, &m_buffer);
		m_buffer = 0;
	}

	void GLBuffer::dirty()
	{
		m_dirty = true;
	}

	void GLBuffer::clean()
	{
		m_dirty = false;
	}

	bool GLBuffer::isDirty()
	{
		return m_dirty;
	}
}