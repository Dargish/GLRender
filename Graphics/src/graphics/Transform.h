#pragma once
#include "fwd.h"
#include <SFML/Graphics/Transform.hpp>
#include "serialisation/Serialiser.h"

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

		Vector3 direction() const;
		Matrix4 world() const;

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);
	};
}
