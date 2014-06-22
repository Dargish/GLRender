#pragma once
#include "EntitySystem.h"

namespace ecs
{
	class RenderSystem : public EntitySystem
	{
	public:
		virtual ~RenderSystem();

		virtual void _draw(const World_Ptr& world, float deltaTime);
	};
}