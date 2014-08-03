#pragma once

#include "fwd.h"
#include "Component.h"
#include <serialisation/Serialiser.h>

namespace ecs
{
	class ComponentContainer : public serialisation::SerialisableContainer<Component>
	{
	public:
		ComponentContainer();
		virtual ~ComponentContainer();

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual Serialisable* clone() const;
	};
}
