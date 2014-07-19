#pragma once
#include "fwd.h"
#include <ecs/EntitySystem.h>

namespace systems
{
	class RenderSystem : public ecs::EntitySystem
	{
	public:
		virtual ~RenderSystem();

		virtual void componentAdded(const ecs::World_Ptr& world, const ecs::EntityID& entityID);
		virtual void componentRemoved(const ecs::World_Ptr& world, const ecs::EntityID& entityID);
		virtual void entityDestroyed(const ecs::EntityID& entityID);

	protected:
		virtual void _draw(const ecs::World_Ptr& world, float deltaTime);
	};
}