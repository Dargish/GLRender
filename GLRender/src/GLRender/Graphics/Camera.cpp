#include <GLRender/Graphics/Camera.h>
#include <glm/gtx/transform.hpp>

namespace glr
{
	Camera::Camera(Entity& entity)
	{
		if(!entity.getComponent(m_camera))
		{
			m_camera = entity.addComponent<CameraComponent>();
		}
		if(!entity.getComponent(m_transform))
		{
			m_transform = entity.addComponent<TransformComponent>();
		}
	}

	void Camera::update(float /*deltaTime*/)
	{
		// Update projection matrix
		float near = m_camera->near;
		float far = m_camera->far;
		float fov = m_camera->fieldOfView;
		Vector2 viewportSize = m_camera->viewportSize;
		float ratio = viewportSize.x / viewportSize.y;
		m_camera->projMatrix = glm::perspective(fov, ratio, near, far);

		// Update view matrix
		Vector3 position = m_transform->position;
		Vector3 rot = m_transform->rotation;
		Vector3 direction(
			std::sin(rot.x) * std::cos(rot.y),
			-std::sin(rot.x),
			std::cos(rot.y) * std::cos(rot.x));
		direction = glm::normalize(direction);
		Vector3 right = glm::cross(direction, Vector3(0, 1, 0));
		right = glm::normalize(right);
		Vector3 up = glm::cross(right, direction);
		up = glm::normalize(up);
		m_camera->viewMatrix = glm::lookAt(position, position + direction, up);

		// Update frustum
		Matrix4 inverseViewProj = glm::inverse(m_camera->projMatrix * m_camera->viewMatrix);
		for (size_t i = 0; i < 8; ++i)
		{
			Vector4 pos(i & 1 ? 1.0f : -0.998f, i & 2 ? 1.0f : -0.998f, i & 4 ? 1.0f : -0.998f, 1.0f);
			pos = inverseViewProj * pos;
			m_camera->frustum.corners[i] = Vector3(pos.x / pos.w, pos.y / pos.w, pos.z / pos.w);
		}
	}
}