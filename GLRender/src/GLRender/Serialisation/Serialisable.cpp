#include <GLRender/Serialisation/Serialisable.h>

#include <json/json.h>

namespace glrender
{
namespace serialisation
{
	void BaseSerialisable::serialise(Json::Value& data) const
	{
		data["typeName"] = typeName();
	}

	void BaseSerialisable::deserialise(const Json::Value& data)
	{
		if (!data["typeName"].asString() == typeName())
		{
			throw std::runtime_error("Incompatible serialisable type");
		}
	}
}
}