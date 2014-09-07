#pragma once

#include "GLBuffer.h"
#include "TextureBuffer.h"
#include "fwd.h"
#include <vector>
#include <map>

namespace graphics
{
	class RGBABuffer : public TextureBuffer
	{
	public:
		RGBABuffer(int width, int height);
		virtual ~RGBABuffer();

		virtual void* data() const;

		virtual uint internalFormat() const;
		virtual uint format() const;
		virtual uint type() const;

	private:
		std::vector<short> m_data;
	};

	class FrameBuffer : public GLBuffer
	{
	public:
		typedef std::map< std::string, RGBABuffer_Ptr > TextureTargets;

		FrameBuffer();
		virtual ~FrameBuffer();

		virtual uint generateBuffer();
		virtual void deleteBuffer();

		void addTextureTarget(const std::string& target, const RGBABuffer_Ptr& texture);

		void bindForRead();
		void bindTargets(const Shader_Ptr& shader);

		void resetFrameBuffer();
		
		virtual void bind();
		virtual void unbind() const;
		virtual bool empty() const;

	private:
		TextureTargets m_textureTargets;
		uint m_depthTexture;
	};
}
