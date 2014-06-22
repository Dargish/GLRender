#pragma once
#include <boost/shared_ptr.hpp>

#define DECL_CLASS( NAME ) \
class NAME; \
	typedef boost::shared_ptr< NAME > NAME ## _Ptr; \
	typedef boost::shared_ptr< const NAME > NAME ## _Const_Ptr; 

namespace io
{
	DECL_CLASS(InputState)
	DECL_CLASS(InputAssignment)
	DECL_CLASS(KeyInputAssignment)
	DECL_CLASS(MouseButtonInputAssignment)
	DECL_CLASS(MouseAxisInputAssignment)
	DECL_CLASS(MappedInput)
	DECL_CLASS(InputManager)
}

DECL_CLASS(Window);

namespace sf
{
	DECL_CLASS(RenderWindow);
}