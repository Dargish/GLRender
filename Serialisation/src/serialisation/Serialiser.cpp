#include "Serialiser.h"
#include <core/JsonFile.h>

using namespace core;

namespace serialisation
{
	/*
	Serialisable
	*/
	Serialisable::Serialisable()
	{
	}

	Serialisable::~Serialisable()
	{
	}

	std::string Serialisable::TypeName()
	{
		return "Serialisable";
	}

	Json::Value Serialisable::serialise() const
	{
		Json::Value data;
		data["typeName"] = typeName();
		return data;
	}


	/*
	FileSerialisable
	*/
	FileSerialisable::FileSerialisable() :
		m_fromFile(false)
	{

	}

	FileSerialisable::~FileSerialisable()
	{

	}

	Json::Value FileSerialisable::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		data["name"] = m_name;
		data["fromFile"] = m_fromFile;
		if (!m_fromFile)
		{
			serialiseToData(data);
		}
		return data;
	}

	void FileSerialisable::deserialise(const Json::Value& data)
	{
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

	void FileSerialisable::load(const std::string& name)
	{
		m_fromFile = true;
		m_name = name;
		deserialiseFromData(JsonFile::Load(pathFromName(m_name)));
	}

	void FileSerialisable::save(const std::string& name)
	{
		m_name = name;
		JsonFile::Save(pathFromName(m_name), serialise());
		m_fromFile = true;
	}

	const std::string& FileSerialisable::name() const
	{
		return m_name;
	}


	/*
	Serialiser_Ptr
	*/
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
