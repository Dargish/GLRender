#include "TransformComponent.h"
#include <json/json.h>
#include "core/TypeDefs.h"

namespace ecs
{
	TransformComponent::TransformComponent()
	{
	}

	TransformComponent::TransformComponent(const Matrix4& t) :
		transform(t)
	{
	}

	TransformComponent::~TransformComponent()
	{
	}

	void TransformComponent::serialise(Json::Value& componentArray)
	{
		Json::Value componentDict;
		componentDict["componentType"] = "Transform";
		Json::Value transformArray = Json::Value(Json::arrayValue);
		for (size_t c = 0; c < 4; ++c)
		{
			Matrix4::col_type col = transform[c];
			for (size_t r = 0; r < 4; ++r)
			{
				transformArray.append(col[r]);
			}
		}
		componentDict["transform"] = transformArray;
		componentArray.append(componentDict);
	}

	void TransformComponent::deserialise(Json::Value& componentDict)
	{
		if (componentDict["componentType"].asString() != "Transform")
		{
			throw std::runtime_error("Invalid component type, expected 'Transform' received '" + componentDict["componentType"].asString() + "'");
		}
		for (size_t c = 0; c < 4; ++c)
		{
			Matrix4::col_type& col = transform[c];
			for (size_t r = 0; r < 4; ++r)
			{
				col[r] = (float)componentDict["transform"][r + c * 4].asDouble();
			}
		}
	}
}