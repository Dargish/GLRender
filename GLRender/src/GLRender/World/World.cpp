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

	void World::update(float deltaTime)
	{
		SystemVector::iterator it = m_systems.begin();
		for (; it != m_systems.end(); ++it)
		{
			(*it)->update(deltaTime);
		}
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

	Camera World::addCamera(const string& name)
	{
		Entity& cameraEntity = createEntity(name);
		Camera camera(cameraEntity);
		return camera;
	}
}