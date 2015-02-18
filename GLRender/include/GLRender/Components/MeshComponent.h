#pragma once
#include <GLRender/World/Component.h>
#include <GLRender/Graphics/Mesh.h>

namespace glr
{
	struct MeshComponent : public Component
	{
		std::shared_ptr<Mesh> mesh;
	};
}