#pragma once

#include "fwd.h"

namespace graphics
{
	class Mesh
	{
	public:
		virtual ~Mesh();

		virtual void serialise(Json::Value& jsonArray) = 0;
		virtual void deserialise(Json::Value& jsonDict) = 0;

		virtual void draw(float deltaTime) = 0;
	};
}

