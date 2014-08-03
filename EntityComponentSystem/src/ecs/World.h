#pragma once

#include "fwd.h"
#include "ComponentContainer.h"
#include <graphics/fwd.h>
#include <serialisation/Serialiser.h>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace ecs
{
	EntityID StrToEntityID(const std::string& str);

	class World : public serialisation::Serialisable, public boost::enable_shared_from_this<World>
	{
	public:
		typedef std::map<EntityID, ComponentContainer_Ptr> EntityMap;
		typedef EntityMap::iterator iterator;
		typedef EntityMap::const_iterator const_iterator;

		static std::string MapPath(const std::string& mapName);
		static std::string EntityPath(const std::string& entityName);

		World();
		World(const World& other);
		~World();
		void operator= (const World& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		void load(const std::string& mapName);
		void save(const std::string& mapName) const;
		
		void update(float deltaTime);
		void draw(float deltaTime);

		graphics::Camera_Ptr& camera();
		graphics::Camera_Const_Ptr camera() const;
		void setCamera(const graphics::Camera_Ptr& camera);

		EntityID createEntity(const std::string& entityName = "");
		void saveEntity(const EntityID& entityID, const std::string& entityName);

		bool hasEntity(const EntityID& entityID) const;
		bool hasComponent(const EntityID& entityID, const std::string& componentType) const;
		bool addComponent(const EntityID& entityID, const Component_Ptr& component);
		Component_Vector getComponents(const EntityID& entityID);
		Component_Const_Vector getComponents(const EntityID& entityID) const;
		bool removeComponent(const EntityID& entityID, const Component_Ptr& component);
		bool destroyEntity(const EntityID& entityID);

		template<class T>
		boost::shared_ptr<T> component(const EntityID& entityID);
		template<class T>
		boost::shared_ptr<const T> component(const EntityID& entityID) const;
		template<class T>
		std::vector<boost::shared_ptr<T>> components(const EntityID& entityID);
		template<class T>
		std::vector<boost::shared_ptr<const T>> components(const EntityID& entityID) const;

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
		void componentAdded(const EntityID& entityID);
		void componentRemoved(const EntityID& entityID);
		void entityDestroyed(const EntityID& entityID);

		EntityMap m_entities;
		Systems_Set m_systems;

		boost::uuids::random_generator randomGenerator;

		graphics::Camera_Ptr m_camera;
	};


	template<class T>
	boost::shared_ptr<T> World::component(const EntityID& entityID)
	{
		iterator found = find(entityID);
		if (found != end())
		{
			ComponentContainer::iterator it = found->second->begin();
			for (it; it != found->second->end(); ++it)
			{
				if ((*it)->typeName() == T::TypeName())
				{
					return boost::dynamic_pointer_cast<T>(*it);
				}
			}
		}
		return boost::shared_ptr<T>();
	}

	template<class T>
	boost::shared_ptr<const T> World::component(const EntityID& entityID) const
	{
		iterator found = find(entityID);
		if (found != end())
		{
			ComponentContainer::const_iterator it = found->second->begin();
			for (it; it != found->second->end(); ++it)
			{
				if ((*it)->typeName() == T::TypeName())
				{
					return boost::dynamic_pointer_cast<const T>(*it);
				}
			}
		}
		return boost::shared_ptr<T>();
	}

	template<class T>
	std::vector<boost::shared_ptr<T>> World::components(const EntityID& entityID)
	{
		std::vector<boost::shared_ptr<T>> components;
		iterator found = find(entityID);
		if (found != end())
		{
			ComponentContainer::iterator it = found->second->begin();
			for (it; it != found->second->end(); ++it)
			{
				if ((*it)->typeName() == T::TypeName())
				{
					components.push_back(boost::dynamic_pointer_cast<T>(*it));
				}
			}
		}
		return components;
	}

	template<class T>
	std::vector<boost::shared_ptr<const T>> World::components(const EntityID& entityID) const
	{
		std::vector<boost::shared_ptr<const T>> components;
		iterator found = find(entityID);
		if (found != end())
		{
			ComponentContainer::const_iterator it = found->second->begin();
			for (it; it != found->second->end(); ++it)
			{
				if ((*it)->typeName() == T::TypeName())
				{
					components.push_back(boost::dynamic_pointer_cast<const T>(*it));
				}
			}
		}
		return components;
	}
}
