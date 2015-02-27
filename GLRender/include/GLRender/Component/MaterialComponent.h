#pragma once
#include <GLRender/Component/Component.h>
#include <GLRender/Graphics/Material.h>

namespace glr
{
	struct MaterialComponent : public Component
	{
		Material material;
	};
}