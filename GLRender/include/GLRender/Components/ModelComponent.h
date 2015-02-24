#pragma once
#include <GLRender/World/Component.h>
#include <GLRender/Graphics/Model.h>

namespace glr
{
	struct ModelComponent : public Component
	{
		Model model;
	};
}