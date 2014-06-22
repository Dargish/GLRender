#pragma once
#include <boost/shared_ptr.hpp>

#define DECL_CLASS( NAME ) \
	class NAME; \
	typedef boost::shared_ptr< NAME > NAME ## _Ptr; \
	typedef boost::shared_ptr< const NAME > NAME ## _Const_Ptr;

namespace ecs
{
	DECL_CLASS(World)
	DECL_CLASS(Entity)
	DECL_CLASS(EntitySystem)
	DECL_CLASS(EntityComponent)

	// Systems
	DECL_CLASS(RenderSystem)

	// Components
	DECL_CLASS(MeshComponent)
	DECL_CLASS(TransformComponent)
}

namespace Json
{
	class Value;
}