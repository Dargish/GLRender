#include "FrameBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Plane.h"
#include <GL/glew.h>

namespace graphics
{
	FrameBuffer::FrameBuffer() :
		m_depthTexture(0)
	{
		
	}

	FrameBuffer::~FrameBuffer()
	{
	}

	uint FrameBuffer::generateBuffer()
	{
		uint buf;
		glGenFramebuffers(1, &buf);	
		return buf;
	}

	void FrameBuffer::deleteBuffer()
	{
		uint buf = buffer();
		if (buf != 0)
		{
			glDeleteFramebuffers(1, &buf);
		}
	}

	void FrameBuffer::addTextureTarget(const std::string& target, const Texture_Ptr& texture)
	{
		addTextureTarget(TextureTarget(target, texture));
	}

	void FrameBuffer::addTextureTarget(const TextureTarget& textureTarget)
	{
		m_textureTargets.push_back(textureTarget);
		dirty();
	}

	void FrameBuffer::drawToScreen(const Shader_Ptr& shader)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, buffer());
		Shader::Enable(shader);
		for (TextureTargets::iterator it = m_textureTargets.begin(); it != m_textureTargets.end(); ++it)
		{
			shader->setValue(it->first, it->second);
		}
		Plane plane;
		plane.draw(0.0f);
		Shader::Disable(shader);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	void FrameBuffer::resetFrameBuffer()
	{
		glEnable(GL_FRAMEBUFFER_SRGB);

		int width = 0;
		int height = 0;
		size_t currentAttachment = 0;
		for (TextureTargets::iterator it = m_textureTargets.begin(); it != m_textureTargets.end(); ++it)
		{
			it->second->bind();
			width = std::max(width, it->second->width());
			height = std::max(height, it->second->height());
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + currentAttachment, GL_TEXTURE_2D, it->second->buffer(), 0);
			it->second->unbind();
			++currentAttachment;
		}

		glGenTextures(1, &m_depthTexture);
		glBindTexture(GL_TEXTURE_2D, m_depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (Status != GL_FRAMEBUFFER_COMPLETE)
		{
			throw std::runtime_error("Frame buffer is not complete");
		}
		clean();
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer());
		if (isDirty())
		{
			resetFrameBuffer();
		}

		size_t drawBufferSize = m_textureTargets.size();
		if (drawBufferSize > 0)
		{
			std::vector< GLenum > drawBuffers(drawBufferSize);
			for (size_t i = 0; i < drawBufferSize; ++i)
			{
				drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
			}
			glDrawBuffers(drawBufferSize, &drawBuffers.front());
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void FrameBuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool FrameBuffer::empty() const
	{
		return m_textureTargets.empty();
	}
}
