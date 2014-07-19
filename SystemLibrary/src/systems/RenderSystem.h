#pragma once
#include "fwd.h"
#include <ecs/EntitySystem.h>

namespace systems
{
	class RenderSystem : public ecs::EntitySystem
	{
	public:
		virtual ~RenderSystem();

		virtual void _draw(const ecs::World_Ptr& world, float deltaTime);
	};
}