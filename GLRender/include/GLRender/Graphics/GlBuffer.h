#pragma once

#include <GLRender/DataTypes.h>

#include <vector>

namespace glr
{
	class BaseGlBuffer
	{
	public:
		virtual ~BaseGlBuffer()
		{

		}
	};

	template<class ELEMENT_TYPE>
	class GlBuffer : public BaseGlBuffer
	{
	public:
		typedef ELEMENT_TYPE element_type;
		typedef std::vector<element_type> buffer_type;
		typedef typename buffer_type::size_type size_type;
		static const size_t Stride = sizeof(element_type);

		GlBuffer()
		{

		}

		virtual ~GlBuffer()
		{

		}

		GlBuffer(size_type size) :
			m_buffer(size)
		{

		}

		// Movable
		GlBuffer(GlBuffer&& o)
		{
			m_buffer = std::move(o.m_buffer);
		}

		GlBuffer& operator=(GlBuffer&& o)
		{
			m_buffer = std::move(o.m_buffer);
			return *this;
		}
		
		// Commented out, needs to go in a vector
		// Noncopyable
	    //GlBuffer(const GlBuffer&) = delete;
	    //GlBuffer& operator=(const GlBuffer&) = delete;

		element_type* data()
		{
			return &m_buffer.front();
		}

		size_type size()
		{
			return m_buffer.size();
		}

		void resize(size_type size)
		{
			m_buffer.resize(size);
		}

		element_type& operator[](size_type i)
		{
			return m_buffer[i];
		}

		const element_type& operator[](size_type i) const
		{
			return m_buffer[i];
		}

	private:
		buffer_type m_buffer;
	};

	typedef GlBuffer<uint> IndexBuffer;
}