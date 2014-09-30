#pragma once
#include <graphics/Camera.h>

#define ROTATE_SPEED 0.01f
#define MOVEMENT_SPEED 100.0f

class FreeCamera : public graphics::Camera
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
