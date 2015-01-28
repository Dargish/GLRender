#include <GLRender\Serialisation\Serialisable.h>

#include <iostream>

#include <json/json.h>

class MySerialisable : public glrender::serialisation::Serialisable<MySerialisable>
{
	virtual void serialise(Json::Value& data) const
	{
		data["typeName"] = typeName();
	}

	virtual void deserialise(const Json::Value& data)
	{
		if (data["typeName"].asString() != typeName())
		{
			throw std::runtime_error("Incompatible serialisable type");
		}
	}
};

int main()
{
	MySerialisable s;
	std::cerr << MySerialisable::TypeName << std::endl;
	std::cerr << s.typeName() << std::endl;
	return 0;
}
