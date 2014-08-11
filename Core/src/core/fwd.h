#pragma once

#include <boost/shared_ptr.hpp>

#include <glm/glm.hpp>

typedef unsigned char ubyte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef glm::mat4 Matrix4;
typedef glm::vec4 Vector4;
typedef glm::vec3 Vector3;
typedef glm::ivec2 Point2;

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

namespace rapidxml
{
	template<class Ch = char>
	class xml_node;
}