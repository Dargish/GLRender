#include "RenderSystem.h"
#include <GL/glew.h>
#include "ecs/World.h"
#include "components/TransformComponent.h"
#include "components/MeshComponent.h"
#include "components/MaterialComponent.h"
#include "components/LightComponent.h"
#include "graphics/lights/Light.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Material.h"
#include "graphics/Transform.h"
#include "graphics/Camera.h"
#include "graphics/FrameBuffer.h"
#include "graphics/Texture.h"
#include <vector>
#include <io/InputManager.h>
#include <graphics/primitives/ScreenQuad.h>

using namespace graphics;
using namespace graphics::primitives;
using namespace ecs;
using namespace components;
using namespace io;

namespace systems
{
	RenderSystem::RenderSystem() :
		m_frameBuffer(new FrameBuffer),
		m_screenQuad(new ScreenQuad),
		m_dbg_showColor(false),
		m_dbg_showNormal(false),
		m_dbg_showRoughness(false),
		m_dbg_showMetallicity(false)
	{
		if (!InputManager::HasMappedInput("Debug_ShowColor"))
		{
			InputManager::AddInput("Debug_ShowColor", sf::Keyboard::F1);
		}
		if (!InputManager::HasMappedInput("Debug_ShowNormal"))
		{
			InputManager::AddInput("Debug_ShowNormal", sf::Keyboard::F2);
		}
		if (!InputManager::HasMappedInput("Debug_ShowRoughness"))
		{
			InputManager::AddInput("Debug_ShowRoughness", sf::Keyboard::F3);
		}
		if (!InputManager::HasMappedInput("Debug_ShowMetallicity"))
		{
			InputManager::AddInput("Debug_ShowMetallicity", sf::Keyboard::F4);
		}
		if (!InputManager::HasMappedInput("Debug_ShowDepth"))
		{
			InputManager::AddInput("Debug_ShowDepth", sf::Keyboard::F5);
		}
	}

	RenderSystem::~RenderSystem()
	{
	}

	void RenderSystem::resetFrameBufferSize(const Point2& size)
	{
		RGBABuffer_Ptr A(new RGBABuffer(size.x, size.y));
		RGBABuffer_Ptr B(new RGBABuffer(size.x, size.y));
		FloatBuffer_Ptr C(new FloatBuffer(size.x, size.y));
		m_frameBuffer->addTextureTarget("g_A", A);
		m_frameBuffer->addTextureTarget("g_B", B);
		m_frameBuffer->addTextureTarget("g_C", C);
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

	void RenderSystem::_update(const World_Ptr& world, float deltaTime)
	{
		if (InputManager::Clicked("Debug_ShowColor"))
		{
			m_dbg_showColor = !m_dbg_showColor;
			m_dbg_showNormal = false;
			m_dbg_showRoughness = false;
			m_dbg_showMetallicity = false;
			m_dbg_showDepth = false;
		}
		if (InputManager::Clicked("Debug_ShowNormal"))
		{
			m_dbg_showColor = false;
			m_dbg_showNormal = !m_dbg_showNormal;
			m_dbg_showRoughness = false;
			m_dbg_showMetallicity = false;
			m_dbg_showDepth = false;
		}
		if (InputManager::Clicked("Debug_ShowRoughness"))
		{
			m_dbg_showColor = false;
			m_dbg_showNormal = false;
			m_dbg_showRoughness = !m_dbg_showRoughness;
			m_dbg_showMetallicity = false;
			m_dbg_showDepth = false;
		}
		if (InputManager::Clicked("Debug_ShowMetallicity"))
		{
			m_dbg_showColor = false;
			m_dbg_showNormal = false;
			m_dbg_showRoughness = false;
			m_dbg_showMetallicity = !m_dbg_showMetallicity;
			m_dbg_showDepth = false;
		}
		if (InputManager::Clicked("Debug_ShowDepth"))
		{
			m_dbg_showColor = false;
			m_dbg_showNormal = false;
			m_dbg_showRoughness = false;
			m_dbg_showMetallicity = false;
			m_dbg_showDepth = !m_dbg_showDepth;
		}
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
				shader->setValue("eyePos", world->camera()->position());
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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (m_dbg_showColor || m_dbg_showNormal || m_dbg_showRoughness || m_dbg_showMetallicity || m_dbg_showDepth)
		{
			if (!m_debugShader)
			{
				m_debugShader = Shader::Load("ShowDebug");
			}
			Shader::Enable(m_debugShader);
			m_frameBuffer->bindTargets(m_debugShader);
			m_debugShader->setValue("proj", world->camera()->projMatrix());
			m_debugShader->setValue("view", world->camera()->viewMatrix());
			m_debugShader->setValue("eyePos", world->camera()->position());

			m_debugShader->setValue("drawColor", m_dbg_showColor ? 1.0f : 0.0f);
			m_debugShader->setValue("drawNormal", m_dbg_showNormal ? 1.0f : 0.0f);
			m_debugShader->setValue("drawRoughness", m_dbg_showRoughness ? 1.0f : 0.0f);
			m_debugShader->setValue("drawMetallicity", m_dbg_showMetallicity ? 1.0f : 0.0f);
			m_debugShader->setValue("drawDepth", m_dbg_showDepth ? 1.0f : 0.0f);

			m_screenQuad->setEyeVec(world->camera());
			m_screenQuad->draw(deltaTime);
			Shader::Disable(m_debugShader);
		}
		else
		{
			for (LightCache::iterator it = m_lightCache.begin(); it != m_lightCache.end(); ++it)
			{
				(*it)->light(m_frameBuffer, world->camera(), deltaTime);
			}
		}
		m_frameBuffer->unbind();
	}
}