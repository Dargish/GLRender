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

	void BaseGlBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	}

	void BaseGlBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexHandler::VertexHandler(uint stride) :
		m_stride(stride), m_offset(0), m_count(0)
	{

	}

	VertexEnabler::VertexEnabler(uint stride) :
		VertexHandler(stride)
	{

	}
	
	template<>
	VertexEnabler& VertexEnabler::attrib<Vector2>()
	{
		glEnableVertexAttribArray(m_count++);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, m_stride, (void*)m_offset);
		m_offset += sizeof(Vector2);
		return *this;
	}

	template<>
	VertexEnabler& VertexEnabler::attrib<Vector3>()
	{
		glEnableVertexAttribArray(m_count++);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_stride, (void*)m_offset);
		m_offset += sizeof(Vector3);
		return *this;
	}

	VertexDisabler::VertexDisabler(uint stride) :
		VertexHandler(stride)
	{

	}

	template<>
	VertexDisabler& VertexDisabler::attrib<Vector2>()
	{
		glDisableVertexAttribArray(m_count++);
		return *this;
	}

	template<>
	VertexDisabler& VertexDisabler::attrib<Vector3>()
	{
		glDisableVertexAttribArray(m_count++);
		return *this;
	}
}