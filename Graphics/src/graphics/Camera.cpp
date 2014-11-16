#include "Camera.h"
#include <glm/gtx/transform.hpp>

namespace graphics
{
	Camera::Camera() :
		m_position(0.0f, 0.0f, 0.0f),
		m_direction(0.0f, 1.0f, 0.0f),
		m_right(0.0f, 0.0f, 1.0f),
		m_up(0.0f, 1.0f, 0.0f)
	{
	}

	Camera::~Camera()
	{
	}

	Vector3 Camera::position()
	{
		return m_position;
	}

	Vector3 Camera::direction()
	{
		return m_direction;
	}

	Vector3 Camera::right()
	{
		return m_right;
	}

	Vector3 Camera::up()
	{
		return m_up;
	}

	Matrix4 Camera::projMatrix()
	{
		return m_projMatrix;
	}

	Matrix4 Camera::viewMatrix()
	{
		return m_viewMatrix;
	}

	void Camera::update(float deltaTime)
	{
		updateViewMatrix();
	}

	void Camera::updateProjectionMatrix(int width, int height)
	{
		m_projMatrix = glm::perspective(60.0f, float(width) / float(height), 0.01f, 10000.0f);
	}

	Frustum Camera::frustum() const
	{
		Matrix4 inverseViewProj = glm::inverse(m_projMatrix * m_viewMatrix);
		Frustum frustum;
		for (size_t i = 0; i < 8; ++i)
		{
			Vector4 pos(i & 1 ? 1.0f : -0.998f, i & 2 ? 1.0f : -0.998f, i & 4 ? 1.0f : -0.998f, 1.0f);
			pos = inverseViewProj * pos;
			frustum.corners[i] = Vector3(pos.x / pos.w, pos.y / pos.w, pos.z / pos.w);
		}
		return frustum;
	}

	void Camera::updateViewMatrix()
	{
		m_right = glm::cross(m_direction, Vector3(0, 1, 0));
		m_right = glm::normalize(m_right);
		m_up = glm::cross(m_right, m_direction);
		m_up = glm::normalize(m_up);
		m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);
	}
}
