#pragma once
#include "fwd.h"
#include "GLBuffer.h"
#include <vector>

namespace graphics
{
	class IndexBuffer : public GLBuffer
	{
	public:
		typedef std::vector<uint> BufferType;

		BufferType& data();
		const BufferType& data() const;

		virtual void bind();

		virtual void unbind() const;

	private:
		BufferType m_data;
	};
}
