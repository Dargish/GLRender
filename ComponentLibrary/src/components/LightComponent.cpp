#include "LightComponent.h"
#include "graphics/Light.h"
#include <json/json.h>

using namespace graphics;
using namespace serialisation;

namespace components
{
	LightComponent::LightComponent()
	{
	}
	
	LightComponent::LightComponent(const LightComponent& other) :
		light(other.light)
	{

	}

	LightComponent::~LightComponent()
	{
	}

	LightComponent& LightComponent::operator= (const LightComponent& other)
	{
		light = other.light;
		return *this;
	}

	std::string LightComponent::TypeName()
	{
		return "LightComponent";
	}

	std::string LightComponent::typeName() const
	{
		return LightComponent::TypeName();
	}

	Serialisable* LightComponent::clone() const
	{
		return new LightComponent(*this);
	}

	Json::Value LightComponent::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		data["light"] = light->serialise();
		return data;
	}

	void LightComponent::deserialise(const Json::Value& data)
	{
		light.reset(Serialiser::Deserialise<Light>(data["light"]));
	}
}
