#include "World.h"
#include "Entity.h"
#include "EntitySystem.h"
#include <graphics/Camera.h>
#include <serialisation/Serialiser.h>
#include <json/json.h>
#include <fstream>

using namespace serialisation;

namespace ecs
{
	World::World()
	{
	}

	World::~World()
	{
	}

	void World::save(const std::string& mapName) const
	{
		Json::StyledWriter writer;
		Json::Value root;
		serialise(root);
		std::ofstream myfile;
		myfile.open("Content/Maps/" + mapName + ".map");
		myfile << writer.write(root);
		myfile.close();
	}

	void World::load(const std::string& mapName)
	{
		Json::Value root;
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
			if (reader.parse(mapFileString, root))
			{
				deserialise(root);
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

	void World::serialise(Json::Value& root) const
	{
		Json::Value entityArray = Json::Value(Json::arrayValue);
		const_iterator it = begin();
		for (; it != end(); ++it)
		{
			entityArray.append((*it)->serialise());
		}
		root["entities"] = entityArray;
	}

	void World::deserialise(const Json::Value& root)
	{
		Json::Value entityArray = root["entities"];
		Json::Value::iterator it = entityArray.begin();
		for (; it != entityArray.end(); ++it)
		{
			m_entities.insert(Entity_Ptr(Serialiser::Deserialise<Entity>(*it)));
		}
	}

	void World::update(float deltaTime)
	{
		m_camera->update(deltaTime);
		std::set<EntitySystem_Ptr>::iterator it = m_systems.begin();
		for (; it != m_systems.end(); ++it)
		{
			(*it)->update(shared_from_this(), deltaTime);
		}
	}

	void World::draw(float deltaTime)
	{
		std::set<EntitySystem_Ptr>::iterator it = m_systems.begin();
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

	Entity_Ptr World::createEntity()
	{
		Entity_Ptr entity(new Entity);
		m_entities.insert(entity);
		return entity;
	}

	void World::destroyEntity(const Entity_Ptr& entity)
	{
		m_entities.erase(entity);
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

	void World::addSystem(const EntitySystem_Ptr& system)
	{
		m_systems.insert(system);
	}

	void World::removeSystem(const EntitySystem_Ptr& system)
	{
		m_systems.erase(system);
	}
}