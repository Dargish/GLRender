#pragma once

#include <GLRender/World/Component.h>

namespace glr
{
	struct Frustum
	{
		Vector3 corners[8];
	};

	struct CameraComponent : public Component
	{
		float near;
		float far;
		float fieldOfView;
		Matrix4 projMatrix;
		Matrix4 viewMatrix;
		Vector2 viewportSize;
		Frustum frustum;

		CameraComponent() : near(0.01f), far(10000.0f), fieldOfView(60.0f) {}
	};
}