#include "RenderSystem.h"
#include <GL/glew.h>
#include "ecs/World.h"
#include "components/TransformComponent.h"
#include "components/MeshComponent.h"
#include "components/MaterialComponent.h"
#include "components/LightComponent.h"
#include "graphics/lights/Light.h"
#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Transform.h"
#include "graphics/Camera.h"
#include "graphics/FrameBuffer.h"
#include "graphics/Texture.h"
#include <vector>

using namespace graphics;
using namespace ecs;
using namespace components;

namespace systems
{
	RenderSystem::RenderSystem() :
		m_frameBuffer(new FrameBuffer)
	{
	}

	RenderSystem::~RenderSystem()
	{
	}

	void RenderSystem::resetFrameBufferSize(const Point2& size)
	{
		RGBABuffer_Ptr diffuse(new RGBABuffer(size.x, size.y));
		RGBABuffer_Ptr normal(new RGBABuffer(size.x, size.y));
		m_frameBuffer->addTextureTarget("g_diffuse", diffuse);
		m_frameBuffer->addTextureTarget("g_normal", normal);
	}

	void RenderSystem::componentAdded(const World_Ptr& world, const EntityID& entityID)
	{
		if (world->hasComponent(entityID, MeshComponent::TypeName()) &&
			world->hasComponent(entityID, TransformComponent::TypeName()) &&
			world->hasComponent(entityID, MaterialComponent::TypeName()))
		{
			m_interestingEntities.insert(entityID);
		}
		if (world->hasComponent(entityID, LightComponent::TypeName()))
		{
			m_interestingEntities.insert(entityID);
		}
	}

	void RenderSystem::componentRemoved(const World_Ptr& world, const EntityID& entityID)
	{
		if (world->hasComponent(entityID, MeshComponent::TypeName()) &&
			world->hasComponent(entityID, TransformComponent::TypeName()) &&
			world->hasComponent(entityID, MaterialComponent::TypeName()))
		{
			return;
		}
		if (world->hasComponent(entityID, LightComponent::TypeName()))
		{
			return;
		}
		m_interestingEntities.erase(entityID);
	}

	void RenderSystem::entityDestroyed(const EntityID& entityID)
	{
		m_interestingEntities.erase(entityID);
	}

	void RenderSystem::_draw(const World_Ptr& world, float deltaTime)
	{
		m_lightCache.clear();
		m_renderCache.clear();
		{
			EntityID_Set::iterator it = m_interestingEntities.begin();
			for (; it != m_interestingEntities.end(); ++it)
			{
				std::vector<MeshComponent_Ptr> meshComponents = world->components<MeshComponent>(*it);
				TransformComponent_Ptr transformComponent = world->component<TransformComponent>(*it);
				MaterialComponent_Ptr materialComponent = world->component<MaterialComponent>(*it);

				if (!meshComponents.empty() && transformComponent && materialComponent)
				{
					RenderCache renderCache;
					renderCache.material = materialComponent->material;
					renderCache.transform = transformComponent->transform;

					std::vector<MeshComponent_Ptr>::iterator it = meshComponents.begin();
					for (; it != meshComponents.end(); ++it)
					{
						renderCache.meshes.push_back((*it)->mesh);
					}

					Shader_Ptr shader = renderCache.material->shader();
					m_renderCache[shader].push_back(renderCache);
				}
				else
				{
					LightComponent_Ptr lightComponent = world->component<LightComponent>(*it);
					if (lightComponent)
					{
						m_lightCache.push_back(lightComponent->light);
					}
				}
			}
		}
		m_frameBuffer->bind();
		glEnable(GL_DEPTH_TEST);
		glDepthMask(true);
		glDisable(GL_BLEND);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		{
			RenderCacheMap::iterator it = m_renderCache.begin();
			for (; it != m_renderCache.end(); ++it)
			{
				Shader_Ptr shader = it->first;
				Shader::Enable(shader);
				shader->setValue("proj", world->camera()->projMatrix());
				shader->setValue("view", world->camera()->viewMatrix());
				RenderCacheVector::iterator rit = it->second.begin();
				for (; rit != it->second.end(); ++rit)
				{
					shader->setValue("world", rit->transform->world());
					shader->setValue("world_it", glm::transpose(glm::inverse(rit->transform->world())));
					rit->material->applyToShader();
					MeshVector::iterator mit = rit->meshes.begin();
					for (; mit != rit->meshes.end(); ++mit)
					{
						(*mit)->draw(deltaTime);
					}
				}
				Shader::Disable(shader);
			}
		}
		m_frameBuffer->bindForRead();
		glDisable(GL_DEPTH_TEST);
		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (LightCache::iterator it = m_lightCache.begin(); it != m_lightCache.end(); ++it)
		{
			(*it)->light(m_frameBuffer, world->camera(), deltaTime);
		}
		m_frameBuffer->unbind();
	}
}