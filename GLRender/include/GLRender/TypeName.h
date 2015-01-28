#pragma once

#include <GLRender/DataTypes.h>

namespace glrender
{
	// Registers a type so that its class name can be retrieved.
	// Usage:
	//   REGISTER_TYPENAME(CLASS)
	//   string className = TypeNameTraits<CLASS>::name

	template<typename T>
	struct TypeNameTraits;
}

#define REGISTER_TYPENAME(CLASS) template <> struct glrender::TypeNameTraits<CLASS>\
{ static const glrender::string Name; };

#define DEFINE_TYPENAME(CLASS) \
const glrender::string glrender::TypeNameTraits<CLASS>::Name = #CLASS;