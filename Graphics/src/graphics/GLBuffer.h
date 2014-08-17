#pragma once
#include "fwd.h"

namespace graphics
{
	class GLBuffer
	{
	public:
		GLBuffer();
		virtual ~GLBuffer();

		uint buffer();
		virtual uint generateBuffer();
		virtual void deleteBuffer();

		void dirty();
		void clean();
		bool isDirty();

		virtual void bind() = 0;
		virtual void unbind() const = 0;
		virtual bool empty() const = 0;

	private:
		uint m_buffer;
		bool m_dirty;
	};
}
