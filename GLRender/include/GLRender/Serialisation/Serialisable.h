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
		virtual ~BaseSerialisable();

		virtual string& typeName() const = 0;
		virtual void serialise(Json::Value& data) const;
		virtual void deserialise(const Json::Value& data);
	};

	template<class T>
	class Serialisable
	{
	public:
		static string TypeName;
		virtual ~Serialisable();
		virtual string& typeName() const;
		virtual T* clone() const;
	};

	template<class T>
	string Serialisable<T>::TypeName = typeid(T).raw_name();

	template<class T>
	Serialisable<T>::~Serialisable()
	{

	}

	template<class T>
	string& Serialisable<T>::typeName() const
	{
		return Serialisable<T>::TypeName;
	}

	template<class T>	
	T* Serialisable<T>::clone() const
	{
		return new T(*((T*)this));
	}
}
}