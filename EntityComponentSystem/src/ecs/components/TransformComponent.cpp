#include "TransformComponent.h"
#include <json/json.h>
#include "core/TypeDefs.h"
#include <glm/gtx/transform.hpp>

namespace ecs
{
	Vector3 TransformComponent::Up(0.0f, 1.0f, 0.0f);
	Vector3 TransformComponent::Down(0.0f, -1.0f, 0.0f);
	Vector3 TransformComponent::Left(-1.0f, 0.0f, 0.0f);
	Vector3 TransformComponent::Right(1.0f, 0.0f, 0.0f);
	Vector3 TransformComponent::Forward(0.0f, 0.0f, 1.0f);
	Vector3 TransformComponent::Backward(0.0f, 0.0f, -1.0f);

	TransformComponent::TransformComponent() :
		position(0.0f, 0.0f, 0.0f),
		rotation(0.0f, 0.0f, 0.0f),
		scale(1.0f, 1.0f, 1.0f)
	{
	}

	TransformComponent::TransformComponent(const Vector3& position, const Vector3& rotation, const Vector3& scale) :
		position(position),
		rotation(rotation),
		scale(scale)
	{

	}

	TransformComponent::TransformComponent(const TransformComponent& other) :
		position(other.position),
		rotation(other.rotation),
		scale(other.scale)
	{
	}

	TransformComponent::~TransformComponent()
	{
	}

	TransformComponent& TransformComponent::operator= (const TransformComponent& other)
	{
		position = other.position;
		rotation = other.rotation;
		scale = other.scale;
		return *this;
	}

	Matrix4 TransformComponent::transform() const
	{
		Matrix4 positionMtx = glm::translate(position);
		Matrix4 yawMtx = glm::rotate(rotation.x, Up);
		Matrix4 pitchMtx = glm::rotate(rotation.y, Right);
		Matrix4 rollMtx = glm::rotate(rotation.z, Forward);
		Matrix4 scaleMtx = glm::scale(scale);
		return positionMtx * yawMtx * pitchMtx * rollMtx * scaleMtx;
	}

	void TransformComponent::serialise(Json::Value& componentArray)
	{
		Json::Value componentDict;
		componentDict["componentType"] = "Transform";
		Json::Value positionArray = Json::Value(Json::arrayValue);
		Json::Value rotationArray = Json::Value(Json::arrayValue);
		Json::Value scaleArray = Json::Value(Json::arrayValue);
		for (size_t r = 0; r < 3; ++r)
		{
			positionArray.append(position[r]);
			rotationArray.append(rotation[r]);
			scaleArray.append(scale[r]);
		}
		componentDict["position"] = positionArray;
		componentDict["rotation"] = rotationArray;
		componentDict["scale"] = scaleArray;
		componentArray.append(componentDict);
	}

	void TransformComponent::deserialise(Json::Value& componentDict)
	{
		if (componentDict["componentType"].asString() != "Transform")
		{
			throw std::runtime_error("Invalid component type, expected 'Transform' received '" + componentDict["componentType"].asString() + "'");
		}
		for (size_t r = 0; r < 3; ++r)
		{
			position[r] = (float)componentDict["transform"][r].asDouble();
			rotation[r] = (float)componentDict["rotation"][r].asDouble();
			scale[r] = (float)componentDict["scale"][r].asDouble();
		}
	}
}