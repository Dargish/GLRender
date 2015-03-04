#include <GLRender/Renderer/ForwardRenderer.h>
#include <GLRender/Component/ModelComponent.h>
#include <GLRender/Component/TransformComponent.h>
#include <GLRender/Component/MaterialComponent.h>
#include <GLRender/Graphics/Shader.h>
#include <GL/glew.h>

namespace glr
{
	void ForwardRenderer::draw(World& world, float /*deltaTime*/)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthMask(true);
		glDisable(GL_BLEND);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Shader shader;
		shader.addSubShader("data/shaders/basic.vert");
		shader.addSubShader("data/shaders/basic.frag");
		shader.link();

		shader.setValue("eyePos", Vector3(0,0,0));
		shader.setValue("proj", Matrix4());
		shader.setValue("view", Matrix4());
		shader.setValue("world", Matrix4());
		shader.setValue("world_it", Matrix4());

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
	}
}