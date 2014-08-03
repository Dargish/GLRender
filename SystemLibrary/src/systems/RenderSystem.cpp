#include "RenderSystem.h"
#include "ecs/World.h"
#include "components/TransformComponent.h"
#include "components/MeshComponent.h"
#include "components/MaterialComponent.h"
#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Shader.h"
#include "graphics/Transform.h"
#include "graphics/Camera.h"
#include <vector>

using namespace graphics;
using namespace ecs;
using namespace components;

namespace systems
{
	RenderSystem::~RenderSystem()
	{
	}

	void RenderSystem::componentAdded(const World_Ptr& world, const EntityID& entityID)
	{
		if (!world->hasComponent(entityID, MeshComponent::TypeName()))
		{
			return;
		}
		if (!world->hasComponent(entityID, TransformComponent::TypeName()))
		{
			return;
		}
		if (!world->hasComponent(entityID, MaterialComponent::TypeName()))
		{
			return;
		}
		m_interestingEntities.insert(entityID);
	}

	void RenderSystem::componentRemoved(const World_Ptr& world, const EntityID& entityID)
	{
		if (!world->hasComponent(entityID, MeshComponent::TypeName()))
		{
			m_interestingEntities.erase(entityID);
		}
		if (!world->hasComponent(entityID, TransformComponent::TypeName()))
		{
			m_interestingEntities.erase(entityID);
		}
		if (!world->hasComponent(entityID, MaterialComponent::TypeName()))
		{
			m_interestingEntities.erase(entityID);
		}
	}

	void RenderSystem::entityDestroyed(const EntityID& entityID)
	{
		m_interestingEntities.erase(entityID);
	}

	void RenderSystem::_draw(const World_Ptr& world, float deltaTime)
	{
		m_renderCache.clear();
		{
			EntityID_Set::iterator it = m_interestingEntities.begin();
			for (; it != m_interestingEntities.end(); ++it)
			{
				std::vector<MeshComponent_Ptr> meshComponents = world->components<MeshComponent>(*it);
				TransformComponent_Ptr transformComponent = world->component<TransformComponent>(*it);
				MaterialComponent_Ptr materialComponent = world->component<MaterialComponent>(*it);

				RenderCache renderCache;
				renderCache.material = materialComponent->material;
				renderCache.transform = transformComponent->transform;

				std::vector<MeshComponent_Ptr>::iterator it = meshComponents.begin();
				for (; it != meshComponents.end(); ++it)
				{
					renderCache.meshes.push_back((*it)->mesh);
				}

				Shader_Ptr shader = renderCache.material->shader();
				m_renderCache[shader].push_back(renderCache);
			}
		}
		{
			RenderCacheMap::iterator it = m_renderCache.begin();
			for (; it != m_renderCache.end(); ++it)
			{
				Shader_Ptr shader = it->first;
				Shader::Enable(shader);
				shader->setValue("proj", world->camera()->projMatrix());
				shader->setValue("view", world->camera()->viewMatrix());
				RenderCacheVector::iterator rit = it->second.begin();
				for (; rit != it->second.end(); ++rit)
				{
					shader->setValue("world", rit->transform->world());
					rit->material->applyToShader();
					MeshVector::iterator mit = rit->meshes.begin();
					for (; mit != rit->meshes.end(); ++mit)
					{
						(*mit)->draw(deltaTime);
					}
				}
				Shader::Disable(shader);
			}
		}
	}
}