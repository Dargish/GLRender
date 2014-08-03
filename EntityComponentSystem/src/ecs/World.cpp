#include "World.h"
#include "Component.h"
#include "EntitySystem.h"
#include <graphics/Camera.h>
#include <json/json.h>
#include <core/JsonFile.h>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

using namespace core;
using namespace serialisation;

namespace ecs
{
	EntityID StrToEntityID(const std::string& str)
	{
		return boost::lexical_cast<EntityID>(str);
	}
	
	std::string World::MapPath(const std::string& mapName)
	{
		return "Content/Maps/" + mapName + ".map";
	}

	std::string World::EntityPath(const std::string& entityName)
	{
		return "Content/Entities/" + entityName + ".ent";
	}

	World::World()
	{
	}

	World::World(const World& other)
	{
		throw std::runtime_error("Worlds cannot be copied");
	}

	World::~World()
	{
	}

	void World::operator= (const World& other)
	{
		throw std::runtime_error("Worlds cannot be copied");
	}

	std::string World::TypeName()
	{
		return "World";
	}

	std::string World::typeName() const
	{
		return World::TypeName();
	}

	Serialisable* World::clone() const
	{
		return new World(*this);
	}

	Json::Value World::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		Json::Value entityArray = Json::Value(Json::arrayValue);
		const_iterator it = begin();
		for (; it != end(); ++it)
		{
			Json::Value entityData = Json::Value();
			entityData["entityID"] = boost::lexical_cast<std::string>( it->first );
			entityData["components"] = it->second->serialise();
			entityArray.append(entityData);
		}
		data["entities"] = entityArray;
		return data;
	}

	void World::deserialise(const Json::Value& data)
	{
		Json::Value entityArray = data["entities"];
		Json::Value::iterator it = entityArray.begin();
		for (; it != entityArray.end(); ++it)
		{
			Json::Value entityData = *it;
			EntityID entityID = boost::lexical_cast<EntityID>(entityData["entityID"].asCString());
			m_entities[entityID] = ComponentContainer_Ptr(Serialiser::Deserialise<ComponentContainer>(entityData["components"]));
			Systems_Set::iterator sit = m_systems.begin();
			for (; sit != m_systems.end(); ++sit)
			{
				(*sit)->componentAdded(shared_from_this(), entityID);
			}
		}
	}

	void World::load(const std::string& mapName)
	{
		deserialise(JsonFile::Load(MapPath(mapName)));
	}

	void World::save(const std::string& mapName) const
	{
		JsonFile::Save(MapPath(mapName), serialise());
	}

	void World::update(float deltaTime)
	{
		m_camera->update(deltaTime);
		Systems_Set::iterator it = m_systems.begin();
		for (; it != m_systems.end(); ++it)
		{
			(*it)->update(shared_from_this(), deltaTime);
		}
	}

	void World::draw(float deltaTime)
	{
		Systems_Set::iterator it = m_systems.begin();
		for (; it != m_systems.end(); ++it)
		{
			(*it)->draw(shared_from_this(), deltaTime);
		}
	}

	graphics::Camera_Ptr& World::camera()
	{
		return m_camera;
	}

	graphics::Camera_Const_Ptr World::camera() const
	{
		return m_camera;
	}

	void World::setCamera(const graphics::Camera_Ptr& camera)
	{
		m_camera = camera;
	}

	EntityID World::createEntity(const std::string& entityName /*= ""*/)
	{
		EntityID entityID = randomGenerator();
		if (entityName.empty())
		{
			m_entities[entityID] = ComponentContainer_Ptr(new ComponentContainer);
		}
		else
		{
			Json::Value data = JsonFile::Load(EntityPath(entityName));
			ComponentContainer_Ptr(Serialiser::Deserialise<ComponentContainer>(data));
		}
		return entityID;
	}

	void World::saveEntity(const EntityID& entityID, const std::string& entityName)
	{
		const_iterator found = find(entityID);
		if (found != end())
		{
			JsonFile::Save(EntityPath(entityName), found->second->serialise());
		}
	}

	bool World::hasEntity(const EntityID& entityID) const
	{
		return (find(entityID) != end());
	}

	bool World::hasComponent(const EntityID& entityID, const std::string& componentType) const
	{
		const_iterator found = find(entityID);
		if (found != end())
		{
			ComponentContainer::const_iterator it = found->second->begin();
			for (it; it != found->second->end(); ++it)
			{
				if ((*it)->typeName() == componentType)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool World::addComponent(const EntityID& entityID, const Component_Ptr& component)
	{
		iterator found = find(entityID);
		if (found != end())
		{
			found->second->push_back(component);
			Systems_Set::iterator it = m_systems.begin();
			for (; it != m_systems.end(); ++it)
			{
				(*it)->componentAdded(shared_from_this(), entityID);
			}
			return true;
		}
		return false;
	}

	Component_Vector World::getComponents(const EntityID& entityID)
	{
		Component_Vector components;
		iterator found = find(entityID);
		if (found != end())
		{
			ComponentContainer::iterator it = found->second->begin();
			for (it; it != found->second->end(); ++it)
			{
				components.push_back(*it);
			}
		}
		return components;
	}

	Component_Const_Vector World::getComponents(const EntityID& entityID) const
	{
		Component_Const_Vector components;
		const_iterator found = find(entityID);
		if (found != end())
		{
			ComponentContainer::const_iterator it = found->second->begin();
			for (it; it != found->second->end(); ++it)
			{
				components.push_back(*it);
			}
		}
		return components;
	}
	
	bool World::removeComponent(const EntityID& entityID, const Component_Ptr& component)
	{
		iterator found = find(entityID);
		if (found != end())
		{
			ComponentContainer::iterator it = found->second->begin();
			for (it; it != found->second->end(); ++it)
			{
				if ((*it) == component)
				{
					found->second->erase(it);
					Systems_Set::iterator it = m_systems.begin();
					for (; it != m_systems.end(); ++it)
					{
						(*it)->componentAdded(shared_from_this(), entityID);
					}
					return true;
				}
			}
		}
		return false;
	}

	bool World::destroyEntity(const EntityID& entityID)
	{
		return (m_entities.erase(entityID) > 0);
	}

	World::iterator World::begin()
	{
		return m_entities.begin();
	}

	World::const_iterator World::begin() const
	{
		return m_entities.begin();
	}

	World::iterator World::end()
	{
		return m_entities.end();
	}

	World::const_iterator World::end() const
	{
		return m_entities.end();
	}

	World::iterator World::find(const EntityID& entityID)
	{
		return m_entities.find(entityID);
	}

	World::const_iterator World::find(const EntityID& entityID) const
	{
		return m_entities.find(entityID);
	}

	void World::addSystem(const EntitySystem_Ptr& system)
	{
		m_systems.insert(system);
	}

	void World::removeSystem(const EntitySystem_Ptr& system)
	{
		m_systems.erase(system);
	}
}