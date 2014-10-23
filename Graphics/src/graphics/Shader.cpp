#include "Shader.h"
#include "Texture.h"
#include "TextureFile.h"
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


	/*
	*	Shader
	*/
	void Shader::CheckGLError()
	{
		GLenum err = glGetError();
		switch (err)
		{
		case GL_INVALID_ENUM:
			std::cerr << "GL_INVALID_ENUM" << std::endl;
			throw std::runtime_error("An unacceptable value is specified for an enumerated argument.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_INVALID_VALUE:
			std::cerr << "GL_INVALID_VALUE" << std::endl;
			throw std::runtime_error("A numeric argument is out of range.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_INVALID_OPERATION:
			std::cerr << "GL_INVALID_OPERATION" << std::endl;
			throw std::runtime_error("The specified operation is not allowed in the current state.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
			throw std::runtime_error("The framebuffer object is not complete.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_OUT_OF_MEMORY:
			std::cerr << "GL_OUT_OF_MEMORY" << std::endl;
			throw std::runtime_error("There is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");
			break;
		case GL_STACK_UNDERFLOW:
			std::cerr << "GL_STACK_UNDERFLOW" << std::endl;
			throw std::runtime_error("An attempt has been made to perform an operation that would cause an internal stack to underflow.");
			break;
		case GL_STACK_OVERFLOW:
			std::cerr << "GL_STACK_OVERFLOW" << std::endl;
			throw std::runtime_error("An attempt has been made to perform an operation that would cause an internal stack to overflow.");
			break;
		case GL_NO_ERROR:
		default:
			return;
		}
	}

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

	std::string Shader::parseDefineXml(xml_node<>* define)
	{
		std::string def = "uniform ";
		def += define->first_attribute("type")->value();
		def += " ";
		def += define->first_attribute("name")->value();
		def += " = ";
		def += define->value();
		def += ";\n";
		return def;
	}

	std::string Shader::parseFunctionXml(xml_node<>* function)
	{
		xml_node<>* source = function->first_node("source");
		if (!source)
		{
			return "";
		}
		std::string retType(function->first_attribute("return")->value());
		std::string funcName(function->first_attribute("name")->value());
		std::string func(retType + " " + funcName + "(");
		bool isFirst = true;
		for (xml_node<>* input = function->first_node("input"); input; input = input->next_sibling("input"))
		{
			std::string line = isFirst ? "\n\t" : ",\n\t";
			std::string name(input->value());
			std::string type(input->first_attribute("type")->value());
			line += type + " " + name;
			func += line;
			isFirst = false;
		}
		func += ")\n{\n";
		func += source->value();
		func += "\n}\n";
		return func;
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
					defStr = " = " + type + "(" + defStr + ")";
				}
				else if (type == "vec3")
				{
					ShaderValue_Ptr defaultValue(new Vector3Value);
					defaultValue->setName(name);
					defaultValue->fromString(defStr);
					m_defaultValues[name] = defaultValue;
					defStr = " = " + type + "(" + defStr + ")";
				}
				else if (type == "sampler2D")
				{
					ShaderValue_Ptr defaultValue(new TextureValue);
					defaultValue->setName(name);
					defaultValue->fromString(defStr);
					m_defaultValues[name] = defaultValue;
					defStr = "";
				}
			}
			source += "uniform " + type + " " + name + defStr + ";\n";
		}
		for (xml_node<>* output = shader->first_node("output"); output; output = output->next_sibling("output"))
		{
			std::string line = "out";
			std::string name(output->value());
			std::string type(output->first_attribute("type")->value());
			line = line + " " + type + " " + name + ";\n";
			xml_attribute<>* location = output->first_attribute("location");
			if (location)
			{
				std::string locValue(location->value());
				line = "layout (location = " + locValue + ") " + line;
			}
			source += line;
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

	void Shader::setValue(const std::string& name, const TextureBuffer_Ptr& value, int textureUnit /*= -1*/ )
	{
		sf::Int32 loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			if (textureUnit < 0)
			{
				textureUnit = nextTextureUnit();
			}
			ActivateTexture activateTexture(textureUnit);
			value->bind();
			glUniform1i(loc, textureUnit);
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

			loadIncludes(shader);
			loadDefines(shader);
			loadFunctions(shader);

			// Parse shaders
			std::string version(shader->first_attribute("version")->value());
			xml_node<>* vertexShader = shader->first_node("vertexshader");
			m_vertexSource = "#version " + version + "\n";
			m_vertexSource += m_defines;
			m_vertexSource += m_functions;
			m_vertexSource += parseShaderXml(vertexShader);
			xml_node<>* fragmentShader = shader->first_node("fragmentshader");
			m_fragmentSource = "#version " + version + "\n";
			m_fragmentSource += m_defines;
			m_fragmentSource += m_functions;
			m_fragmentSource += parseShaderXml(fragmentShader);
		}
		catch (std::runtime_error& err)
		{
			throw std::runtime_error((boost::format("Error loading xml shader: %s") % err.what()).str());
		}
		compile();
	}

	void Shader::loadDefines(xml_node<>* shader)
	{
		for (xml_node<>* define = shader->first_node("define"); define; define = define->next_sibling("define"))
		{
			m_defines += parseDefineXml(define);
		}
	}

	void Shader::loadFunctions(const std::string& filePath)
	{
		rapidxml::file<> xmlFile(ShaderPath(filePath).c_str());
		xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		xml_node<>* shader = doc.first_node("shader");
		loadIncludes(shader);
		loadDefines(shader);
		loadFunctions(shader);
	}

	void Shader::loadFunctions(xml_node<>* shader)
	{
		for (xml_node<>* function = shader->first_node("function"); function; function = function->next_sibling("function"))
		{
			m_functions += parseFunctionXml(function);
		}
	}

	void Shader::loadIncludes(xml_node<>* shader)
	{
		for (xml_node<>* include = shader->first_node("include"); include; include = include->next_sibling("include"))
		{
			loadFunctions(include->value());
		}
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

	int Shader::nextTextureUnit()
	{
		if (m_textureUnits.empty())
		{
			fillTextureUnits();
		}
		int next = m_textureUnits.front();
		m_textureUnits.pop_front();
		m_textureUnits.push_back(next);
		return next;
	}

	void Shader::fillTextureUnits()
	{
		int maxTextureUnits;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
		for (int unit = 0; unit < maxTextureUnits; ++unit)
		{
			m_textureUnits.push_back(unit);
		}
	}
}
