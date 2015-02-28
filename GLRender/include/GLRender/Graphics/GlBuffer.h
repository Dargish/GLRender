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

		GlBuffer();
		GlBuffer(size_type size);
		virtual ~GlBuffer();

		// Movable
		GlBuffer(GlBuffer&& o);
		GlBuffer& operator=(GlBuffer&& o);
		
		// Commented out, needs to go in a vector
		// Noncopyable
	    //GlBuffer(const GlBuffer&) = delete;
	    //GlBuffer& operator=(const GlBuffer&) = delete;

		element_type* data();

		size_type size();
		void resize(size_type size);

		element_type& operator[](size_type i);
		const element_type& operator[](size_type i) const;

	private:
		buffer_type m_buffer;
	};

	template<class ELEMENT_TYPE>
	GlBuffer<ELEMENT_TYPE>::GlBuffer()
	{

	}

	template<class ELEMENT_TYPE>
	GlBuffer<ELEMENT_TYPE>::GlBuffer(typename GlBuffer<ELEMENT_TYPE>::size_type size) :
		m_buffer(size)
	{

	}

	template<class ELEMENT_TYPE>
	GlBuffer<ELEMENT_TYPE>::~GlBuffer()
	{

	}

	// Movable
	template<class ELEMENT_TYPE>
	GlBuffer<ELEMENT_TYPE>::GlBuffer(GlBuffer<ELEMENT_TYPE>&& o)
	{
		m_buffer = std::move(o.m_buffer);
	}

	template<class ELEMENT_TYPE>
	GlBuffer<ELEMENT_TYPE>& GlBuffer<ELEMENT_TYPE>::operator=(GlBuffer<ELEMENT_TYPE>&& o)
	{
		m_buffer = std::move(o.m_buffer);
		return *this;
	}

	template<class ELEMENT_TYPE>
	typename GlBuffer<ELEMENT_TYPE>::element_type* GlBuffer<ELEMENT_TYPE>::data()
	{
		return &m_buffer.front();
	}

	template<class ELEMENT_TYPE>
	typename GlBuffer<ELEMENT_TYPE>::size_type GlBuffer<ELEMENT_TYPE>::size()
	{
		return m_buffer.size();
	}

	template<class ELEMENT_TYPE>
	void GlBuffer<ELEMENT_TYPE>::resize(size_type size)
	{
		m_buffer.resize(size);
	}

	template<class ELEMENT_TYPE>
	typename GlBuffer<ELEMENT_TYPE>::element_type& GlBuffer<ELEMENT_TYPE>::operator[](size_type i)
	{
		return m_buffer[i];
	}

	template<class ELEMENT_TYPE>
	const typename GlBuffer<ELEMENT_TYPE>::element_type& GlBuffer<ELEMENT_TYPE>::operator[](size_type i) const
	{
		return m_buffer[i];
	}

	typedef GlBuffer<uint> IndexBuffer;
}