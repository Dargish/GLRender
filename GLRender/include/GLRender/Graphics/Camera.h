#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/World/World.h>
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

		void render(World& world, Renderer& renderer);

	private:
		std::shared_ptr<CameraComponent> m_camera;
		std::shared_ptr<TransformComponent> m_transform;
	};
}