#pragma once
#include "fwd.h"
#include "serialisation/Serialiser.h"

namespace graphics
{
	class Mesh : public serialisation::Serialisable
	{
	public:
		Mesh();
		virtual ~Mesh();

		VertexBuffer_Ptr vertexBuffer();
		VertexBuffer_Const_Ptr vertexBuffer() const;

		IndexBuffer_Ptr indexBuffer();
		IndexBuffer_Const_Ptr indexBuffer() const;

		virtual void draw(float deltaTime);

		virtual void createMesh() = 0;

		void dirty();

	protected:
		VertexBuffer_Ptr m_vertexBuffer;
		IndexBuffer_Ptr m_indexBuffer;

	private:
		bool m_isDirty;
	};
}

