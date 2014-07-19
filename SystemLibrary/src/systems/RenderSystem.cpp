#include "RenderSystem.h"
#include "ecs/World.h"
#include "ecs/Entity.h"
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

	void RenderSystem::_draw(const World_Ptr& world, float deltaTime)
	{
		TransformComponent_Ptr transformComponent;
		std::vector<MeshComponent_Ptr> meshComponents;
		World::iterator it = world->begin();
		for (; it != world->end(); ++it)
		{
			meshComponents.clear();
			if (!(*it)->getComponents(meshComponents))
			{
				continue;
			}
			if ((*it)->getComponent(transformComponent))
			{
				Shader_Ptr shader = Shader::Current();
				if (shader.get())
				{
					shader->setValue("world", transformComponent->transform->world());
				}
			}
			std::vector<MeshComponent_Ptr>::iterator it = meshComponents.begin();
			for (; it != meshComponents.end(); ++it)
			{
				(*it)->mesh->draw(deltaTime);
			}
		}
	}
}