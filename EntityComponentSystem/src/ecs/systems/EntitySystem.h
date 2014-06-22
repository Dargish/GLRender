#pragma once

#include "../fwd.h"

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

	protected:
		virtual void _update(const World_Ptr& world, float deltaTime);
		virtual void _draw(const World_Ptr& world, float deltaTime);

	private:
		bool m_enabled;
	};
}
