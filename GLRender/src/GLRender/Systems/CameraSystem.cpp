#include <GLRender/System/CameraSystem.h>
#include <GLRender/Component/CameraComponent.h>
#include <GLRender/Component/TransformComponent.h>
#include <glm/gtx/transform.hpp>
#include <algorithm>

namespace glr
{
	void CameraSystem::update(World& world, float /*deltaTime*/)
	{
		std::shared_ptr<CameraComponent> camera;
		std::shared_ptr<const TransformComponent> transform;
		std::for_each(world.begin(), world.end(),
			[&camera, &transform](auto& p)
			{
				if (p.second.getComponent(camera) && p.second.getComponent(transform))
				{
					float near = camera->near;
					float far = camera->far;
					float fov = camera->fieldOfView;
					Vector2 viewportSize = camera->viewportSize;
					float ratio = viewportSize.x / viewportSize.y;
					camera->projMatrix = glm::perspective(fov, ratio, near, far);

					// Update view matrix
					Vector3 position = transform->position;
					Vector3 rot = transform->rotation;
					Vector3 direction(
						std::sin(rot.x) * std::cos(rot.y),
						-std::sin(rot.x),
						std::cos(rot.y) * std::cos(rot.x));
					direction = glm::normalize(direction);
					Vector3 right = glm::cross(direction, Vector3(0, 1, 0));
					right = glm::normalize(right);
					Vector3 up = glm::cross(right, direction);
					up = glm::normalize(up);
					camera->viewMatrix = glm::lookAt(position, position + direction, up);

					// Update frustum
					Matrix4 inverseViewProj = glm::inverse(camera->projMatrix * camera->viewMatrix);
					for (size_t i = 0; i < 8; ++i)
					{
						Vector4 pos(i & 1 ? 1.0f : -0.998f, i & 2 ? 1.0f : -0.998f, i & 4 ? 1.0f : -0.998f, 1.0f);
						pos = inverseViewProj * pos;
						camera->frustum.corners[i] = Vector3(pos.x / pos.w, pos.y / pos.w, pos.z / pos.w);
					}
				}
			} );
	}
}