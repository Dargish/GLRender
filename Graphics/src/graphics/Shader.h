#pragma once
#include "fwd.h"
#include <map>
#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector3.hpp>
#include "serialisation/Serialiser.h"

namespace graphics
{
	class Shader
	{
	public:
		static void CheckGLError();

		static Shader_Ptr& Load(const std::string& name);
		static void Enable(const Shader_Ptr& shader);
		static void Disable(const Shader_Ptr& shader);
		static const Shader_Ptr& Current();

		~Shader();

		const std::string& name() const;

		void setValue(const std::string& name, float value);
		void setValue(const std::string& name, const Vector2& value);
		void setValue(const std::string& name, const Vector3& value);
		void setValue(const std::string& name, const Matrix4& value);
		void setValue(const std::string& name, const GLBuffer_Ptr& value, int textureUnit = -1);

		const ShaderValueMap& defaultValues() const;
		uint program() const;

	private:
		typedef std::map<std::string, Shader_Ptr> ShaderCache;

		Shader(const std::string& name);

		void compile();

		void enable();
		void disable();

		void compileSubShader(uint subShader);

		int nextTextureUnit();
		void fillTextureUnits();

		std::string m_name;
		ShaderSource_Ptr m_shaderSource;
		uint m_program;
		std::deque<int> m_textureUnits;

		static Shader_Ptr s_current;
		static ShaderCache s_shaderCache;
	};
}