#pragma once
#include "fwd.h"
#include "GLBuffer.h"

namespace graphics
{
	class TextureBuffer : public GLBuffer
	{
	public:
		static float MaxAnisotropicLevel();

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
		virtual void* data() const = 0;

		virtual uint internalFormat() const;
		virtual uint format() const;
		virtual uint type() const;

		uint minFilter() const;
		uint magFilter() const;
		float anisotropicLevel() const;
		bool mipMapped() const;

		void setMinFilter(uint minFilter);
		void setMagFilter(uint magFilter);
		void setAnisotropicLevel(float anisotropicLevel);
		void setMipMapped(bool mipMapped);

	private:
		uint m_minFilter;
		uint m_magFilter;
		uint m_anisotropicLevel;
		bool m_mipMapped;
	};
}
