#pragma once
#include "fwd.h"
#include "ecs/Component.h"
#include "graphics/fwd.h"

namespace components
{
	class MaterialComponent : public ecs::Component
	{
	public:
		graphics::Material_Ptr material;

		MaterialComponent();
		MaterialComponent(const MaterialComponent& other);
		virtual ~MaterialComponent();
		MaterialComponent& operator= (const MaterialComponent& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);
	};
}

