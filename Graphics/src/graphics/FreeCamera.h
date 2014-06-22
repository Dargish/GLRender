#pragma once

#include "Camera.h"

namespace graphics
{
	class FreeCamera : public Camera
	{
	public:
		FreeCamera();

		virtual void update( float deltaTime );

	private:
		void applyDrag( float deltaTime );
		void processInput( float deltaTime );
		void integrateVelocity( float deltaTime );
		void updateDirection();

		float m_yaw;
		float m_pitch;
		Vector3 m_velocity;
	};
}
