#pragma once

#include <GLRender/World/Component.h>

namespace glr
{
	struct TransformComponent : public Component
	{
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		TransformComponent() : scale(1, 1, 1) { }
	};
}