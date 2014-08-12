#pragma once
#include "fwd.h"
#include "GLBuffer.h"
#include <vector>
#include <GL/glew.h>

#define DECL_BUFFER_TYPE(NAME) \
typedef TypedVertexBuffer< NAME > NAME ## Buffer; \
typedef boost::shared_ptr< NAME ## Buffer > NAME ## Buffer_Ptr; \
typedef boost::shared_ptr< const NAME ## Buffer > NAME ## Buffer_Const_Ptr;

namespace graphics
{
	struct VertexPosition
	{
		Vector3 position;

		static void Enable();
		static void Disable();
	};

	struct VertexPositionNormal
	{
		Vector3 position;
		Vector3 normal;

		static void Enable();
		static void Disable();
	};

	class VertexBuffer : public GLBuffer
	{
	public:
		virtual ~VertexBuffer();
	};

	template< class VERTEX_TYPE >
	class TypedVertexBuffer : public VertexBuffer
	{
	public:
		typedef VERTEX_TYPE VertexType;
		typedef std::vector<VERTEX_TYPE> BufferType;

		virtual ~TypedVertexBuffer();

		BufferType& data();
		const BufferType& data() const;

		virtual void bind();
		virtual void unbind() const;

		virtual bool empty() const;

	private:
		BufferType m_data;
	};

	DECL_BUFFER_TYPE(VertexPosition);
	DECL_BUFFER_TYPE(VertexPositionNormal);

	template< class VERTEX_TYPE >
	TypedVertexBuffer<VERTEX_TYPE>::~TypedVertexBuffer()
	{

	}

	template< class VERTEX_TYPE >
	typename TypedVertexBuffer<VERTEX_TYPE>::BufferType& TypedVertexBuffer<VERTEX_TYPE>::data()
	{
		return m_data;
	}

	template< class VERTEX_TYPE >
	const typename TypedVertexBuffer<VERTEX_TYPE>::BufferType& TypedVertexBuffer<VERTEX_TYPE>::data() const
	{
		return m_data;
	}

	template< class VERTEX_TYPE >
	void TypedVertexBuffer<VERTEX_TYPE>::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer());
		if (isDirty())
		{
			glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(VertexType), &m_data.front(), GL_STATIC_DRAW);
			clean();
		}
		VertexType::Enable();
	}

	template< class VERTEX_TYPE >
	void TypedVertexBuffer<VERTEX_TYPE>::unbind() const
	{
		VertexType::Disable();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	template< class VERTEX_TYPE >
	bool TypedVertexBuffer<VERTEX_TYPE>::empty() const
	{
		return m_data.empty();
	}
}
