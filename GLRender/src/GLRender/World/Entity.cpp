#include <GLRender/World/Entity.h>

namespace glr
{
	Entity::Entity(const string& name) :
		m_name(name)
	{

	}

	const string& Entity::name() const
	{
		return m_name;
	}

	Entity::iterator Entity::begin()
	{
		return m_components.begin();
	}

	Entity::const_iterator Entity::begin() const
	{
		return m_components.begin();
	}

	Entity::iterator Entity::end()
	{
		return m_components.end();
	}

	Entity::const_iterator Entity::end() const
	{
		return m_components.end();
	}	

	Entity::size_type Entity::size() const
	{
		return m_components.size();
	}
}