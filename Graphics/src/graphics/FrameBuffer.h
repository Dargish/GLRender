#pragma once
#include "TextureBuffer.h"

namespace graphics
{
	class FrameBuffer : public GLBuffer
	{
	public:
		FrameBuffer();
		virtual ~FrameBuffer();

		virtual uint generateBuffer();
		virtual void deleteBuffer();

		virtual void bind();
		virtual void unbind() const;
		virtual bool empty() const;
	};
}
