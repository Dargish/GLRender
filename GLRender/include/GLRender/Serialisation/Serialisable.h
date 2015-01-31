#pragma once

#include <GLRender/GLRender.h>
#include <GLRender/DataTypes.h>

#include <typeinfo>

namespace Json
{
	class Value;
}

namespace glrender
{
namespace serialisation
{
	class GLRENDERAPI BaseSerialisable
	{
	public:
		virtual ~BaseSerialisable();

		virtual const string& typeName() const = 0;
		virtual void serialise(Json::Value& data) const;
		virtual void deserialise(const Json::Value& data);
	};

	template<class T>
	class Serialisable
	{
	public:
		static string TypeName();
		virtual ~Serialisable();
		virtual string typeName() const;
		virtual T* clone() const;
	};

	template<class T>
	Serialisable<T>::~Serialisable()
	{

	}

	template<class T>
	string Serialisable<T>::TypeName()
	{
		string name = typeid(T).name();
		size_t i = name.find_first_of(' ') + 1;
		return name.substr(i, name.size() - i);
	}

	template<class T>
	string Serialisable<T>::typeName() const
	{
		return T::TypeName();
	}

	template<class T>	
	T* Serialisable<T>::clone() const
	{
		return new T(*((T*)this));
	}
}
}
