#include "TransformComponent.h"
#include <graphics/Transform.h>
#include <json/json.h>

using namespace graphics;
using namespace serialisation;

namespace components
{
	TransformComponent::TransformComponent() :
		transform(new Transform)
	{

	}

	TransformComponent::TransformComponent(const TransformComponent& other) :
		transform(other.transform)
	{

	}

	TransformComponent::~TransformComponent()
	{

	}

	TransformComponent& TransformComponent::operator= (const TransformComponent& other)
	{
		transform = other.transform;
		return *this;
	}

	std::string TransformComponent::TypeName()
	{
		return "TransformComponent";
	}

	std::string TransformComponent::typeName() const
	{
		return TransformComponent::TypeName();
	}

	Serialisable* TransformComponent::clone() const
	{
		return new TransformComponent(*this);
	}

	Json::Value TransformComponent::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		data["transform"] = transform->serialise();
		return data;
	}

	void TransformComponent::deserialise(const Json::Value& data)
	{
		transform.reset(Serialiser::Deserialise<Transform>(data["transform"]));
	}
}