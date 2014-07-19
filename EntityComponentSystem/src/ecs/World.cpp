#include "World.h"
#include "Component.h"
#include "EntitySystem.h"
#include <graphics/Camera.h>
#include <json/json.h>
#include <fstream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

using namespace serialisation;

namespace ecs
{
	World::World()
	{
	}

	World::World(const World& other)
	{
		// Todo: Implement
	}

	World::~World()
	{
	}

	void World::operator= (const World& other)
	{
		// Todo: Implement
	}

	std::string World::typeName() const
	{
		return "World";
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
			Json::Value componentArray = Json::Value(Json::arrayValue);
			Component_Vector::const_iterator cit = it->second.begin();
			for (; cit != it->second.end(); ++cit)
			{
				componentArray.append((*cit)->serialise());
			}
			entityData["components"] = componentArray;
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
			Component_Vector componentVector;
			Json::Value componentArray = entityData["components"];
			Json::Value::iterator it = componentArray.begin();
			for (; it != componentArray.end(); ++it)
			{
				componentVector.push_back(Component_Ptr(Serialiser::Deserialise<Component>(*it)));
			}
			m_entities[entityID] = componentVector;
			Systems_Set::iterator sit = m_systems.begin();
			for (; sit != m_systems.end(); ++sit)
			{
				(*sit)->componentAdded(shared_from_this(), entityID);
			}
		}
	}

	void World::save(const std::string& mapName) const
	{
		Json::StyledWriter writer;
		Json::Value data = serialise();
		std::ofstream myfile;
		myfile.open("Content/Maps/" + mapName + ".map");
		myfile << writer.write(data);
		myfile.close();
	}

	void World::load(const std::string& mapName)
	{
		Json::Value data;
		Json::Reader reader;
		std::ifstream myfile("Content/Maps/" + mapName + ".map");
		if (myfile.is_open())
		{
			std::string mapFileString;
			std::string line;
			while (std::getline(myfile, line))
			{
				mapFileString += line;
			}
			myfile.close();
			if (reader.parse(mapFileString, data))
			{
				deserialise(data);
			}
			else
			{
				std::cerr << "Error loading map" << std::endl;
			}
		}
		else
		{
			std::cerr << "Couldn't open map file " << mapName << std::endl;
		}
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

	EntityID World::createEntity()
	{
		EntityID entityID = randomGenerator();
		m_entities[entityID];
		return entityID;
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
			Component_Vector::const_iterator it = found->second.begin();
			for (it; it != found->second.end(); ++it)
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
			found->second.push_back(component);
			Systems_Set::iterator it = m_systems.begin();
			for (; it != m_systems.end(); ++it)
			{
				(*it)->componentAdded(shared_from_this(), entityID);
			}
			return true;
		}
		return false;
	}

	bool World::getComponent(const EntityID& entityID, const std::string& componentType, Component_Ptr& component)
	{
		iterator found = find(entityID);
		if (found != end())
		{
			Component_Vector::iterator it = found->second.begin();
			for (it; it != found->second.end(); ++it)
			{
				if ((*it)->typeName() == componentType)
				{
					component = *it;
					return true;
				}
			}
		}
		return false;
	}

	bool World::getComponent(const EntityID& entityID, const std::string& componentType, Component_Const_Ptr& component) const
	{
		const_iterator found = find(entityID);
		if (found != end())
		{
			Component_Vector::const_iterator it = found->second.begin();
			for (it; it != found->second.end(); ++it)
			{
				if ((*it)->typeName() == componentType)
				{
					component = *it;
					return true;
				}
			}
		}
		return false;
	}

	size_t World::getComponents(const EntityID& entityID, Component_Vector& components)
	{
		iterator found = find(entityID);
		if (found != end())
		{
			components = found->second;
			return components.size();
		}
		return 0;
	}

	size_t World::getComponents(const EntityID& entityID, Component_Const_Vector& components) const
	{
		const_iterator found = find(entityID);
		if (found != end())
		{
			Component_Vector::const_iterator it = found->second.begin();
			for (it; it != found->second.end(); ++it)
			{
				components.push_back(*it);
			}
			return components.size();
		}
		return 0;
	}

	size_t World::getComponents(const EntityID& entityID, const std::string& componentType, Component_Vector& components)
	{
		size_t amountFound = 0;
		iterator found = find(entityID);
		if (found != end())
		{
			Component_Vector::iterator it = found->second.begin();
			for (it; it != found->second.end(); ++it)
			{
				if ((*it)->typeName() == componentType)
				{
					components.push_back(*it);
					++amountFound;
				}
			}
		}
		return amountFound;
	}

	size_t World::getComponents(const EntityID& entityID, const std::string& componentType, Component_Const_Vector& components) const
	{
		size_t amountFound = 0;
		const_iterator found = find(entityID);
		if (found != end())
		{
			Component_Vector::const_iterator it = found->second.begin();
			for (it; it != found->second.end(); ++it)
			{
				if ((*it)->typeName() == componentType)
				{
					components.push_back(*it);
					++amountFound;
				}
			}
		}
		return amountFound;
	}

	bool World::removeComponent(const EntityID& entityID, const Component_Ptr& component)
	{
		iterator found = find(entityID);
		if (found != end())
		{
			Component_Vector::iterator it = found->second.begin();
			for (it; it != found->second.end(); ++it)
			{
				if ((*it) == component)
				{
					found->second.erase(it);
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