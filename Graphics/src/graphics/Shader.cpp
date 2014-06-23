#include "Shader.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <boost/format.hpp>

using namespace rapidxml;

namespace graphics
{
	Shader_Ptr Shader::s_current;

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

	std::string parseShaderXml(xml_node<>* shader)
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
				defStr = " = " + defStr;
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

	Shader::Shader() :
		m_program(0)
	{
	}

	Shader::~Shader()
	{
	}

	void Shader::load(const std::string& filePath)
	{
		try
		{
			rapidxml::file<> xmlFile(filePath.c_str());
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
		m_program = glCreateProgram();
		sf::Uint32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
		sf::Uint32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		
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

	void Shader::setValue(const std::string& name, const Matrix4& value)
	{
		sf::Int32 loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniformMatrix4fv(loc, 1, false, glm::value_ptr(value));
		}
		else
		{
			throw std::runtime_error((boost::format("Failed to get uniform location of '%s'") % name).str());
		}		
	}

	void Shader::compileSubShader(sf::Uint32 subShader)
	{
		glCompileShader(subShader);
		sf::Int32 result = GL_FALSE;
		glGetShaderiv(subShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			throw std::runtime_error("Error compiling subshader");
		}
	}
}
