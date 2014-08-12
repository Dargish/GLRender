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

		// Helper function to convert the mesh type
		template< class T >
		boost::shared_ptr< T > meshAs()
		{
			return boost::dynamic_pointer_cast<T>(mesh);
		}

		template< class T >
		boost::shared_ptr< const T > meshAs() const
		{
			return boost::dynamic_pointer_cast<const T>(mesh);
		}

		MeshComponent();
		MeshComponent(const MeshComponent& other);
		virtual ~MeshComponent();
		MeshComponent& operator= (const MeshComponent& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);
	};
}
