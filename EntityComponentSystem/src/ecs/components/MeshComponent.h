#pragma once
#include "EntityComponent.h"
#include "graphics/fwd.h"

namespace ecs
{
	class MeshComponent : public EntityComponent
	{
	public:
		graphics::Mesh_Ptr mesh;

		MeshComponent();
		MeshComponent(const MeshComponent& other);
		virtual ~MeshComponent();

		MeshComponent& operator= (const MeshComponent& other);

		virtual void serialise(Json::Value& componentArray);
		virtual void deserialise(Json::Value& componentDict);
	};
}
