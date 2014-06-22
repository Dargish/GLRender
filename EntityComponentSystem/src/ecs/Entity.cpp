#include "Entity.h"
#include "components/EntityComponent.h"
#include <json/json.h>

namespace ecs
{
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}

	void Entity::serialise(Json::Value& entityArray) const
	{
		Json::Value componentArray = Json::Value(Json::arrayValue);
		std::vector< EntityComponent_Ptr >::const_iterator it = m_components.begin();
		for (; it != m_components.end(); ++it)
		{
			(*it)->serialise(componentArray);
		}
		entityArray.append(componentArray);
	}

	void Entity::deserialise(const Json::Value& componentArray)
	{
	}

	const std::vector< EntityComponent_Ptr >& Entity::components() const
	{
		return m_components;
	}
}