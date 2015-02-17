#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/World/Entity.h>
#include <GLRender/Systems/System.h>

#include <map>
#include <vector>

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

	    void update(float deltaTime);

		Entity& createEntity(const string& name);
		Entity& entity(const string& name);

		Entity& addModel(const string& name, const string& modelPath);
		Entity& addCamera(const string& name);

		template<class T>
		std::shared_ptr<T> addSystem()
		{
			std::shared_ptr<T> ptr(new T);
			m_systems.push_back(ptr);
			return ptr;
		}

	private:
		typedef std::map<string, Entity> EntityMap;
		typedef std::vector<std::shared_ptr<System>> SystemVector;
		EntityMap m_entities;
		SystemVector m_systems;
	};
}