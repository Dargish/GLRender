#pragma once
#include "fwd.h"

namespace graphics
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		Vector3 position();
		Vector3 direction();
		Vector3 right();
		Vector3 up();
		Matrix4 projMatrix();
		Matrix4 viewMatrix();

		virtual void update(float deltaTime);

		void updateProjectionMatrix(int width, int height);

	protected:
		void updateViewMatrix();

		Vector3 m_position;
		Vector3 m_direction;
		Vector3 m_right;
		Vector3 m_up;
		Matrix4 m_projMatrix;
		Matrix4 m_viewMatrix;
	};
}

