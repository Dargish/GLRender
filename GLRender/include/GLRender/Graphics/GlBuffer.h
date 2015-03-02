#pragma once

#include <GLRender/DataTypes.h>

#include <vector>

#include <GL/glew.h>

namespace glr
{
	class GLRENDERAPI BaseGlBuffer
	{
	public:
		BaseGlBuffer();
		virtual ~BaseGlBuffer();

		virtual void bind();
		virtual void unbind();

	private:
		uint m_buffer;
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

		void copyToGPU();

		element_type* data();

		size_type size();
		void resize(size_type size);

		element_type& operator[](size_type i);
		const element_type& operator[](size_type i) const;

	private:
		buffer_type m_data;
	};

	template<class ELEMENT_TYPE>
	class VertexBuffer : public GlBuffer<ELEMENT_TYPE>
	{
		VertexBuffer();
		VertexBuffer(size_type size);
		virtual ~VertexBuffer();

		virtual void bind();
		virtual void unbind();
	};

	template<class ELEMENT_TYPE>
	GlBuffer<ELEMENT_TYPE>::GlBuffer()
	{

	}

	template<class ELEMENT_TYPE>
	GlBuffer<ELEMENT_TYPE>::GlBuffer(typename GlBuffer<ELEMENT_TYPE>::size_type size) :
		m_data(size)
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
		m_data = std::move(o.m_data);
	}

	template<class ELEMENT_TYPE>
	GlBuffer<ELEMENT_TYPE>& GlBuffer<ELEMENT_TYPE>::operator=(GlBuffer<ELEMENT_TYPE>&& o)
	{
		m_data = std::move(o.m_data);
		return *this;
	}

	template<class ELEMENT_TYPE>
	void GlBuffer<ELEMENT_TYPE>::copyToGPU()
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(ELEMENT_TYPE), (void*)data(), GL_STATIC_DRAW);
		unbind();
	}

	template<class ELEMENT_TYPE>
	typename GlBuffer<ELEMENT_TYPE>::element_type* GlBuffer<ELEMENT_TYPE>::data()
	{
		return &m_data.front();
	}

	template<class ELEMENT_TYPE>
	typename GlBuffer<ELEMENT_TYPE>::size_type GlBuffer<ELEMENT_TYPE>::size()
	{
		return m_data.size();
	}

	template<class ELEMENT_TYPE>
	void GlBuffer<ELEMENT_TYPE>::resize(size_type size)
	{
		m_data.resize(size);
	}

	template<class ELEMENT_TYPE>
	typename GlBuffer<ELEMENT_TYPE>::element_type& GlBuffer<ELEMENT_TYPE>::operator[](size_type i)
	{
		return m_data[i];
	}

	template<class ELEMENT_TYPE>
	const typename GlBuffer<ELEMENT_TYPE>::element_type& GlBuffer<ELEMENT_TYPE>::operator[](size_type i) const
	{
		return m_data[i];
	}

	class VertexHandler
	{
	public:
		VertexHandler(uint stride);

	protected:
		uint m_stride;
		uint m_offset;
		uint m_count;
	};

	class VertexEnabler : public VertexHandler
	{
	public:
		VertexEnabler(uint stride);

		template<class ATTRIB_TYPE>
		VertexEnabler& attrib();
	};

	class VertexDisabler : public VertexHandler
	{
	public:
		VertexDisabler(uint stride);

		template<class ATTRIB_TYPE>
		VertexDisabler& attrib();
	};

	template<class ELEMENT_TYPE>
	void VertexBuffer<ELEMENT_TYPE>::bind()
	{
		GlBuffer<ELEMENT_TYPE>::bind();
		VertexEnabler enabler;
		ELEMENT_TYPE::Enable(enabler);
	}

	template<class ELEMENT_TYPE>
	void VertexBuffer<ELEMENT_TYPE>::unbind()
	{
		VertexDisabler disabler;
		ELEMENT_TYPE::Disable(disabler);
		GlBuffer<ELEMENT_TYPE>::unbind();
	}

	typedef GlBuffer<uint> IndexBuffer;
}