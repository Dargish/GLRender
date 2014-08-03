#pragma once
#include "fwd.h"
#include "graphics/fwd.h"
#include <map>
#include <vector>
#include <ecs/EntitySystem.h>

namespace systems
{

	class RenderSystem : public ecs::EntitySystem
	{
	public:
		virtual ~RenderSystem();

		virtual void componentAdded(const ecs::World_Ptr& world, const ecs::EntityID& entityID);
		virtual void componentRemoved(const ecs::World_Ptr& world, const ecs::EntityID& entityID);
		virtual void entityDestroyed(const ecs::EntityID& entityID);

	protected:
		virtual void _draw(const ecs::World_Ptr& world, float deltaTime);

	private:
		typedef std::vector<graphics::Mesh_Ptr> MeshVector;
		struct RenderCache
		{
			graphics::Material_Ptr material;
			graphics::Transform_Ptr transform;
			MeshVector meshes;
		};
		typedef std::vector<RenderCache> RenderCacheVector;
		typedef std::map<graphics::Shader_Ptr, RenderCacheVector> RenderCacheMap;

		RenderCacheMap m_renderCache;
	};
}