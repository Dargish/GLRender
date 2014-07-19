#include "Entity.h"
#include "Component.h"
#include <json/json.h>

using namespace serialisation;

namespace ecs
{
	Entity::Entity()
	{

	}

	Entity::Entity(const Entity& other)
	{
		std::vector< Component_Ptr >::const_iterator it = other.m_components.begin();
		for (; it != other.m_components.end(); ++it)
		{
			m_components.push_back(Component_Ptr(dynamic_cast<Component*>((*it)->clone())));
		}
	}

	Entity::~Entity()
	{

	}

	void Entity::operator= (const Entity& other)
	{
		std::vector< Component_Ptr >::const_iterator it = other.m_components.begin();
		for (; it != other.m_components.end(); ++it)
		{
			m_components.push_back(Component_Ptr(dynamic_cast<Component*>((*it)->clone())));
		}
	}

	std::string Entity::typeName() const
	{
		return "Entity";
	}

	Serialisable* Entity::clone() const
	{
		return new Entity(*this);
	}

	Json::Value Entity::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		Json::Value componentArray = Json::Value(Json::arrayValue);
		std::vector< Component_Ptr >::const_iterator it = m_components.begin();
		for (; it != m_components.end(); ++it)
		{
			componentArray.append((*it)->serialise());
		}
		data["components"] = componentArray;
		return data;
	}

	void Entity::deserialise(const Json::Value& data)
	{
		Json::Value componentArray = data["components"];
		Json::Value::iterator it = componentArray.begin();
		for (; it != componentArray.end(); ++it)
		{
			m_components.push_back(Component_Ptr(Serialiser::Deserialise<Component>(*it)));
		}
	}

	const std::vector< Component_Ptr >& Entity::components() const
	{
		return m_components;
	}
}