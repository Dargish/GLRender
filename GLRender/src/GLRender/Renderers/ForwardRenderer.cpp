#include <GLRender/Renderer/ForwardRenderer.h>
#include <GLRender/Component/ModelComponent.h>
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

	void ForwardRenderer::draw(Entity& camera, World& world, float /*deltaTime*/)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthMask(true);
		glDisable(GL_BLEND);
		//glDisable(GL_CULL_FACE);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shader.enable();

		m_shader.setValue("eyePos", Vector3(0, 0, 0));
		m_shader.setValue("proj", Matrix4());
		m_shader.setValue("view", Matrix4());
		m_shader.setValue("world", Matrix4());
		m_shader.setValue("world_it", Matrix4());

		std::shared_ptr<const ModelComponent> cModel;
		std::shared_ptr<const TransformComponent> cTransform;
		std::shared_ptr<const MaterialComponent> cMaterial;
		for (World::EntityMap::const_iterator it = world.begin(); it != world.end(); ++it)
		{
			const Entity& entity = it->second;
			if (entity.getComponent(cModel) && entity.getComponent(cTransform) && entity.getComponent(cMaterial))
			{
				cModel->model.draw();
			}
		}

		m_shader.disable();
	}
}