#include "MeshComponent.h"
#include "graphics/Mesh.h"

namespace ecs
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

	void MeshComponent::serialise(Json::Value& componentArray)
	{
		//mesh->serialise(componentArray);
	}

	void MeshComponent::deserialise(Json::Value& componentDict)
	{
		//mesh->serialise(componentDict);
	}
}
