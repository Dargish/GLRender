#include <GLRender/World/Entity.h>

namespace glr
{
	Entity::Entity(const string& name) :
		m_name(name)
	{

	}

	bool Entity::operator==(const Entity& other) const
	{
		return m_name == other.m_name;
	}

	const string& Entity::name() const
	{
		return m_name;
	}
}