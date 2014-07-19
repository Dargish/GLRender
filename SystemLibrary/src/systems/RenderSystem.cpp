#include "RenderSystem.h"
#include "ecs/World.h"
#include "components/TransformComponent.h"
#include "components/MeshComponent.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Transform.h"
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
		m_interestingEntities.insert(entityID);
	}

	void RenderSystem::componentRemoved(const World_Ptr& world, const EntityID& entityID)
	{
		if (world->hasComponent(entityID, MeshComponent::TypeName()))
		{
			m_interestingEntities.erase(entityID);
		}
		if (!world->hasComponent(entityID, TransformComponent::TypeName()))
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
		Component_Ptr transformComponent;
		Component_Vector meshComponents;
		EntityID_Set::iterator it = m_interestingEntities.begin();
		for (; it != m_interestingEntities.end(); ++it)
		{
			meshComponents.clear();
			world->getComponents(*it, MeshComponent::TypeName(), meshComponents);
			world->getComponent(*it, TransformComponent::TypeName(), transformComponent);

			TransformComponent_Ptr typedTransformComponent = boost::dynamic_pointer_cast<TransformComponent>(transformComponent);
			Shader_Ptr shader = Shader::Current();
			if (shader.get())
			{
				shader->setValue("world", typedTransformComponent->transform->world());
			}
			Component_Vector::iterator it = meshComponents.begin();
			for (; it != meshComponents.end(); ++it)
			{
				MeshComponent_Ptr typedMeshComponent = boost::dynamic_pointer_cast<MeshComponent>(*it);
				typedMeshComponent->mesh->draw(deltaTime);
			}
		}
	}
}