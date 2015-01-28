#pragma once

#include <GLRender/GLRender.h>
#include <GLRender/DataTypes.h>
#include <GLRender/TypeName.h>

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

		virtual const string& typeName() const = 0;
		virtual void serialise(Json::Value& data) const;
		virtual void deserialise(const Json::Value& data);
	};

	template<class T>
	class Serialisable
	{
	public:
		virtual ~Serialisable();
		virtual const string& typeName() const;
		virtual T* clone() const;
	};

	template<class T>
	Serialisable<T>::~Serialisable()
	{

	}

	template<class T>
	const string& Serialisable<T>::typeName() const
	{
		return TypeNameTraits<T>::Name;
	}

	template<class T>	
	T* Serialisable<T>::clone() const
	{
		return new T(*((T*)this));
	}
}
}

#define SERIALISABLE_CLASS(CLASS) \
class CLASS; \
REGISTER_TYPENAME(CLASS) \
class CLASS : public glrender::serialisation::Serialisable<CLASS>