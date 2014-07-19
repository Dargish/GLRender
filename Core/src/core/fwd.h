#pragma once

#include <boost/shared_ptr.hpp>

#define DECL_CLASS( NAME ) \
class NAME; \
	typedef boost::shared_ptr< NAME > NAME ## _Ptr; \
	typedef boost::shared_ptr< const NAME > NAME ## _Const_Ptr; 

namespace sf
{
	DECL_CLASS(RenderWindow);
}

namespace Json
{
	class Value;
}