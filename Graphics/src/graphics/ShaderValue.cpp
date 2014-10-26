#include "ShaderValue.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureFile.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

namespace graphics
{	
	/*
	*	ShaderValue
	*/
	ShaderValue::ShaderValue()
	{

	}

	ShaderValue::ShaderValue(const std::string& name) :
		m_name(name)
	{

	}

	ShaderValue::~ShaderValue()
	{

	}

	const std::string& ShaderValue::name() const
	{
		return m_name;
	}

	void ShaderValue::setName(const std::string& name)
	{
		m_name = name;
	}

	Json::Value ShaderValue::serialise() const
	{
		Json::Value data = Serialisable::serialise();
		data["name"] = m_name;
		return data;
	}

	void ShaderValue::deserialise(const Json::Value& data)
	{
		m_name = data["name"].asString();
	}


	/*
	*	FloatValue
	*/
	FloatValue::FloatValue()
	{

	}
	FloatValue::FloatValue(const std::string& name, float value) :
		ShaderValue(name),
		m_value(value)
	{

	}

	FloatValue::FloatValue(const FloatValue& other) :
		ShaderValue(other.m_name),
		m_value(other.m_value)
	{

	}

	FloatValue::~FloatValue()
	{

	}

	FloatValue& FloatValue::operator=(const FloatValue& other)
	{
		m_name = other.m_name;
		m_value = other.m_value;
		return *this;
	}

	std::string FloatValue::TypeName()
	{
		return "FloatValue";
	}

	std::string FloatValue::typeName() const
	{
		return FloatValue::TypeName();
	}

	serialisation::Serialisable* FloatValue::clone() const
	{
		return new FloatValue(*this);
	}

	Json::Value FloatValue::serialise() const
	{
		Json::Value data = ShaderValue::serialise();
		data["value"] = m_value;
		return data;
	}

	void FloatValue::deserialise(const Json::Value& data)
	{
		ShaderValue::deserialise(data);
		m_value = float(data["value"].asDouble());
	}

	void FloatValue::applyToShader(const Shader_Ptr& shader) const
	{
		shader->setValue(m_name, m_value);
	}

	void FloatValue::fromString(const std::string& str)
	{
		m_value = boost::lexical_cast<float>(str);
	}


	/*
	*	Vector3Value
	*/
	Vector3Value::Vector3Value()
	{

	}

	Vector3Value::Vector3Value(const std::string& name, const Vector3& value) :
		ShaderValue(name),
		m_value(value)
	{

	}

	Vector3Value::Vector3Value(const Vector3Value& other) :
		ShaderValue(other.m_name),
		m_value(other.m_value)
	{

	}

	Vector3Value::~Vector3Value()
	{

	}

	Vector3Value& Vector3Value::operator=(const Vector3Value& other)
	{
		m_name = other.m_name;
		m_value = other.m_value;
		return *this;
	}

	std::string Vector3Value::TypeName()
	{
		return "Vector3Value";
	}

	std::string Vector3Value::typeName() const
	{
		return Vector3Value::TypeName();
	}

	serialisation::Serialisable* Vector3Value::clone() const
	{
		return new Vector3Value(*this);
	}

	Json::Value Vector3Value::serialise() const
	{
		Json::Value data = ShaderValue::serialise();
		std::string valueString = "";
		for (int i = 0; i < 3; ++i)
		{
			if (i > 0)
			{
				valueString += ",";
			}
			valueString += boost::lexical_cast<std::string>(m_value[i]);
		}
		data["value"] = valueString;
		return data;
	}

	void Vector3Value::deserialise(const Json::Value& data)
	{
		ShaderValue::deserialise(data);
		fromString(data["value"].asString());
	}

	void Vector3Value::applyToShader(const Shader_Ptr& shader) const
	{
		shader->setValue(m_name, m_value);
	}

	void Vector3Value::fromString(const std::string& str)
	{
		std::vector<std::string> strs;
		boost::split(strs, str, boost::is_any_of(","));
		if (strs.size() != 3)
		{
			throw std::runtime_error("Incorrect number of tokens for Vector3Value. Is " + boost::lexical_cast<std::string>(strs.size()) + " expected 3");
		}
		for (int i = 0; i < 3; ++i)
		{
			m_value[i] = boost::lexical_cast<float>(strs[i]);
		}
	}


	/*
	* TextureValue
	*/

	TextureValue::TextureValue()
	{

	}

	TextureValue::TextureValue(const std::string& name, const TextureFile_Ptr& value) :
		ShaderValue(name),
		m_value(value)
	{

	}

	TextureValue::TextureValue(const TextureValue& other) :
		ShaderValue(other.m_name),
		m_value(other.m_value)
	{

	}

	TextureValue::~TextureValue()
	{

	}

	TextureValue& TextureValue::operator=(const TextureValue& other)
	{
		m_name = other.m_name;
		m_value = other.m_value;
		return *this;
	}

	std::string TextureValue::TypeName()
	{
		return "TextureValue";
	}

	std::string TextureValue::typeName() const
	{
		return TextureValue::TypeName();
	}

	serialisation::Serialisable* TextureValue::clone() const
	{
		return new TextureValue(*this);
	}

	Json::Value TextureValue::serialise() const
	{
		Json::Value data = ShaderValue::serialise();
		data["value"] = m_value->filePath();
		return data;
	}

	void TextureValue::deserialise(const Json::Value& data)
	{
		ShaderValue::deserialise(data);
		fromString(data["value"].asString());
	}

	void TextureValue::applyToShader(const Shader_Ptr& shader) const
	{
		shader->setValue(m_name, m_value);
	}

	void TextureValue::fromString(const std::string& str)
	{
		m_value = TextureFile::Load(str);
	}
}
