#include <GLRender/Renderer/ForwardRenderer.h>
#include <GLRender/Component/ModelComponent.h>
#include <GLRender/Component/TransformComponent.h>
#include <GLRender/Component/MaterialComponent.h>

namespace glr
{
	void ForwardRenderer::draw(World& world, float deltaTime)
	{
		std::shared_ptr<const ModelComponent> cModel;
		std::shared_ptr<const TransformComponent> cTransform;
		std::shared_ptr<const MaterialComponent> cMaterial;
		for (World::EntityMap::const_iterator it = world.begin(); it != world.end(); ++it)
		{
			const Entity& entity = it->second;
			if (entity.getComponent(cModel) && entity.getComponent(cTransform) && entity.getComponent(cMaterial))
			{

			}
		}
	}
}