#pragma once

#include <GLRender/DataTypes.h>
#include <GLRender/World/Entity.h>
#include <GLRender/Component/CameraComponent.h>
#include <GLRender/Component/TransformComponent.h>

namespace glr
{
	class GLRENDERAPI Camera
	{
	public:
		Camera(Entity& entity);

		void update(float deltaTime);

	private:
		std::shared_ptr<CameraComponent> m_camera;
		std::shared_ptr<TransformComponent> m_transform;
	};
}