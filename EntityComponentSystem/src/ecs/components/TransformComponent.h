#pragma once
#include "EntityComponent.h"
#include <SFML/Graphics/Transform.hpp>
#include "core/TypeDefs.h"
#include "../fwd.h"

namespace ecs
{
	class TransformComponent : public EntityComponent
	{
	public:
		Matrix4 transform;

		TransformComponent();
		TransformComponent(const Matrix4& t);
		virtual ~TransformComponent();

		virtual void serialise(Json::Value& componentArray);
		virtual void deserialise(Json::Value& componentDict);
	};
}
