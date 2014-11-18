#pragma once
#include "fwd.h"

namespace graphics
{
	struct Frustum
	{
		Vector3 corners[8];
	};

	class Camera
	{
	public:
		Camera();
		~Camera();

		Vector3 position() const;
		Vector3 direction() const;
		Vector3 right() const;
		Vector3 up() const;
		Matrix4 projMatrix() const;
		Matrix4 viewMatrix() const;
		Vector2 viewportSize() const;

		virtual void update(float deltaTime);

		void updateProjectionMatrix(int width, int height);

		Frustum frustum() const;

	protected:
		void updateViewMatrix();

		Vector3 m_position;
		Vector3 m_direction;
		Vector3 m_right;
		Vector3 m_up;
		Matrix4 m_projMatrix;
		Matrix4 m_viewMatrix;
		Vector2 m_viewportSize;
	};
}

