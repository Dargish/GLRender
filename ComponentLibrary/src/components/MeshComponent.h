#pragma once
#include "fwd.h"
#include "ecs/Component.h"
#include "graphics/fwd.h"

namespace components
{
	class MeshComponent : public ecs::Component
	{
	public:
		graphics::Mesh_Ptr mesh;

		MeshComponent();
		MeshComponent(const MeshComponent& other);
		virtual ~MeshComponent();
		MeshComponent& operator= (const MeshComponent& other);

		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);
	};
}
