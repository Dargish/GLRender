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
		MeshComponent(const graphics::Mesh_Ptr& m);
		virtual ~MeshComponent();

		virtual void serialise(Json::Value& componentArray);
		virtual void deserialise(Json::Value& componentDict);
	};
}
