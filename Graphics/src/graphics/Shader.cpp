#include "Shader.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <json/json.h>

using namespace rapidxml;

namespace graphics
{
	Shader_Ptr Shader::s_current;
	Shader::ShaderCache Shader::s_shaderCache;
	
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
	*	Shader
	*/
	std::string Shader::ShaderPath(const std::string& shaderName)
	{
		return "Content/Shaders/" + shaderName + ".xml";
	}

	Shader_Ptr& Shader::Load(const std::string& name)
	{
		ShaderCache::iterator it = s_shaderCache.find(name);
		if (it != s_shaderCache.end())
		{
			return it->second;
		}
		else
		{
			Shader_Ptr shader(new Shader(name));
			shader->load();
			s_shaderCache[name] = shader;
			return s_shaderCache[name];
		}
	}

	void Shader::Enable(const Shader_Ptr& shader)
	{
		shader->enable();
		s_current = shader;
	}

	void Shader::Disable(const Shader_Ptr& shader)
	{
		shader->disable();
		s_current.reset();
	}

	const Shader_Ptr& Shader::Current()
	{
		return s_current;
	}

	Shader::Shader(const std::string& name) :
		m_name(name),
		m_program(0)
	{
		
	}

	Shader::~Shader()
	{

	}

	const std::string& Shader::name() const
	{
		return m_name;
	}

	std::string Shader::parseShaderXml(xml_node<>* shader)
	{
		std::string source;
		for (xml_node<>* input = shader->first_node("input"); input; input = input->next_sibling("input"))
		{
			std::string line = "in";
			std::string name(input->value());
			std::string type(input->first_attribute("type")->value());
			line = line + " " + type + " " + name + ";\n";
			xml_attribute<>* location = input->first_attribute("location");
			if (location)
			{
				std::string locValue(location->value());
				line = "layout (location = " + locValue + ") " + line;
			}
			source += line;
		}
		for (xml_node<>* uniform = shader->first_node("uniform"); uniform; uniform = uniform->next_sibling("uniform"))
		{
			std::string name(uniform->value());
			std::string type(uniform->first_attribute("type")->value());
			xml_attribute<>* defAttr = uniform->first_attribute("default");
			std::string defStr;
			if (defAttr)
			{
				defStr = defAttr->value();
				if (type == "float")
				{
					ShaderValue_Ptr defaultValue(new FloatValue);
					defaultValue->fromString(defStr);
					m_defaultValues[name] = defaultValue;
				}
				else if (type == "vec3")
				{
					ShaderValue_Ptr defaultValue(new Vector3Value);
					defaultValue->setName(name);
					defaultValue->fromString(defStr);
					m_defaultValues[name] = defaultValue;
				}
				defStr = " = " + type + "(" + defStr + ")";
			}
			source += "uniform " + type + " " + name + defStr + ";\n";
		}
		for (xml_node<>* output = shader->first_node("output"); output; output = output->next_sibling("output"))
		{
			std::string name(output->value());
			std::string type(output->first_attribute("type")->value());
			source += "out " + type + " " + name + ";\n";
		}
		std::string main(shader->first_node("source")->value());
		source += "void main(void)\n{\n" + main + "\n}\n";
		return source;
	}

	void Shader::setValue(const std::string& name, float value)
	{
		sf::Int32 loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniform1f(loc, value);
		}
	}

	void Shader::setValue(const std::string& name, const Vector3& value)
	{
		sf::Int32 loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniform3fv(loc, 1, glm::value_ptr(value));
		}
	}

	void Shader::setValue(const std::string& name, const Matrix4& value)
	{
		sf::Int32 loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniformMatrix4fv(loc, 1, false, glm::value_ptr(value));
		}
	}
	
	const ShaderValueMap& Shader::defaultValues() const
	{
		return m_defaultValues;
	}

	uint Shader::program() const
	{
		return m_program;
	}

	void Shader::load()
	{
		try
		{
			rapidxml::file<> xmlFile(ShaderPath(m_name).c_str());
			xml_document<> doc;
			doc.parse<0>(xmlFile.data());
			xml_node<>* shader = doc.first_node("shader");
			std::string version(shader->first_attribute("version")->value());
			xml_node<>* vertexShader = shader->first_node("vertexshader");
			m_vertexSource = parseShaderXml(vertexShader);
			m_vertexSource = "#version " + version + "\n" + m_vertexSource;
			xml_node<>* fragmentShader = shader->first_node("fragmentshader");
			m_fragmentSource = parseShaderXml(fragmentShader);
			m_fragmentSource = "#version " + version + "\n" + m_fragmentSource;
		}
		catch (std::runtime_error& err)
		{
			throw std::runtime_error((boost::format("Error loading xml shader: %s") % err.what()).str());
		}
		compile();
	}

	void Shader::compile()
	{
		if (m_vertexSource == "" || m_fragmentSource == "")
		{
			return;
		}
		m_program = glCreateProgram();
		uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* vv = m_vertexSource.c_str();
		const char* ff = m_fragmentSource.c_str();

		glShaderSource(vertexShader, 1, &vv, NULL);
		glShaderSource(fragmentShader, 1, &ff, NULL);

		compileSubShader(vertexShader);
		compileSubShader(fragmentShader);

		glAttachShader(m_program, vertexShader);
		glAttachShader(m_program, fragmentShader);

		glLinkProgram(m_program);
	}

	void Shader::enable()
	{
		glEnable(GL_FRAGMENT_PROGRAM_ARB);
		glUseProgram(m_program);
	}

	void Shader::disable()
	{
		glUseProgram(0);
		glDisable(GL_FRAGMENT_PROGRAM_ARB);
	}

	void Shader::compileSubShader(uint subShader)
	{
		glCompileShader(subShader);
		sf::Int32 result = GL_FALSE;
		glGetShaderiv(subShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint logLength = 0;
			glGetShaderiv(subShader, GL_INFO_LOG_LENGTH, &logLength);
			std::string log;
			log.resize(logLength);
			glGetShaderInfoLog(subShader, logLength, &logLength, (GLchar*)log.c_str());

			GLint srcLength = 0;
			glGetShaderiv(subShader, GL_SHADER_SOURCE_LENGTH, &srcLength);
			std::string src;
			src.resize(srcLength);
			glGetShaderSource(subShader, srcLength, &srcLength, (GLchar*)src.c_str());
			std::cerr << src << std::endl << log << std::endl;
			throw std::runtime_error("Error compiling subshader");
		}
	}
}
