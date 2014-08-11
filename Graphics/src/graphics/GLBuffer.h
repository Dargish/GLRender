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

		void dirty();
		void clean();
		bool isDirty();

		virtual void bind() = 0;

		virtual void unbind() const = 0;

	private:
		uint m_buffer;
		bool m_dirty;
	};
}
