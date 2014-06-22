#include "RenderSystem.h"
#include "../World.h"
#include "../Entity.h"
#include "../components/MeshComponent.h"
#include "graphics/Mesh.h"
#include <vector>

namespace ecs
{
	RenderSystem::~RenderSystem()
	{
	}

	void RenderSystem::_draw(const World_Ptr& world, float deltaTime)
	{
		std::vector<MeshComponent_Ptr> meshComponents;
		World::iterator it = world->begin();
		for (; it != world->end(); ++it)
		{
			meshComponents.clear();
			if (!(*it)->getComponents(meshComponents))
			{
				continue;
			}
			std::vector<MeshComponent_Ptr>::iterator it = meshComponents.begin();
			for (; it != meshComponents.end(); ++it)
			{
				(*it)->mesh->draw(deltaTime);
			}
		}
	}
}