#pragma once

#include <GLRender\Serialisation\Serialisable.h>

SERIALISABLE_CLASS(MySerialisable)
{
	virtual void serialise(Json::Value& data) const;
	virtual void deserialise(const Json::Value& data);
};