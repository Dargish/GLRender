#include "ShaderSource.h"
#include "ShaderValue.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

using namespace rapidxml;

namespace graphics
{
	std::string ShaderSource::ShaderPath(const std::string& shaderName)
	{
		return "Content/Shaders/" + shaderName + ".xml";
	}

	ShaderSource::ShaderSource(const std::string& shaderName, bool isInclude /*= false*/)
	{
		load(ShaderPath(shaderName), isInclude);
	}

	const std::string& ShaderSource::version() const
	{
		return m_version;
	}

	const std::string& ShaderSource::defines() const
	{
		return m_defines;
	}

	const std::string& ShaderSource::structs() const
	{
		return m_structs;
	}

	const std::string& ShaderSource::functions() const
	{
		return m_functions;
	}

	const std::string& ShaderSource::vertexFunction() const
	{
		return m_vertexFunction;
	}

	const std::string& ShaderSource::fragmentFunction() const
	{
		return m_fragmentFunction;
	}

	std::string ShaderSource::vertexSource() const
	{
		std::string vertexSource =
			m_version + "\n" +
			m_defines + "\n" +
			m_structs + "\n" +
			m_functions + "\n" +
			m_vertexFunction;
		return vertexSource;
	}

	std::string ShaderSource::fragmentSource() const
	{
		std::string fragmentSource =
			m_version + "\n" +
			m_defines + "\n" +
			m_structs + "\n" +
			m_functions + "\n" +
			m_fragmentFunction;
		return fragmentSource;
	}
	
	const ShaderValueMap& ShaderSource::defaultValues() const
	{
		return m_defaultValues;
	}

	void ShaderSource::load(const std::string& filePath, bool isInclude)
	{
		try
		{
			rapidxml::file<> xmlFile(filePath.c_str());
			xml_document<> doc;
			doc.parse<0>(xmlFile.data());
			xml_node<>* shader = doc.first_node("shader");

			m_version = "#version ";
			m_version += shader->first_attribute("version")->value();

			loadIncludes(shader);
			loadDefines(shader);
			loadStructs(shader);
			loadFunctions(shader);

			if (!isInclude)
			{
				xml_node<>* vertexShader = shader->first_node("vertexshader");
				m_vertexFunction = parseShaderXml(vertexShader);
				xml_node<>* fragmentShader = shader->first_node("fragmentshader");
				m_fragmentFunction = parseShaderXml(fragmentShader);
			}
		}
		catch (std::runtime_error& err)
		{
			throw std::runtime_error((boost::format("Error loading xml shader: %s") % err.what()).str());
		}
	}

	void ShaderSource::loadDefines(xml_node<>* shader)
	{
		for (xml_node<>* define = shader->first_node("define"); define; define = define->next_sibling("define"))
		{
			m_defines += parseDefineXml(define);
		}
	}

	void ShaderSource::loadStructs(xml_node<>* shader)
	{
		for (xml_node<>* structNode = shader->first_node("struct"); structNode; structNode = structNode->next_sibling("struct"))
		{
			m_structs += parseStructXml(structNode) + "\n";
		}
	}
	
	void ShaderSource::loadFunctions(xml_node<>* shader)
	{
		for (xml_node<>* function = shader->first_node("function"); function; function = function->next_sibling("function"))
		{
			m_functions += parseFunctionXml(function) + "\n";
		}
	}

	void ShaderSource::loadIncludes(xml_node<>* shader)
	{
		for (xml_node<>* include = shader->first_node("include"); include; include = include->next_sibling("include"))
		{
			ShaderSource includeSource(include->value(), true);
			m_defines += includeSource.defines();
			m_structs += includeSource.structs();
			m_functions += includeSource.functions();
		}
	}

	std::string ShaderSource::parseDefineXml(xml_node<>* define)
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

	std::string ShaderSource::parseStructXml(xml_node<>* structNode)
	{
		std::string structName(structNode->first_attribute("name")->value());
		std::string strct = "struct ";
		strct += structName;
		strct += "\n{";
		for (xml_node<>* input = structNode->first_node("value"); input; input = input->next_sibling("value"))
		{
			std::string valueName(input->first_attribute("name")->value());
			std::string valueType(input->first_attribute("type")->value());
			strct += "\n\t" + valueType + " " + valueName + ";";
		}
		strct += "\n};\n";
		return strct;
	}

	std::string ShaderSource::parseFunctionXml(xml_node<>* function)
	{
		std::string func;
		for (xml_node<>* uniform = function->first_node("uniform"); uniform; uniform = uniform->next_sibling("uniform"))
		{
			func += parseUniformXml(uniform);
		}
		std::string retType(function->first_attribute("return")->value());
		std::string funcName(function->first_attribute("name")->value());
		func += retType + " " + funcName + "(";
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
		std::string main(function->first_node("source")->value());
		boost::replace_all(main, "\r\n", "\n");
		boost::replace_all(main, "      ", "\t");
		boost::trim(main);
		func += ")\n{\n\t" + main + "\n}\n";
		return func;
	}

	std::string ShaderSource::parseShaderXml(xml_node<>* shader)
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
			source += parseUniformXml(uniform);
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
		boost::replace_all(main, "\r\n", "\n");
		boost::replace_all(main, "      ", "\t");
		boost::trim(main);
		source += "void main(void)\n{\n\t" + main + "\n}\n";
		return source;
	}

	std::string ShaderSource::parseUniformXml(xml_node<>* uniform)
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
		std::string source;
		source += "uniform " + type + " " + name + defStr + ";\n";
		return source;
	}
}
