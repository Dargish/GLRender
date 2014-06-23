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
		static Vector3 Up, Down, Left, Right, Forward, Backward;

		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

		TransformComponent();
		TransformComponent(const Vector3& position, const Vector3& rotation, const Vector3& scale);
		TransformComponent(const TransformComponent& t);
		virtual ~TransformComponent();

		TransformComponent& operator= (const TransformComponent& t);

		Matrix4 transform() const;

		virtual void serialise(Json::Value& componentArray);
		virtual void deserialise(Json::Value& componentDict);
	};
}
