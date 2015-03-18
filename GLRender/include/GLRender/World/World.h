#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/World/Entity.h>

#include <map>

namespace glr
{
	typedef std::map<string, Entity> EntityMap;

	class GLRENDERAPI World
	{
	public:
		typedef EntityMap::size_type size_type;
		typedef EntityMap::iterator iterator;
		typedef EntityMap::const_iterator const_iterator;

		World();

		// Entity creation
		Entity& createEntity(const string& name);
		Entity& entity(const string& name);

		// Iterator methods
		iterator begin();
		const_iterator begin() const;		
		iterator end();
		const_iterator end() const;

		size_type size() const;

		// Find methods
		bool hasEntity(const string& name);

		// Helper methods
		Entity& addModel(const string& name, const string& modelPath);
		Entity& addCamera(const string& name);

	private:
		EntityMap m_entities;
	};
}