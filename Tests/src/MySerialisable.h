#pragma once

#include <GLRender\Serialisation\Serialisable.h>

class MySerialisable : public glrender::serialisation::Serialisable<MySerialisable>
{
public:
	virtual void serialise(Json::Value& data) const;
	virtual void deserialise(const Json::Value& data);
};
