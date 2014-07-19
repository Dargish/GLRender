#pragma once
#include "fwd.h"
#include <serialisation/Serialiser.h>

namespace ecs
{
	class Component : public serialisation::Serialisable
	{
	public:
		virtual ~Component() { }
	};
}