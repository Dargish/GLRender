#pragma once

#include <GLRender/Serialisation/FileSerialisable.h>

class MyFileSerialisable : public glrender::serialisation::FileSerialisable<MyFileSerialisable>
{
public:
	virtual std::string path() const;

protected:
	virtual void serialiseToData(Json::Value& data) const;
	virtual void deserialiseFromData(const Json::Value& data);
};
