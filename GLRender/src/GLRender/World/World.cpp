#include <GLRender/World/World.h>
#include <GLRender/Component/ModelComponent.h>

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
		auto result = m_entities.emplace(name, Entity(name));
		return (*result.first).second;
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

	World::EntityMap::iterator World::begin()
	{
		return m_entities.begin();
	}

	World::EntityMap::const_iterator World::begin() const
	{
		return m_entities.begin();
	}

	World::EntityMap::iterator World::end()
	{
		return m_entities.end();
	}

	World::EntityMap::const_iterator World::end() const
	{
		return m_entities.end();
	}

	bool World::hasEntity(const string& name)
	{
		return m_entities.find(name) != m_entities.end();
	}

	Entity& World::addModel(const string& name, const string& modelPath)
	{
		Entity& model = createEntity(name);
		std::shared_ptr<ModelComponent> modelComponent = model.addComponent<ModelComponent>();
		modelComponent->model.load(modelPath);
		return model;
	}

	Camera World::addCamera(const string& name)
	{
		Entity& cameraEntity = createEntity(name);
		Camera camera(cameraEntity);
		return camera;
	}
}