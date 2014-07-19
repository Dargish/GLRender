#pragma once

#include "fwd.h"
#include <set>
#include <map>
#include <vector>
#include "graphics/fwd.h"
#include <boost/uuid/uuid.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace ecs
{
	class World : public boost::enable_shared_from_this<World>
	{
	public:
		typedef std::map<boost::uuids::uuid, std::vector<Component_Ptr>> EntityMap;
		typedef std::set< Entity_Ptr > EntitySet;
		typedef EntitySet::iterator iterator;
		typedef EntitySet::const_iterator const_iterator;

		World();
		~World();

		void save(const std::string& mapName) const;
		void load(const std::string& mapName);

		void serialise(Json::Value& root) const;
		void deserialise(const Json::Value& root);

		void update(float deltaTime);
		void draw(float deltaTime);

		graphics::Camera_Ptr& camera();
		graphics::Camera_Const_Ptr camera() const;
		void setCamera(const graphics::Camera_Ptr& camera);

		Entity_Ptr createEntity();
		void destroyEntity(const Entity_Ptr& entity);

		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;

		template< class SYSTEM_TYPE>
		EntitySystem_Ptr createSystem()
		{
			EntitySystem_Ptr system(new SYSTEM_TYPE);
			m_systems.insert(system);
			return system;
		}

		void addSystem(const EntitySystem_Ptr& system);
		void removeSystem(const EntitySystem_Ptr& system);

	private:
		std::set<Entity_Ptr> m_entities;
		std::set<EntitySystem_Ptr> m_systems;

		graphics::Camera_Ptr m_camera;
	};
}
