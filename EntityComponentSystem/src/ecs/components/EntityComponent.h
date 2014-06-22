#pragma once

#include "../fwd.h"

namespace ecs
{
	class EntityComponent
	{
	public:
		virtual ~EntityComponent() { }

		virtual void serialise(Json::Value& componentArray) = 0;
		virtual void deserialise(Json::Value& componentDict) = 0;
	};
}