#pragma once
#include <boost/shared_ptr.hpp>

#define DECL_CLASS( NAME ) \
	class NAME; \
	typedef boost::shared_ptr< NAME > NAME ## _Ptr; \
	typedef boost::shared_ptr< const NAME > NAME ## _Const_Ptr;

namespace graphics
{
	DECL_CLASS(Camera);
	DECL_CLASS(Mesh);
	DECL_CLASS(Primitive);
	DECL_CLASS(Cube);
	DECL_CLASS(Shader);
}

namespace Json
{
	class Value;
}