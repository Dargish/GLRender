#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/World/Entity.h>

#include <map>

namespace glr
{
	class GLRENDERAPI World
	{
	public:
		// Movable
		World();
		World(World&& o);
		World& operator=(World&& o);

		// Noncopyable
	    World(const World&) = delete;
	    World& operator=(const World&) = delete;

		Entity& createEntity(const string& name);
		Entity& entity(const string& name);

		Entity& addModel(const string& name, const string& modelPath);
		Entity& addCamera(const string& name);

	private:
		typedef std::map<string, Entity> EntityMap;
		EntityMap m_entities;
	};
}