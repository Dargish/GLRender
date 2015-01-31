#pragma once

#include <GLRender/Serialisation/Serialisable.h>

namespace glrender
{
namespace serialisation
{
	class BaseFileSerialisable : public BaseSerialisable
	{
	public:
		BaseFileSerialisable();
		virtual ~BaseFileSerialisable();

		virtual void serialise(Json::Value& data) const;
		virtual void deserialise(const Json::Value& data);

		void save(const std::string& name);
		void load(const std::string& name);

		const std::string& name() const;

		virtual std::string path() const = 0;

	protected:
		virtual void serialiseToData(Json::Value& data) const = 0;
		virtual void deserialiseFromData(const Json::Value& data) = 0;

		std::string m_name;
		bool m_fromFile;
	};

	template<class T>
	class FileSerialisable : public Serialisable<T>, public BaseFileSerialisable
	{
		virtual ~FileSerialisable();
	};
}
}