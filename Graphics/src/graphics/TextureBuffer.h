#pragma once
#include "fwd.h"
#include "GLBuffer.h"

namespace graphics
{
	class TextureBuffer : public GLBuffer
	{
	public:
		static float MaxAnisotropicLevel();

		TextureBuffer(int width, int height, int nChannels);
		virtual ~TextureBuffer();

		virtual void* data() const = 0;

		virtual uint generateBuffer();
		virtual void deleteBuffer();

		virtual void bind();
		virtual void unbind() const;
		virtual bool empty() const;

		virtual uint internalFormat() const;
		virtual uint format() const;
		virtual uint type() const;

		int width() const;
		int height() const;
		int nChannels() const;
		uint minFilter() const;
		uint magFilter() const;
		float anisotropicLevel() const;
		bool mipMapped() const;

		void setWidth(int width);
		void setHeight(int height);
		void setNChannels(int nChannels);
		void setMinFilter(uint minFilter);
		void setMagFilter(uint magFilter);
		void setAnisotropicLevel(float anisotropicLevel);
		void setMipMapped(bool mipMapped);

	private:
		int m_width;
		int m_height;
		int m_nChannels;
		uint m_minFilter;
		uint m_magFilter;
		uint m_anisotropicLevel;
		bool m_mipMapped;
	};
}
