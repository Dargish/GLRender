#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/World/Entity.h>
#include <GLRender/Graphics/Renderer.h>
#include <GLRender/Components/CameraComponent.h>
#include <GLRender/Components/TransformComponent.h>

namespace glr
{
	class Camera
	{
	public:
		Camera(Entity& entity);

		void update(float deltaTime);

	private:
		std::shared_ptr<CameraComponent> m_camera;
		std::shared_ptr<TransformComponent> m_transform;
	};
}