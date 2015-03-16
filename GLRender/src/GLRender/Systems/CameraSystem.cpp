#include <GLRender/System/CameraSystem.h>
#include <GLRender/Component/CameraComponent.h>
#include <GLRender/Component/TransformComponent.h>
#include <glm/gtx/transform.hpp>

namespace glr
{
	void CameraSystem::update(World& world, float /*deltaTime*/)
	{
		std::shared_ptr<CameraComponent> cCamera;
		std::shared_ptr<const TransformComponent> cTransform;
		for (World::EntityMap::iterator it = world.begin(); it != world.end(); ++it)
		{
			Entity& entity = it->second;
			if (entity.getComponent(cCamera) && entity.getComponent(cTransform))
			{
				float near = cCamera->near;
				float far = cCamera->far;
				float fov = cCamera->fieldOfView;
				Vector2 viewportSize = cCamera->viewportSize;
				float ratio = viewportSize.x / viewportSize.y;
				cCamera->projMatrix = glm::perspective(fov, ratio, near, far);

				// Update view matrix
				Vector3 position = cTransform->position;
				Vector3 rot = cTransform->rotation;
				Vector3 direction(
					std::sin(rot.x) * std::cos(rot.y),
					-std::sin(rot.x),
					std::cos(rot.y) * std::cos(rot.x));
				direction = glm::normalize(direction);
				Vector3 right = glm::cross(direction, Vector3(0, 1, 0));
				right = glm::normalize(right);
				Vector3 up = glm::cross(right, direction);
				up = glm::normalize(up);
				cCamera->viewMatrix = glm::lookAt(position, position + direction, up);

				// Update frustum
				Matrix4 inverseViewProj = glm::inverse(cCamera->projMatrix * cCamera->viewMatrix);
				for (size_t i = 0; i < 8; ++i)
				{
					Vector4 pos(i & 1 ? 1.0f : -0.998f, i & 2 ? 1.0f : -0.998f, i & 4 ? 1.0f : -0.998f, 1.0f);
					pos = inverseViewProj * pos;
					cCamera->frustum.corners[i] = Vector3(pos.x / pos.w, pos.y / pos.w, pos.z / pos.w);
				}
			}
		}
	}
}