#pragma once
#include "fwd.h"
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector3.hpp>
#include "serialisation/Serialiser.h"

namespace graphics
{
	class ShaderValue : public serialisation::Serialisable
	{
	public:
		ShaderValue();
		ShaderValue(const std::string& name);
		virtual ~ShaderValue();

		const std::string& name() const;
		void setName(const std::string& name);

		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		virtual void applyToShader(const Shader_Ptr& shader) const = 0;

		virtual void fromString(const std::string& str) = 0;

	protected:
		std::string m_name;
	};

	typedef std::map<std::string, ShaderValue_Ptr> ShaderValueMap;

	class FloatValue : public ShaderValue
	{
	public:
		FloatValue();
		FloatValue(const std::string& name, float value);
		FloatValue(const FloatValue& other);
		virtual ~FloatValue();
		FloatValue& operator=(const FloatValue& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		virtual void applyToShader(const Shader_Ptr& shader) const;

		virtual void fromString(const std::string& str);

	private:
		float m_value;
	};

	class Vector3Value : public ShaderValue
	{
	public:
		Vector3Value();
		Vector3Value(const std::string& name, const Vector3& value);
		Vector3Value(const Vector3Value& other);
		virtual ~Vector3Value();
		Vector3Value& operator=(const Vector3Value& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		virtual void applyToShader(const Shader_Ptr& shader) const;

		virtual void fromString(const std::string& str);

	private:
		Vector3 m_value;
	};

	class Shader
	{
	public:
		static std::string ShaderPath(const std::string& shaderName);

		static Shader_Ptr& Load(const std::string& name);
		static void Enable(const Shader_Ptr& shader);
		static void Disable(const Shader_Ptr& shader);
		static const Shader_Ptr& Current();

		~Shader();

		const std::string& name() const;

		void setValue(const std::string& name, float value);
		void setValue(const std::string& name, const Vector3& value);
		void setValue(const std::string& name, const Matrix4& value);

		const ShaderValueMap& defaultValues() const;
		uint program() const;

	private:
		typedef std::map<std::string, Shader_Ptr> ShaderCache;

		Shader(const std::string& name);

		void load();
		void compile();

		void enable();
		void disable();

		std::string parseShaderXml(rapidxml::xml_node<>* shader);

		void compileSubShader(uint subShader);

		std::string m_name;
		std::string m_vertexSource;
		std::string m_fragmentSource;
		uint m_program;
		ShaderValueMap m_defaultValues;

		static Shader_Ptr s_current;
		static ShaderCache s_shaderCache;
	};
}