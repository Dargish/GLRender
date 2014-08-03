#include "ComponentContainer.h"

using namespace serialisation;

namespace ecs
{
	ComponentContainer::ComponentContainer()
	{

	}

	ComponentContainer::~ComponentContainer()
	{

	}

	std::string ComponentContainer::TypeName()
	{
		return "ComponentContainer";
	}

	std::string ComponentContainer::typeName() const
	{
		return ComponentContainer::TypeName();
	}

	Serialisable* ComponentContainer::clone() const
	{
		return new ComponentContainer(*this);
	}
}
