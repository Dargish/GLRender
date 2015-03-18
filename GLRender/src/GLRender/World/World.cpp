#include <GLRender/World/World.h>
#include <GLRender/Component/ModelComponent.h>
#include <GLRender/Component/CameraComponent.h>
#include <GLRender/Component/TransformComponent.h>
#include <GLRender/Component/MaterialComponent.h>

namespace glr
{
	World::World()
	{

	}

	Entity& World::createEntity(const string& name)
	{
		auto result = m_entities.emplace(name, Entity(name));
		return (*result.first).second;
	}

	Entity& World::entity(const string& name)
	{
		iterator it = m_entities.find(name);
		if (it != m_entities.end())
		{
			return it->second;
		}
		else
		{
			return createEntity(name);
		}
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

	World::size_type World::size() const
	{
		return m_entities.size();
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
		model.addComponent<TransformComponent>();
		model.addComponent<MaterialComponent>();
		return model;
	}

	Entity& World::addCamera(const string& name)
	{
		Entity& camera = createEntity(name);
		camera.addComponent<CameraComponent>();
		camera.addComponent<TransformComponent>();
		return camera;
	}
}