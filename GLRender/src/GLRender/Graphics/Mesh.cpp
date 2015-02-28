#include <GLRender/Graphics/Mesh.h>

namespace glr
{
	BaseMesh::~BaseMesh()
	{

	}

	IndexBuffer& BaseMesh::indexBuffer()
	{
		return m_indexBuffer;
	}
}