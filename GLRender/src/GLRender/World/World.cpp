#include <GLRender/World/World.h>

namespace glr
{
	Entity& World::createEntity(const string& name)
	{
		EntityMap::value_type pair(name, Entity(name));
		m_entities.insert(pair);
		return pair.second;
	}

	Entity& World::entity(const string& name)
	{
		EntityMap::iterator it = m_entities.find(name);
		if (it != m_entities.end())
		{
			return it->second;
		}
		else
		{
			return createEntity(name);
		}
	}
}