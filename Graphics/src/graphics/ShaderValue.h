#pragma once
#include "fwd.h"
//#include <SFML/Graphics.hpp>
//#include <SFML/System/Vector3.hpp>
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

	class TextureValue : public ShaderValue
	{
	public:
		TextureValue();
		TextureValue(const std::string& name, const TextureFile_Ptr& value);
		TextureValue(const TextureValue& other);
		virtual ~TextureValue();
		TextureValue& operator=(const TextureValue& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		virtual void applyToShader(const Shader_Ptr& shader) const;

		virtual void fromString(const std::string& str);

	private:
		TextureFile_Ptr m_value;
	};
}