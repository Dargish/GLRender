#pragma once
#include "fwd.h"
#include <map>

namespace serialisation
{
	class Serialisable
	{
	public:
		Serialisable();
		virtual ~Serialisable();

		virtual std::string typeName() const = 0;
		virtual Serialisable* clone() const = 0;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data) = 0;
	};

	class Serialiser
	{
	public:
		static Serialiser_Ptr Instance();
		~Serialiser();

		template<class T>
		void registerSerialisable();

		template<class T>
		T* deserialise(const Json::Value& data);

		template<class T>
		static void RegisterSerialisable();

		template<class T>
		static T* Deserialise(const Json::Value& data);

	private:
		Serialiser();

		static Serialiser_Ptr s_instance;

		typedef std::map<std::string, Serialisable_Ptr> SerialisableMap;
		SerialisableMap m_serialisables;
	};

	template<class T>
	void Serialiser::registerSerialisable()
	{
		Serialisable_Ptr serialisable(new T);
		m_serialisables[serialisable->typeName()] = serialisable;
	}

	template<class T>
	void Serialiser::RegisterSerialisable()
	{
		Instance()->registerSerialisable<T>();
	}

	template<class T>
	T* Serialiser::deserialise(const Json::Value& data)
	{
		SerialisableMap::const_iterator it = m_serialisables.find(data["typeName"].asString());
		if (it != m_serialisables.end())
		{
			T* s = dynamic_cast<T*>(it->second->clone());
			s->deserialise(data);
			return s;
		}
		return NULL;
	}

	template<class T>
	T* Serialiser::Deserialise(const Json::Value& data)
	{
		return Instance()->deserialise<T>(data);
	}
}