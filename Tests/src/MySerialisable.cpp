#include "MySerialisable.h"

#include <json/json.h>

void MySerialisable::serialise(Json::Value& data) const
{
	data["typeName"] = typeName();
}

void MySerialisable::deserialise(const Json::Value& data)
{
	if (data["typeName"].asString() != typeName())
	{
		throw std::runtime_error("Incompatible serialisable type");
	}
}

DEFINE_TYPENAME(MySerialisable)