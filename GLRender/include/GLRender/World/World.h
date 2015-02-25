#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/World/Entity.h>
#include <GLRender/Graphics/Camera.h>

#include <map>
#include <vector>

namespace glr
{
	class GLRENDERAPI World
	{
	public:
		World();

		// Movable
		World(World&& o);
		World& operator=(World&& o);

		// Noncopyable
	    World(const World&) = delete;
	    World& operator=(const World&) = delete;

		Entity& createEntity(const string& name);
		Entity& entity(const string& name);

		// Helper methods
		Entity& addModel(const string& name, const string& modelPath);
		Camera addCamera(const string& name);

	private:
		typedef std::map<string, Entity> EntityMap;
		EntityMap m_entities;
	};
}