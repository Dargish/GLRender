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

		void setValue(const std::string& name, float value);
		void setValue(const std::string& name, const Vector2& value);
		void setValue(const std::string& name, const Vector3& value);
		void setValue(const std::string& name, const Matrix4& value);
		//void setValue(const std::string& name, const GLBuffer_Ptr& value, int textureUnit = -1);

	private:
		typedef std::map<uint, uint> SubShaderMap;
		void compileSubShader(uint subShader);

		uint m_program;
		SubShaderMap m_subShaders;
	};
}