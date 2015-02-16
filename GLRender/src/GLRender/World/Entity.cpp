#include <GLRender/World/Entity.h>

namespace glr
{
	Entity::Entity()
	{

	}

	Entity::Entity(const string& name) :
		m_name(name)
	{

	}

	Entity::Entity(Entity&& o) :
		m_name(std::move(o.m_name))
	{
		m_components = std::move(o.m_components);
	}

	Entity& Entity::operator=(Entity&& o)
	{
		m_name = std::move(o.m_name);
		m_components = std::move(o.m_components);
		return *this;
	}

	const string& Entity::name() const
	{
		return m_name;
	}
}