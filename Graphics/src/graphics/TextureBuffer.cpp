#include "TextureBuffer.h"
#include "Shader.h"

namespace graphics
{
	GLfloat TextureBuffer::MaxAnisotropicLevel()
	{
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		return largest;
	}

	TextureBuffer::TextureBuffer() :
		m_minFilter(GL_NEAREST), m_magFilter(GL_NEAREST), m_anisotropicLevel(1.0f), m_mipMapped(true)
	{
	}

	TextureBuffer::~TextureBuffer()
	{
	}

	uint TextureBuffer::generateBuffer()
	{
		uint buf = 0;
		glGenTextures(1, &buf);
		return buf;
	}

	void TextureBuffer::deleteBuffer()
	{
		uint buf = buffer();
		if (buf != 0)
		{
			glDeleteTextures(1, &buf);
		}
	}

	void TextureBuffer::bind()
	{
		glBindTexture(GL_TEXTURE_2D, buffer());
		if (isDirty())
		{
			GLenum internalFormat = this->internalFormat();
			GLenum format = this->format();
			int width = this->width();
			int height = this->height();
			GLenum type = this->type();
			GLvoid* data = this->data();
			Shader::CheckGLError();
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
			if (mipMapped())
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			Shader::CheckGLError();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter());
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropicLevel());
			Shader::CheckGLError();
		}
	}

	void TextureBuffer::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	bool TextureBuffer::empty() const
	{
		return (width() > 0) && (height() > 0) && (data() != NULL);
	}

	GLenum TextureBuffer::internalFormat() const
	{
		return format();
	}

	GLenum TextureBuffer::format() const
	{
		// By default infer from nChannels
		if (nChannels() == 1)
		{
			return GL_R;
		}
		else if (nChannels() == 3)
		{
			return GL_RGB;
		}
		else if (nChannels() == 4)
		{
			return GL_RGBA;
		}
		return GL_NONE;
	}

	GLenum TextureBuffer::type() const
	{
		// By default infer from nChannels
		if (nChannels() == 1)
		{
			return GL_FLOAT;
		}
		else
		{
			return GL_UNSIGNED_BYTE;
		}
	}

	GLenum TextureBuffer::minFilter() const
	{
		return m_minFilter;
	}

	GLenum TextureBuffer::magFilter() const
	{
		return m_magFilter;
	}

	GLfloat TextureBuffer::anisotropicLevel() const
	{
		return m_anisotropicLevel;
	}

	bool TextureBuffer::mipMapped() const
	{
		return m_mipMapped;
	}

	void TextureBuffer::setMinFilter(GLenum minFilter)
	{
		m_minFilter = minFilter;
		dirty(); // Todo: setting filters shouldn't require data to be copied to gpu again
	}
	void TextureBuffer::setMagFilter(GLenum magFilter)
	{
		m_magFilter = magFilter;
		dirty(); // Todo: setting filters shouldn't require data to be copied to gpu again
	}

	void TextureBuffer::setAnisotropicLevel(GLfloat anisotropicLevel)
	{
		m_anisotropicLevel = std::max(1.0f, std::min(MaxAnisotropicLevel(), anisotropicLevel));
		dirty(); // Todo: setting filters shouldn't require data to be copied to gpu again
	}

	void TextureBuffer::setMipMapped(bool mipMapped)
	{
		m_mipMapped = mipMapped;
		dirty();
	}
}