#pragma once

#include <GLRender/Component/Component.h>

namespace glr
{
	struct Frustum
	{
		Vector3 corners[8];
	};

	struct CameraComponent : public Component
	{
		// Modified by user
		float near;
		float far;
		float fieldOfView;

		// Modified when window size changes
		Vector2 viewportSize;

		// Modified by camera system
		Matrix4 projMatrix;
		Matrix4 viewMatrix;
		Frustum frustum;

		CameraComponent() : near(0.01f), far(10000.0f), fieldOfView(60.0f) {}
	};
}