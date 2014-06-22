#pragma once

#include "fwd.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector3.hpp>
#include "core/TypeDefs.h"

namespace graphics
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		void load(const std::string& filePath);

		void compile();

		void enable();
		void disable();

		void setValue(const std::string& name, const Matrix4& value);

	private:
		void compileSubShader(sf::Uint32 subShader);

		std::string m_vertexSource;
		std::string m_fragmentSource;
		sf::Uint32 m_program;
	};
}