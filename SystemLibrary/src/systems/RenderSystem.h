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
		RenderSystem();
		virtual ~RenderSystem();

		void resetFrameBufferSize(const Point2& size);

		virtual void componentAdded(const ecs::World_Ptr& world, const ecs::EntityID& entityID);
		virtual void componentRemoved(const ecs::World_Ptr& world, const ecs::EntityID& entityID);
		virtual void entityDestroyed(const ecs::EntityID& entityID);

	protected:
		virtual void _update(const ecs::World_Ptr& world, float deltaTime);
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

		typedef std::vector<graphics::lights::Light_Ptr> LightCache;

		LightCache m_lightCache;
		RenderCacheMap m_renderCache;
		graphics::FrameBuffer_Ptr m_frameBuffer;
		graphics::Shader_Ptr m_debugShader;
		graphics::primitives::ScreenQuad_Ptr m_screenQuad;

		bool m_dbg_showColor;
		bool m_dbg_showNormal;
		bool m_dbg_showRoughness;
		bool m_dbg_showMetallicity;
	};
}