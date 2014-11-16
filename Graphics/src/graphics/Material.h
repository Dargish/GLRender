#pragma once
#include "fwd.h"
#include <map>
#include <Serialisation/Serialiser.h>

namespace graphics
{
	class Material : public serialisation::FileSerialisable
	{
	public:
		Material();
		Material(const std::string& name);
		Material(const Material& other);
		~Material();
		Material& operator= (const Material& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;

		virtual std::string pathFromName(const std::string& name) const;

		Shader_Ptr shader();
		Shader_Const_Ptr shader() const;
		void setShader(const Shader_Ptr& shader);

		void setValue(const std::string& name, float value);
		void setValue(const std::string& name, const Vector3& value);
		void setTexture(const std::string& name, const std::string& filePath);

		void applyToShader();

	protected:
		virtual void serialiseToData(Json::Value& data) const;
		virtual void deserialiseFromData(const Json::Value& data);

	private:
		void getDefaultValuesFromShader();

		Shader_Ptr m_shader;
		ShaderValueMap m_values;
	};
}
