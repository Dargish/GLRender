#pragma once
#include <GLRender/Component/Component.h>
#include <GLRender/Graphics/Model.h>

namespace glr
{
	struct ModelComponent : public Component
	{
		Model model;
	};
}