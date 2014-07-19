#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <json/json.h>

using namespace serialisation;

namespace graphics
{
	Vector3 Transform::Up(0.0f, 1.0f, 0.0f);
	Vector3 Transform::Down(0.0f, -1.0f, 0.0f);
	Vector3 Transform::Left(-1.0f, 0.0f, 0.0f);
	Vector3 Transform::Right(1.0f, 0.0f, 0.0f);
	Vector3 Transform::Forward(0.0f, 0.0f, 1.0f);
	Vector3 Transform::Backward(0.0f, 0.0f, -1.0f);

	Transform::Transform() :
		position(0.0f, 0.0f, 0.0f),
		rotation(0.0f, 0.0f, 0.0f),
		scale(1.0f, 1.0f, 1.0f)
	{
	}

	Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale) :
		position(position),
		rotation(rotation),
		scale(scale)
	{

	}

	Transform::Transform(const Transform& other) :
		position(other.position),
		rotation(other.rotation),
		scale(other.scale)
	{
	}

	Transform::~Transform()
	{
	}

	Transform& Transform::operator= (const Transform& other)
	{
		position = other.position;
		rotation = other.rotation;
		scale = other.scale;
		return *this;
	}

	Matrix4 Transform::world() const
	{
		Matrix4 positionMtx = glm::translate(position);
		Matrix4 yawMtx = glm::rotate(rotation.x, Up);
		Matrix4 pitchMtx = glm::rotate(rotation.y, Right);
		Matrix4 rollMtx = glm::rotate(rotation.z, Forward);
		Matrix4 scaleMtx = glm::scale(scale);
		return positionMtx * yawMtx * pitchMtx * rollMtx * scaleMtx;
	}

	std::string Transform::TypeName()
	{
		return "Transform";
	}

	std::string Transform::typeName() const
	{
		return Transform::TypeName();
	}

	Serialisable* Transform::clone() const
	{
		return new Transform(*this);
	}

	Json::Value Transform::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		Json::Value positionArray = Json::Value(Json::arrayValue);
		Json::Value rotationArray = Json::Value(Json::arrayValue);
		Json::Value scaleArray = Json::Value(Json::arrayValue);
		for (size_t r = 0; r < 3; ++r)
		{
			positionArray.append(position[r]);
			rotationArray.append(rotation[r]);
			scaleArray.append(scale[r]);
		}
		data["position"] = positionArray;
		data["rotation"] = rotationArray;
		data["scale"] = scaleArray;
		return data;
	}

	void Transform::deserialise(const Json::Value& data)
	{
		for (size_t r = 0; r < 3; ++r)
		{
			position[r] = (float)data["position"][r].asDouble();
			rotation[r] = (float)data["rotation"][r].asDouble();
			scale[r] = (float)data["scale"][r].asDouble();
		}
	}
}