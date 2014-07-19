#pragma once

#include "fwd.h"

namespace ecs
{
	class EntitySystem
	{
	public:
		EntitySystem();
		virtual ~EntitySystem();

		void setEnabled(bool enabled = true);
		void setDisabled(bool disabled = true);

		void update(const World_Ptr& world, float deltaTime);
		void draw(const World_Ptr& world, float deltaTime);

		virtual void componentAdded(const World_Ptr& world, const EntityID& entityID) = 0;
		virtual void componentRemoved(const World_Ptr& world, const EntityID& entityID) = 0;
		virtual void entityDestroyed(const EntityID& entityID) = 0;

	protected:
		virtual void _update(const World_Ptr& world, float deltaTime);
		virtual void _draw(const World_Ptr& world, float deltaTime);

		EntityID_Set m_interestingEntities;

	private:
		bool m_enabled;
	};
}
