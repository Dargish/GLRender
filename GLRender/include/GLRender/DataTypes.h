#pragma once

// STL
#include <string>

// GLM
#include <glm/glm.hpp>

namespace glrender
{
	typedef std::string string;
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef glm::mat4 Matrix4;
	typedef glm::vec4 Vector4;
	typedef glm::vec3 Vector3;
	typedef glm::vec2 Vector2;
	typedef glm::ivec2 Point2;
	typedef glm::ivec3 Point3;
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