#include "MaterialComponent.h"
#include "graphics/Material.h"
#include <json/json.h>

using namespace graphics;
using namespace serialisation;

namespace components
{
	MaterialComponent::MaterialComponent()
	{

	}

	MaterialComponent::MaterialComponent(const MaterialComponent& other) :
		material(other.material)
	{

	}

	MaterialComponent::~MaterialComponent()
	{

	}

	MaterialComponent& MaterialComponent::operator= (const MaterialComponent& other)
	{
		material = other.material;
		return *this;
	}

	std::string MaterialComponent::TypeName()
	{
		return "MaterialComponent";
	}

	std::string MaterialComponent::typeName() const
	{
		return MaterialComponent::TypeName();
	}

	Serialisable* MaterialComponent::clone() const
	{
		return new MaterialComponent(*this);
	}

	Json::Value MaterialComponent::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		data["material"] = material->serialise();
		return data;
	}

	void MaterialComponent::deserialise(const Json::Value& data)
	{
		material.reset(Serialiser::Deserialise<Material>(data["material"]));
	}
}