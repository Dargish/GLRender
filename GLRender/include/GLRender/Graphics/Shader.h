#pragma once

#include <GLRender/DataTypes.h>

#include <map>

namespace glr
{
	class GLRENDERAPI Shader
	{
	public:
		static void CheckGLError();

		Shader();

		void addSubShader(const string& path);
		void addSubShader(const string& source, uint shaderType);
		void link();

		void enable();
		void disable();

	private:
		typedef std::map<uint, uint> SubShaderMap;
		void compileSubShader(uint subShader);

		uint m_program;
		SubShaderMap m_subShaders;
	};
}