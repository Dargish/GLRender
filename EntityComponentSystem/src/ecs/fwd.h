#pragma once
#include <core/fwd.h>
#include <boost/uuid/uuid.hpp>
#include <set>
#include <map>
#include <vector>

namespace ecs
{
	DECL_CLASS(World)
	DECL_CLASS(EntitySystem)
	DECL_CLASS(Component)

	typedef boost::uuids::uuid EntityID;
	typedef std::set<EntityID> EntityID_Set;
	typedef std::vector<Component_Ptr> Component_Vector;
	typedef std::vector<Component_Const_Ptr> Component_Const_Vector;
	typedef std::map<EntityID, Component_Vector> Entity_Map;
	typedef std::set<EntitySystem_Ptr> Systems_Set;
}