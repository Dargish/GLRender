#pragma once

#include <GLRender/DataTypes.h>

#include <vector>

namespace glr
{
	template<class VERTEX_TYPE>
	class VertexBuffer : public std::vector<VERTEX_TYPE>
	{
	public:
		typedef VERTEX_TYPE vertex_type;
		static const size_t Stride = sizeof(vertex_type);

		vertex_type* data()
		{
			return &m_buffer.front();
		}

		uint buffer();
	};
}