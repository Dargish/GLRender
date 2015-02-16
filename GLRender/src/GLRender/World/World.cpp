#include <GLRender/World/World.h>

namespace glr
{
	World::World()
	{

	}

	World::World(World&& o)
	{
		m_entities = std::move(o.m_entities);
	}

	World& World::operator=(World&& o)
	{
		m_entities = std::move(o.m_entities);
		return *this;
	}

	Entity& World::createEntity(const string& name)
	{
		m_entities.insert(EntityMap::value_type(name, Entity(name)));
		return m_entities[name];
	}

	Entity& World::entity(const string& name)
	{
		EntityMap::iterator it = m_entities.find(name);
		if (it != m_entities.end())
		{
			return it->second;
		}
		else
		{
			return createEntity(name);
		}
	}

	Entity& World::addModel(const string& name, const string& modelPath)
	{
		Entity& model = createEntity(name);
		return model;
	}

	Entity& World::addCamera(const string& name)
	{
		Entity& camera = createEntity(name);
		return camera;
	}
}