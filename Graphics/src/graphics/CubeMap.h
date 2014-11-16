#pragma once
#include "fwd.h"
#include "GLBuffer.h"
#include <Serialisation/Serialiser.h>
#include <boost/array.hpp>

namespace graphics
{
	class CubeMap : public GLBuffer, public serialisation::FileSerialisable
	{
	public:
		CubeMap();
		CubeMap(const std::string& name);
		CubeMap(const CubeMap& other);
		~CubeMap();
		CubeMap& operator= (const CubeMap& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;

		virtual std::string pathFromName(const std::string& name) const;

		virtual uint generateBuffer();
		virtual void deleteBuffer();

		virtual void bind();
		virtual void unbind() const;
		virtual bool empty() const;

	protected:
		virtual void serialiseToData(Json::Value& data) const;
		virtual void deserialiseFromData(const Json::Value& data);

	private:
		boost::array<std::string, 6> m_sidePaths;
		boost::array<TextureFile_Ptr, 6> m_textures;
	};
}
