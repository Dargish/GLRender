#include <GLRender/Serialisation/FileSerialisable.h>

#include <json/json.h>

namespace glrender
{
namespace serialisation
{
	BaseFileSerialisable::BaseFileSerialisable() :
		m_fromFile(false)
	{

	}

	BaseFileSerialisable::~BaseFileSerialisable()
	{

	}

	void BaseFileSerialisable::serialise(Json::Value& data) const
	{
		BaseSerialisable::serialise(data);
		data["name"] = m_name;
		data["fromFile"] = m_fromFile;
		if (!m_fromFile)
		{
			serialiseToData(data);
		}
	}

	void BaseFileSerialisable::deserialise(const Json::Value& data)
	{
		BaseSerialisable::deserialise(data);
		m_name = data["name"].asString();
		m_fromFile = data["fromFile"].asBool();
		if (m_fromFile)
		{
			load(m_name);
		}
		else
		{
			deserialiseFromData(data);
		}
	}

	void BaseFileSerialisable::save(const std::string& name)
	{
		m_name = name;
		Json::Value data;
		serialise(data);
		//JsonFile::Save(path(), data);
		m_fromFile = true;
	}

	void BaseFileSerialisable::load(const std::string& name)
	{
		m_fromFile = true;
		m_name = name;
		//deserialiseFromData(JsonFile::Load(path()));
	}

	const std::string& BaseFileSerialisable::name() const
	{
		return m_name;
	}

	template<class T>
	FileSerialisable<T>::~FileSerialisable()
	{

	}
}
}