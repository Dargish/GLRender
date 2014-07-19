#pragma once
#include "fwd.h"
#include <graphics/fwd.h>
#include "ecs/Component.h"

namespace components
{
	class TransformComponent : public ecs::Component
	{
	public:
		graphics::Transform_Ptr transform;

		TransformComponent();
		TransformComponent(const TransformComponent& other);
		virtual ~TransformComponent();
		TransformComponent& operator= (const TransformComponent& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);
	};
}
