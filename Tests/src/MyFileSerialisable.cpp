#include "MyFileSerialisable.h"

glrender::string MyFileSerialisable::path() const
{
	return "Content/Test/" + m_name + ".test";
}

void MyFileSerialisable::serialiseToData(Json::Value& data) const
{
	
}

void MyFileSerialisable::deserialiseFromData(const Json::Value& data)
{
	
}