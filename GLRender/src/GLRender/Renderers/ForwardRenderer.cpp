#include <GLRender/Renderer/ForwardRenderer.h>
#include <GLRender/Component/ModelComponent.h>
#include <GLRender/Component/CameraComponent.h>
#include <GLRender/Component/TransformComponent.h>
#include <GLRender/Component/MaterialComponent.h>
#include <GL/glew.h>

namespace glr
{
	ForwardRenderer::ForwardRenderer()
	{
		m_shader.addSubShader("data/shaders/basic.vert");
		m_shader.addSubShader("data/shaders/basic.frag");
		m_shader.link();
	}

	void ForwardRenderer::draw(Entity& cameraEntity, World& world, float /*deltaTime*/)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthMask(true);
		glDisable(GL_BLEND);
		//glDisable(GL_CULL_FACE);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shader.enable();

		{
			std::shared_ptr<const CameraComponent> camera;
			std::shared_ptr<const TransformComponent> transform;
			if (cameraEntity.getComponent(camera) &&
				cameraEntity.getComponent(transform))
			{
				m_shader.setValue("eyePos", transform->position);
				m_shader.setValue("proj", camera->projMatrix);
				m_shader.setValue("view", camera->viewMatrix);
			}
		}
		
		m_shader.setValue("world", Matrix4());
		m_shader.setValue("world_it", Matrix4());

		{
			std::shared_ptr<const ModelComponent> model;
			std::shared_ptr<const TransformComponent> transform;
			std::shared_ptr<const MaterialComponent> material;
			std::for_each(world.begin(), world.end(),
				[&model, &transform, &material](auto& p)
				{
					if (p.second.getComponent(model) &&
						p.second.getComponent(transform) &&
						p.second.getComponent(material))
					{
						model->model.draw();
					}
				} );
		}

		m_shader.disable();
	}
}