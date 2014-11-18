#include "Shader.h"
#include "ShaderSource.h"
#include "GLBuffer.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

namespace graphics
{
	Shader_Ptr Shader::s_current;
	Shader::ShaderCache Shader::s_shaderCache;

	class ActivateTexture
	{
	public:
		ActivateTexture(int textureUnit)
		{
			glGetIntegerv(GL_ACTIVE_TEXTURE, &m_oldTextureUnit);
			glActiveTexture(GL_TEXTURE0 + textureUnit);
		}

		~ActivateTexture()
		{
			glActiveTexture(m_oldTextureUnit);
		}

	private:
		int m_oldTextureUnit;
	};

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
		m_shaderSource(new ShaderSource(name)),
		m_program(0)
	{
		compile();
	}

	Shader::~Shader()
	{

	}

	const std::string& Shader::name() const
	{
		return m_name;
	}

	void Shader::setValue(const std::string& name, float value)
	{
		sf::Int32 loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniform1f(loc, value);
		}
	}

	void Shader::setValue(const std::string& name, const Vector2& value)
	{
		sf::Int32 loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniform2fv(loc, 1, glm::value_ptr(value));
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

	void Shader::setValue(const std::string& name, const GLBuffer_Ptr& value, int textureUnit /*= -1*/ )
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
		return m_shaderSource->defaultValues();
	}

	uint Shader::program() const
	{
		return m_program;
	}

	void Shader::compile()
	{
		std::string vertexSource = m_shaderSource->vertexSource();
		std::string fragmentSource = m_shaderSource->fragmentSource();

		std::ofstream vertexLogFile;
		vertexLogFile.open("Logs/Shaders/" + m_name + "_vertex.glsl");
		vertexLogFile << vertexSource;
		vertexLogFile.close();
		std::ofstream fragmentLogFile;
		fragmentLogFile.open("Logs/Shaders/" + m_name + "_fragment.glsl");
		fragmentLogFile << fragmentSource;
		fragmentLogFile.close();

		m_program = glCreateProgram();
		uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* vv = vertexSource.c_str();
		const char* ff = fragmentSource.c_str();

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
