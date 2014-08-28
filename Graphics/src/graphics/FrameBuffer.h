#pragma once

#include "GLBuffer.h"
#include "fwd.h"
#include <vector>

namespace graphics
{
	class FrameBuffer : public GLBuffer
	{
	public:
		typedef std::pair< std::string, Texture_Ptr > TextureTarget;
		typedef std::vector< TextureTarget > TextureTargets;

		FrameBuffer();
		virtual ~FrameBuffer();

		virtual uint generateBuffer();
		virtual void deleteBuffer();

		void addTextureTarget(const std::string& target, const Texture_Ptr& texture);
		void addTextureTarget(const TextureTarget& textureTarget);

		void drawToScreen(const Shader_Ptr& shader);

		void resetFrameBuffer();
		
		virtual void bind();
		virtual void unbind() const;
		virtual bool empty() const;

	private:
		TextureTargets m_textureTargets;
		uint m_depthTexture;
	};
}
