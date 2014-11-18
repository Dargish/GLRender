#include "FrameBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "primitives/Plane.h"
#include <GL/glew.h>

namespace graphics
{
	RGBABuffer::RGBABuffer(int width, int height) :
		TextureBuffer(width, height, 4)
	{
		m_data.resize(width * height * 4);
		setMipMapped(false);
	}

	RGBABuffer::~RGBABuffer()
	{

	}

	void* RGBABuffer::data() const
	{
		return (void*)&m_data.front();
	}

	uint RGBABuffer::internalFormat() const
	{
		return GL_RGBA16F;
	}

	uint RGBABuffer::format() const
	{
		return GL_RGBA;
	}

	uint RGBABuffer::type() const
	{
		return GL_SHORT;
	}


	FloatBuffer::FloatBuffer(int width, int height) :
		TextureBuffer(width, height, 2)
	{
		m_data.resize(width * height * 2);
		setMipMapped(false);
	}

	FloatBuffer::~FloatBuffer()
	{

	}

	void* FloatBuffer::data() const
	{
		return (void*)&m_data.front();
	}

	uint FloatBuffer::internalFormat() const
	{
		return GL_RG32F;
	}

	uint FloatBuffer::format() const
	{
		return GL_RG;
	}

	uint FloatBuffer::type() const
	{
		return GL_FLOAT;
	}


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

	void FrameBuffer::addTextureTarget(const std::string& target, const TextureBuffer_Ptr& buffer)
	{
		m_textureTargets[target] = buffer;
		dirty();
	}

	void FrameBuffer::bindForRead()
	{
		unbind();
		glBindFramebuffer(GL_READ_FRAMEBUFFER, buffer());
	}

	void FrameBuffer::bindTargets(const Shader_Ptr& shader)
	{
		for (TextureTargets::iterator it = m_textureTargets.begin(); it != m_textureTargets.end(); ++it)
		{
			shader->setValue(it->first, it->second);
		}
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
