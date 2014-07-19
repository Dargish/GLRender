#include "Serialiser.h"
#include <json/json.h>

namespace serialisation
{
	Serialisable::Serialisable()
	{
	}

	Serialisable::~Serialisable()
	{
	}

	Json::Value Serialisable::serialise() const
	{
		Json::Value data;
		data["typeName"] = typeName();
		return data;
	}
	
	Serialiser_Ptr Serialiser::s_instance;

	Serialiser_Ptr Serialiser::Instance()
	{
		if (!s_instance.get())
		{
			s_instance.reset(new Serialiser);
		}
		return s_instance;
	}

	Serialiser::Serialiser()
	{
	}

	Serialiser::~Serialiser()
	{
	}
}
