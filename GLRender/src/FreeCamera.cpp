#include "FreeCamera.h"
#include <cmath>
#include <io/InputManager.h>
#include <core/MathUtils.h>

using namespace io;
using namespace graphics;

FreeCamera::FreeCamera() :
	m_yaw(-PI), m_pitch(0.0f)
{
	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;
	m_velocity.z = 0.0f;
	m_position.x = 1.0f;
	m_position.y = 1.0f;
	m_position.z = 5.0f;
	updateDirection();
	updateViewMatrix();
	if (!InputManager::HasMappedInput("Accelerate"))
	{
		InputManager::AddInput("Accelerate", sf::Keyboard::LShift);
	}
	if (!InputManager::HasMappedInput("Decelerate"))
	{
		InputManager::AddInput("Decelerate", sf::Keyboard::LControl);
	}
	if (!InputManager::HasMappedInput("Forward"))
	{
		InputManager::AddInput("Forward", sf::Keyboard::W);
	}
	if (!InputManager::HasMappedInput("Back"))
	{
		InputManager::AddInput("Back", sf::Keyboard::S);
	}
	if (!InputManager::HasMappedInput("Left"))
	{
		InputManager::AddInput("Left", sf::Keyboard::A);
	}
	if (!InputManager::HasMappedInput("Right"))
	{
		InputManager::AddInput("Right", sf::Keyboard::D);
	}
	if (!InputManager::HasMappedInput("Yaw"))
	{
		InputManager::AddInput("Yaw", Axis::X);
	}
	if (!InputManager::HasMappedInput("Pitch"))
	{
		InputManager::AddInput("Pitch", Axis::Y);
	}
}

void FreeCamera::update( float deltaTime )
{
	applyDrag( deltaTime );
	processInput( deltaTime );
	integrateVelocity( deltaTime );
	updateDirection();
	Camera::update(deltaTime);
}

void FreeCamera::applyDrag( float deltaTime )
{
	Vector3 drag = m_velocity * 10.0f * deltaTime;
	float dragLength = glm::length( drag );
	float velocityLength = glm::length( m_velocity );
	if ( dragLength > velocityLength || velocityLength < 0.1f )
	{
		m_velocity.x = 0.0f;
		m_velocity.y = 0.0f;
		m_velocity.z = 0.0f;
	}
	else
	{
		m_velocity -= drag;
	}
}

void FreeCamera::processInput( float deltaTime )
{
	Vector3 movement( 0.0f, 0.0f, 0.0f );
	float movementSpeed = InputManager::IsDown("Accelerate") ? MOVEMENT_SPEED * 5.0f : MOVEMENT_SPEED;
	movementSpeed = InputManager::IsDown("Decelerate") ? MOVEMENT_SPEED * 0.2f : MOVEMENT_SPEED;
	if (InputManager::IsDown("Forward"))
	{
		movement += m_direction * movementSpeed * deltaTime;
	}
	if (InputManager::IsDown("Back"))
	{
		movement -= m_direction * movementSpeed * deltaTime;
	}
	if (InputManager::IsDown("Left"))
	{
		movement -= m_right * movementSpeed * deltaTime;
	}
	if (InputManager::IsDown("Right"))
	{
		movement += m_right * movementSpeed * deltaTime;
	}
	m_yaw -= InputManager::FDelta("Yaw") * deltaTime * 0.1f;
	m_pitch += InputManager::FDelta("Pitch") * deltaTime * 0.1f;
	m_velocity += movement;
}

void FreeCamera::integrateVelocity( float deltaTime )
{
	m_position += m_velocity * deltaTime;
}

void FreeCamera::updateDirection()
{
	m_yaw = wrapAngle(m_yaw);
	m_pitch = constrainAngle(m_pitch);
	m_direction.x = std::sin( m_yaw ) * std::cos( m_pitch );
	m_direction.y = -std::sin(m_pitch);
	m_direction.z = std::cos(m_yaw) * std::cos(m_pitch);
	m_direction = glm::normalize(m_direction);
}
