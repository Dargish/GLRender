#include "EntitySystem.h"

namespace ecs
{
	EntitySystem::EntitySystem() :
		m_enabled(true)
	{

	}

	EntitySystem::~EntitySystem()
	{

	}

	void EntitySystem::setEnabled(bool enabled /*= true*/)
	{
		m_enabled = enabled;
	}

	void EntitySystem::setDisabled(bool disabled /*= true*/)
	{
		m_enabled = !disabled;
	}

	void EntitySystem::update(const World_Ptr& world, float deltaTime)
	{
		if (m_enabled)
		{
			_update(world, deltaTime);
		}
	}

	void EntitySystem::draw(const World_Ptr& world, float deltaTime)
	{
		if (m_enabled)
		{
			_draw(world, deltaTime);
		}
	}

	void EntitySystem::_update(const World_Ptr& world, float deltaTime)
	{

	}

	void EntitySystem::_draw(const World_Ptr& world, float deltaTime)
	{

	}
}