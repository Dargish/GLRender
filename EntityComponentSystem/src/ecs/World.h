#pragma once

#include "fwd.h"
#include <serialisation/Serialiser.h>
#include "graphics/fwd.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace ecs
{
	class World : public serialisation::Serialisable, public boost::enable_shared_from_this<World>
	{
	public:
		typedef Entity_Map::iterator iterator;
		typedef Entity_Map::const_iterator const_iterator;

		World();
		World(const World& other);
		~World();
		void operator= (const World& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		void save(const std::string& mapName) const;
		void load(const std::string& mapName);
		
		void update(float deltaTime);
		void draw(float deltaTime);

		graphics::Camera_Ptr& camera();
		graphics::Camera_Const_Ptr camera() const;
		void setCamera(const graphics::Camera_Ptr& camera);

		EntityID createEntity();
		bool hasEntity(const EntityID& entityID) const;
		bool hasComponent(const EntityID& entityID, const std::string& componentType) const;
		bool addComponent(const EntityID& entityID, const Component_Ptr& component);
		bool getComponent(const EntityID& entityID, const std::string& componentType, Component_Ptr& component);
		bool getComponent(const EntityID& entityID, const std::string& componentType, Component_Const_Ptr& component) const;
		size_t getComponents(const EntityID& entityID, Component_Vector& components);
		size_t getComponents(const EntityID& entityID, Component_Const_Vector& components) const;
		size_t getComponents(const EntityID& entityID, const std::string& componentType, Component_Vector& components);
		size_t getComponents(const EntityID& entityID, const std::string& componentType, Component_Const_Vector& components) const;
		bool removeComponent(const EntityID& entityID, const Component_Ptr& component);
		bool destroyEntity(const EntityID& entityID);

		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;

		iterator find(const EntityID& entityID);
		const_iterator find(const EntityID& entityID) const;

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
		Entity_Map m_entities;
		Systems_Set m_systems;

		boost::uuids::random_generator randomGenerator;

		graphics::Camera_Ptr m_camera;
	};
}
