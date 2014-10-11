#pragma once
#include "fwd.h"
#include "ecs/Component.h"
#include "graphics/fwd.h"

namespace components
{
	class LightComponent : public ecs::Component
	{
	public:
		graphics::lights::Light_Ptr light;

		// Helper function to convert the mesh type
		template< class T >
		boost::shared_ptr< T > lightAs()
		{
			return boost::dynamic_pointer_cast<T>(light);
		}

		template< class T >
		boost::shared_ptr< const T > lightAs() const
		{
			return boost::dynamic_pointer_cast<const T>(light);
		}

		LightComponent();
		LightComponent(const LightComponent& other);
		virtual ~LightComponent();
		LightComponent& operator= (const LightComponent& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);
	};
}
