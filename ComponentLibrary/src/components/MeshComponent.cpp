#include "MeshComponent.h"
#include "graphics/Mesh.h"
#include <json/json.h>

using namespace graphics;
using namespace serialisation;

namespace components
{
	MeshComponent::MeshComponent()
	{
	}
	
	MeshComponent::MeshComponent(const MeshComponent& other) :
		mesh(other.mesh)
	{

	}

	MeshComponent::~MeshComponent()
	{
	}

	MeshComponent& MeshComponent::operator= (const MeshComponent& other)
	{
		mesh = other.mesh;
		return *this;
	}

	std::string MeshComponent::TypeName()
	{
		return "MeshComponent";
	}

	std::string MeshComponent::typeName() const
	{
		return MeshComponent::TypeName();
	}

	Serialisable* MeshComponent::clone() const
	{
		return new MeshComponent(*this);
	}

	Json::Value MeshComponent::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		data["mesh"] = mesh->serialise();
		return data;
	}

	void MeshComponent::deserialise(const Json::Value& data)
	{
		mesh.reset(Serialiser::Deserialise<Mesh>(data["mesh"]));
	}
}
