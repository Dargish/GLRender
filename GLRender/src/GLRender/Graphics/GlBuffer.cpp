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
		glBindBuffer(bufferType(), m_buffer);
	}

	void BaseGlBuffer::unbind() const
	{
		glBindBuffer(bufferType(), 0);
	}


	IndexBuffer::IndexBuffer()
	{

	}

	IndexBuffer::IndexBuffer(typename GlBuffer<uint>::size_type size) :
		GlBuffer<uint>(size)
	{
		
	}

	uint IndexBuffer::bufferType() const
	{
		return GL_ELEMENT_ARRAY_BUFFER;
	}
}