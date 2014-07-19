#pragma once
#include "fwd.h"
#include <SFML/Graphics/Transform.hpp>
#include "core/TypeDefs.h"
#include "serialisation/Serialiser.h"

// ToDo: Move this somewhere sensible
namespace Json
{
	class Value;
}

namespace graphics
{
	class Transform : public serialisation::Serialisable
	{
	public:
		static Vector3 Up, Down, Left, Right, Forward, Backward;

		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

		Transform();
		Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale);
		Transform(const Transform& t);
		virtual ~Transform();
		Transform& operator= (const Transform& t);

		Matrix4 world() const;

		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);
	};
}
