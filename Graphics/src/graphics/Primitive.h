#pragma once
#include "fwd.h"
#include "Mesh.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector3.hpp>
#include <vector>

namespace graphics
{
	class Primitive : public Mesh
	{
	public:
		Primitive();
		virtual ~Primitive();

		VertexBuffer_Ptr vertexBuffer();
		VertexBuffer_Const_Ptr vertexBuffer() const;

		IndexBuffer_Ptr indexBuffer();
		IndexBuffer_Const_Ptr indexBuffer() const;

		virtual void draw(float deltaTime);

	protected:
		VertexBuffer_Ptr m_vertexBuffer;
		IndexBuffer_Ptr m_indexBuffer;
	};
}
