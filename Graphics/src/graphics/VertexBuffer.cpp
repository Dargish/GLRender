#include "VertexBuffer.h"

namespace graphics
{
	void VertexPosition::Enable()
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void VertexPosition::Disable()
	{
		glDisableVertexAttribArray(0);
	}

	void VertexPositionNormal::Enable()
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (void*)offsetof(VertexPositionNormal, normal));
	}

	void VertexPositionNormal::Disable()
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	VertexBuffer::~VertexBuffer()
	{

	}
}