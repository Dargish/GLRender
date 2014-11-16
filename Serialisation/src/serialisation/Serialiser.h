#pragma once
#include "fwd.h"
#include <map>
#include <vector>
#include <json/json.h>

namespace serialisation
{
	class Serialisable
	{
	public:
		Serialisable();
		virtual ~Serialisable();

		static std::string TypeName();
		virtual std::string typeName() const = 0;
		virtual Serialisable* clone() const = 0;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data) = 0;
	};

	class FileSerialisable : public Serialisable
	{
	public:
		FileSerialisable();
		virtual ~FileSerialisable();

		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		virtual std::string pathFromName(const std::string& name) const = 0;

		void load(const std::string& name);
		void save(const std::string& name);

		const std::string& name() const;

	protected:
		virtual void serialiseToData(Json::Value& data) const = 0;
		virtual void deserialiseFromData(const Json::Value& data) = 0;

		std::string m_name;
		bool m_fromFile;
	};

	template<class T>
	class SerialisableContainer : public Serialisable
	{
	public:
		typedef T ValueType;
		typedef boost::shared_ptr<T> ValueType_Ptr;
		typedef std::vector<ValueType_Ptr> ArrayType;
		typedef typename ArrayType::iterator iterator;
		typedef typename ArrayType::const_iterator const_iterator;

		SerialisableContainer();

		SerialisableContainer(const SerialisableContainer& other);

		virtual ~SerialisableContainer();

		SerialisableContainer& operator= (const SerialisableContainer& other);

		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		void push_back(const ValueType_Ptr& val);

		void erase(const_iterator it);

		virtual Json::Value serialise() const;

		virtual void deserialise(const Json::Value& data);

	private:
		ArrayType m_array;
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


	/*
	SerialisableContainer
	*/
	template<class T>
	SerialisableContainer<T>::SerialisableContainer()
	{

	}

	template<class T>
	SerialisableContainer<T>::~SerialisableContainer()
	{

	}

	template<class T>
	SerialisableContainer<T>::SerialisableContainer(const SerialisableContainer<T>& other)
	{
		const_iterator it = other.begin();
		for (; it != other.end(); ++it)
		{
			T* ptr = dynamic_cast<T*>((*it)->clone());
			if (ptr == NULL)
			{
				throw std::runtime_error("SerialisableContainer type mismatch in copy constructor");
			}
			push_back(ValueType_Ptr(ptr));
		}
	}

	template<class T>
	SerialisableContainer<T>& SerialisableContainer<T>::operator= (const SerialisableContainer<T>& other)
	{
		const_iterator it = other.begin();
		for (; it != other.end(); ++it)
		{
			T* ptr = dynamic_cast<T*>((*it)->clone());
			if (ptr == NULL)
			{
				throw std::runtime_error("SerialisableContainer type mismatch in assignment operator");
			}
			push_back(ValueType_Ptr(ptr));
		}
	}

	template<class T>
	typename SerialisableContainer<T>::iterator SerialisableContainer<T>::begin()
	{
		return m_array.begin();
	}

	template<class T>
	typename SerialisableContainer<T>::const_iterator SerialisableContainer<T>::begin() const
	{
		return m_array.begin();
	}

	template<class T>
	typename SerialisableContainer<T>::iterator SerialisableContainer<T>::end()
	{
		return m_array.end();
	}

	template<class T>
	typename SerialisableContainer<T>::const_iterator SerialisableContainer<T>::end() const
	{
		return m_array.end();
	}

	template<class T>
	void SerialisableContainer<T>::push_back(const ValueType_Ptr& val)
	{
		m_array.push_back(val);
	}

	template<class T>
	void SerialisableContainer<T>::erase(const_iterator it)
	{
		m_array.erase(it);
	}

	template<class T>
	Json::Value SerialisableContainer<T>::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		Json::Value jsonArray = Json::Value(Json::arrayValue);
		const_iterator it = begin();
		for (; it != end(); ++it)
		{
			jsonArray.append((*it)->serialise());
		}
		data["array"] = jsonArray;
		return data;
	}

	template<class T>
	void SerialisableContainer<T>::deserialise(const Json::Value& data)
	{
		Json::Value jsonArray = data["array"];
		Json::Value::iterator it = jsonArray.begin();
		for (; it != jsonArray.end(); ++it)
		{
			m_array.push_back(ValueType_Ptr(Serialiser::Deserialise<T>(*it)));
		}
	}


	/*
	Serialiser
	*/
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
		std::string serialisedType = data["typeName"].asString();
		SerialisableMap::const_iterator it = m_serialisables.find(serialisedType);
		if (it != m_serialisables.end())
		{
			T* s = dynamic_cast<T*>(it->second->clone());
			if (s == NULL)
			{
				throw std::runtime_error("Failed to convert serialised object of type '" + serialisedType + "' to desired type");
			}
			s->deserialise(data);
			return s;
		}
		throw std::runtime_error("Serialised type '" + serialisedType + "' has not been registered");
	}

	template<class T>
	T* Serialiser::Deserialise(const Json::Value& data)
	{
		return Instance()->deserialise<T>(data);
	}
}