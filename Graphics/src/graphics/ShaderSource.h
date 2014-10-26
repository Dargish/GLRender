#pragma once
#include "fwd.h"

namespace graphics
{
	class ShaderSource
	{
	public:
		static std::string ShaderPath(const std::string& shaderName);

		ShaderSource(const std::string& shaderName, bool isInclude = false);

		const std::string& version() const;
		const std::string& defines() const;
		const std::string& structs() const;
		const std::string& functions() const;
		const std::string& vertexFunction() const;
		const std::string& fragmentFunction() const;

		std::string vertexSource() const;
		std::string fragmentSource() const;

		const ShaderValueMap& defaultValues() const;

	private:
		void load(const std::string& filePath, bool isInclude);
		void loadDefines(rapidxml::xml_node<>* shader);
		void loadStructs(rapidxml::xml_node<>* shader);
		void loadFunctions(rapidxml::xml_node<>* shader);
		void loadIncludes(rapidxml::xml_node<>* shader);

		std::string parseDefineXml(rapidxml::xml_node<>* define);
		std::string parseStructXml(rapidxml::xml_node<>* structNode);
		std::string parseFunctionXml(rapidxml::xml_node<>* function);
		std::string parseShaderXml(rapidxml::xml_node<>* shader);
		std::string parseUniformXml(rapidxml::xml_node<>* uniform);

		std::string m_version;
		std::string m_defines;
		std::string m_structs;
		std::string m_functions;
		std::string m_vertexFunction;
		std::string m_fragmentFunction;

		ShaderValueMap m_defaultValues;
	};
}