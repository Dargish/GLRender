#include <GLRender/DataTypes.h>
#include <GLRender/World/Entity.h>

#include <map>

namespace glr
{
	class GLRENDERAPI World
	{
	public:
		Entity& createEntity(const string& name);
		Entity& entity(const string& name);

	private:
		typedef std::map<string, Entity> EntityMap;
		EntityMap m_entities;
	};
}