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

		virtual void bind() const;
		virtual void unbind() const;
		virtual uint bufferType() const = 0;

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
		//GlBuffer(GlBuffer&& o);
		//GlBuffer& operator=(GlBuffer&& o);
		
		// Commented out, needs to go in a vector
		// Noncopyable
	    //GlBuffer(const GlBuffer&) = delete;
	    //GlBuffer& operator=(const GlBuffer&) = delete;

		void copyToGPU();

		element_type* data();

		size_type size() const;
		void resize(size_type size);

		element_type& operator[](size_type i);
		const element_type& operator[](size_type i) const;

	private:
		buffer_type m_data;
	};

	class IndexBuffer : public GlBuffer<uint>
	{
	public:
		IndexBuffer();
		IndexBuffer(GlBuffer<uint>::size_type size);

		virtual uint bufferType() const;		
	};

	template<class VERTEX_TYPE>
	class BaseVertexBuffer : public GlBuffer<VERTEX_TYPE>
	{
	public:
		BaseVertexBuffer();
		BaseVertexBuffer(typename GlBuffer<VERTEX_TYPE>::size_type size);

		virtual void bind() const;
		virtual void unbind() const;
		virtual uint bufferType() const;
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
	//template<class ELEMENT_TYPE>
	//GlBuffer<ELEMENT_TYPE>::GlBuffer(GlBuffer<ELEMENT_TYPE>&& o)
	//{
	//	m_data = std::move(o.m_data);
	//}

	//template<class ELEMENT_TYPE>
	//GlBuffer<ELEMENT_TYPE>& GlBuffer<ELEMENT_TYPE>::operator=(GlBuffer<ELEMENT_TYPE>&& o)
	//{
	//	m_data = std::move(o.m_data);
	//	return *this;
	//}

	template<class ELEMENT_TYPE>
	void GlBuffer<ELEMENT_TYPE>::copyToGPU()
	{
		bind();
		glBufferData(bufferType(), m_data.size() * sizeof(ELEMENT_TYPE), (void*)data(), GL_STATIC_DRAW);
		unbind();
	}

	template<class ELEMENT_TYPE>
	typename GlBuffer<ELEMENT_TYPE>::element_type* GlBuffer<ELEMENT_TYPE>::data()
	{
		return &m_data.front();
	}

	template<class ELEMENT_TYPE>
	typename GlBuffer<ELEMENT_TYPE>::size_type GlBuffer<ELEMENT_TYPE>::size() const
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
	
	template<class VERTEX_TYPE>
	BaseVertexBuffer<VERTEX_TYPE>::BaseVertexBuffer()
	{

	}

	template<class VERTEX_TYPE>
	BaseVertexBuffer<VERTEX_TYPE>::BaseVertexBuffer(typename GlBuffer<VERTEX_TYPE>::size_type size) :
		GlBuffer<VERTEX_TYPE>(size)
	{

	}

	template<class VERTEX_TYPE>
	void BaseVertexBuffer<VERTEX_TYPE>::bind() const
	{
		GlBuffer<VERTEX_TYPE>::bind();
		VERTEX_TYPE::Enable();
	}

	template<class VERTEX_TYPE>
	void BaseVertexBuffer<VERTEX_TYPE>::unbind() const
	{
		GlBuffer<VERTEX_TYPE>::unbind();
		VERTEX_TYPE::Disable();
	}

	template<class VERTEX_TYPE>
	uint BaseVertexBuffer<VERTEX_TYPE>::bufferType() const
	{
		return GL_ARRAY_BUFFER;
	}
}