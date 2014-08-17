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

	void VertexPositionUVNormal::Enable()
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), (void*)offsetof(VertexPositionUVNormal, uv));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUVNormal), (void*)offsetof(VertexPositionUVNormal, normal));
	}

	void VertexPositionUVNormal::Disable()
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	VertexBuffer::~VertexBuffer()
	{

	}
}