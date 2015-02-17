#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/World/Entity.h>
#include <GLRender/Systems/System.h>
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

	    // Update all systems
	    void update(float deltaTime);

		Entity& createEntity(const string& name);
		Entity& entity(const string& name);

		template<class T>
		std::shared_ptr<T> addSystem()
		{
			std::shared_ptr<T> ptr(new T);
			m_systems.push_back(ptr);
			return ptr;
		}

		// Helper methods
		Entity& addModel(const string& name, const string& modelPath);
		Camera addCamera(const string& name);

	private:
		typedef std::map<string, Entity> EntityMap;
		typedef std::vector<std::shared_ptr<System>> SystemVector;
		EntityMap m_entities;
		SystemVector m_systems;
	};
}