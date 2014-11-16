#include "Material.h"
#include "Shader.h"
#include "ShaderValue.h"
#include "TextureFile.h"
#include <json/json.h>

using namespace serialisation;

namespace graphics
{
	Material::Material()
	{
	}

	Material::Material(const std::string& name)
	{
		load(name);
	}

	Material::Material(const Material& other) :
		m_shader(other.m_shader)
	{
		m_name = other.m_name;
		m_fromFile = other.m_fromFile;
		getDefaultValuesFromShader();
	}

	Material::~Material()
	{
	}

	Material& Material::operator= (const Material& other)
	{
		setShader(other.m_shader);
		m_name = other.m_name;
		m_fromFile = other.m_fromFile;
		return *this;
	}

	std::string Material::TypeName()
	{
		return "Material";
	}

	std::string Material::typeName() const
	{
		return Material::TypeName();
	}

	Serialisable* Material::clone() const
	{
		return new Material(*this);
	}

	std::string Material::pathFromName(const std::string& name) const
	{
		return "Content/Materials/" + name + ".mat";
	}
	
	Shader_Ptr Material::shader()
	{
		return m_shader;
	}

	Shader_Const_Ptr Material::shader() const
	{
		return m_shader;
	}

	void Material::setShader(const Shader_Ptr& shader)
	{
		m_shader = shader;
		m_fromFile = false;
		getDefaultValuesFromShader();
	}

	void Material::setValue(const std::string& name, float value)
	{
		m_fromFile = false;
		m_values[name] = ShaderValue_Ptr(new FloatValue(name, value));
	}

	void Material::setValue(const std::string& name, const Vector3& value)
	{
		m_fromFile = false;
		m_values[name] = ShaderValue_Ptr(new Vector3Value(name, value));
	}

	void Material::setTexture(const std::string& name, const std::string& filePath)
	{
		m_fromFile = false;
		m_values[name] = ShaderValue_Ptr(new TextureValue(name, TextureFile::Load(filePath)));
	}

	void Material::applyToShader()
	{
		ShaderValueMap::const_iterator it = m_values.begin();
		for (; it != m_values.end(); ++it)
		{
			it->second->applyToShader(m_shader);
		}
	}

	void Material::serialiseToData(Json::Value& data) const
	{
		data["shader"] = m_shader->name();
		Json::Value valueArray = Json::Value(Json::arrayValue);
		ShaderValueMap::const_iterator it = m_values.begin();
		for (; it != m_values.end(); ++it)
		{
			valueArray.append(it->second->serialise());
		}
		data["values"] = valueArray;
	}

	void Material::deserialiseFromData(const Json::Value& data)
	{
		m_values.clear();
		m_shader = Shader::Load(data["shader"].asString());
		getDefaultValuesFromShader();
		Json::Value valueArray = data["values"];
		Json::Value::iterator it = valueArray.begin();
		for (; it != valueArray.end(); ++it)
		{
			ShaderValue_Ptr shaderValue(Serialiser::Deserialise<ShaderValue>(*it));
			m_values[shaderValue->name()] = shaderValue;
		}
	}

	void Material::getDefaultValuesFromShader()
	{
		if (m_shader)
		{
			ShaderValueMap::const_iterator it = m_shader->defaultValues().begin();
			for (; it != m_shader->defaultValues().end(); ++it)
			{
				ShaderValueMap::const_iterator fit = m_values.find(it->first);
				if (fit == m_values.end())
				{
					ShaderValue_Ptr defaultValue(dynamic_cast<ShaderValue*>(it->second->clone()));
					m_values[it->first] = defaultValue;
				}
			}
		}
	}
}