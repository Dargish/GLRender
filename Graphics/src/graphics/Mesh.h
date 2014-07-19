#pragma once
#include "fwd.h"
#include "serialisation/Serialiser.h"

namespace graphics
{
	class Mesh : public serialisation::Serialisable
	{
	public:
		virtual ~Mesh();

		virtual void draw(float deltaTime) = 0;
	};
}

