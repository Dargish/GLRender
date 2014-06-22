#include "MeshComponent.h"
#include "graphics/Mesh.h"

namespace ecs
{
	MeshComponent::MeshComponent()
	{
	}
	
	MeshComponent::MeshComponent(const graphics::Mesh_Ptr& m) :
		mesh(m)
	{

	}

	MeshComponent::~MeshComponent()
	{
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
