#pragma once
#include "fwd.h"
#include "GLBuffer.h"
#include <GL/glew.h>

namespace graphics
{
	class TextureBuffer : public GLBuffer
	{
	public:
		static GLfloat MaxAnisotropicLevel();

		TextureBuffer();
		virtual ~TextureBuffer();

		virtual uint generateBuffer();
		virtual void deleteBuffer();

		virtual void bind();
		virtual void unbind() const;
		virtual bool empty() const;

		virtual int nChannels() const = 0;
		virtual int width() const = 0;
		virtual int height() const = 0;
		virtual GLvoid* data() const = 0;

		virtual GLenum internalFormat() const;
		virtual GLenum format() const;
		virtual GLenum type() const;

		GLenum minFilter() const;
		GLenum magFilter() const;
		GLfloat anisotropicLevel() const;
		bool mipMapped() const;

		void setMinFilter(GLenum minFilter);
		void setMagFilter(GLenum magFilter);
		void setAnisotropicLevel(GLfloat anisotropicLevel);
		void setMipMapped(bool mipMapped);

	private:
		GLenum m_minFilter;
		GLenum m_magFilter;
		GLenum m_anisotropicLevel;
		bool m_mipMapped;
	};
}
