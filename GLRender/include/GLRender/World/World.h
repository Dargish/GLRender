#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/World/Entity.h>

#include <map>
#include <vector>

namespace glr
{
	class GLRENDERAPI World
	{
	public:
		typedef std::map<string, Entity> EntityMap;

		World();

		// Movable
		World(World&& o);
		World& operator=(World&& o);

		// Noncopyable
	    World(const World&) = delete;
	    World& operator=(const World&) = delete;

		// Entity creation
		Entity& createEntity(const string& name);
		Entity& entity(const string& name);

		// Iterator methods
		EntityMap::iterator begin();
		EntityMap::const_iterator begin() const;
		
		EntityMap::iterator end();
		EntityMap::const_iterator end() const;

		// Find methods
		bool hasEntity(const string& name);

		// Helper methods
		Entity& addModel(const string& name, const string& modelPath);
		Entity& addCamera(const string& name);

	private:
		EntityMap m_entities;
	};
}