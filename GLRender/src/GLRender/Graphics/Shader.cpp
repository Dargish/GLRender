#include <GLRender/Graphics/Shader.h>
#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

// Todo: remove this in the future
#include <iostream>
#include <fstream>

namespace glr
{
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
			throw std::runtime_error("GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_INVALID_VALUE:
			throw std::runtime_error("GL_INVALID_VALUE: A numeric argument is out of range.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_INVALID_OPERATION:
			throw std::runtime_error("GL_INVALID_OPERATION: The specified operation is not allowed in the current state.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			throw std::runtime_error("GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.The offending command is ignored and has no other side effect than to set the error flag.");
			break;
		case GL_OUT_OF_MEMORY:
			throw std::runtime_error("GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");
			break;
		case GL_STACK_UNDERFLOW:
			throw std::runtime_error("GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.");
			break;
		case GL_STACK_OVERFLOW:
			throw std::runtime_error("GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.");
			break;
		case GL_NO_ERROR:
		default:
			return;
		}
	}

	Shader::Shader()
	{

	}

	void Shader::addSubShader(const string& path)
	{
		// Get the extension of the sub shader to determine the type
		string ext = path.substr(path.find_last_of(".") + 1);
		uint shaderType = 0;
		if (ext == "vert")
		{
			shaderType = GL_VERTEX_SHADER;
		}
		else if (ext == "frag")
		{
			shaderType = GL_FRAGMENT_SHADER;
		}
		else
		{
			throw std::runtime_error("Unrecognised sub shader type " + ext);
		}
		
		// Read the source code from the file
		string source = "";
		std::ifstream myfile(path);
		string line;
		if (myfile.is_open())
		{
			while (std::getline(myfile, line))
			{
				source += line + '\n';
			}
			myfile.close();
		}

		addSubShader(source, shaderType);
	}

	void Shader::addSubShader(const string& source, uint shaderType)
	{
		// Create and compile the sub shader
		const char* vv = source.c_str();
		uint subShader = glCreateShader(shaderType);
		glShaderSource(subShader, 1, &vv, NULL);
		compileSubShader(subShader);

		// Add it to our maps of compiled sub shaders
		m_subShaders[shaderType] = subShader;
	}

	void Shader::link()
	{
		m_program = glCreateProgram();
		for (SubShaderMap::const_iterator it = m_subShaders.begin(); it != m_subShaders.end(); ++it)
		{
			glAttachShader(m_program, it->second);
		}
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

	void Shader::setValue(const std::string& name, float value)
	{
		uint loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniform1f(loc, value);
		}
	}

	void Shader::setValue(const std::string& name, const Vector2& value)
	{
		uint loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniform2fv(loc, 1, glm::value_ptr(value));
		}
	}

	void Shader::setValue(const std::string& name, const Vector3& value)
	{
		uint loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniform3fv(loc, 1, glm::value_ptr(value));
		}
	}

	void Shader::setValue(const std::string& name, const Matrix4& value)
	{
		uint loc = glGetUniformLocation(m_program, name.c_str());
		if (loc > -1)
		{
			glUniformMatrix4fv(loc, 1, false, glm::value_ptr(value));
		}
	}

	//void Shader::setValue(const std::string& name, const GLBuffer_Ptr& value, int textureUnit /*= -1*/)
	//{
	//	uint loc = glGetUniformLocation(m_program, name.c_str());
	//	if (loc > -1)
	//	{
	//		if (textureUnit < 0)
	//		{
	//			textureUnit = nextTextureUnit();
	//		}
	//		ActivateTexture activateTexture(textureUnit);
	//		value->bind();
	//		glUniform1i(loc, textureUnit);
	//	}
	//}

	void Shader::compileSubShader(uint subShader)
	{
		glCompileShader(subShader);
		GLint result = GL_FALSE;
		glGetShaderiv(subShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint logLength = 0;
			glGetShaderiv(subShader, GL_INFO_LOG_LENGTH, &logLength);
			string log;
			log.resize(logLength);
			glGetShaderInfoLog(subShader, logLength, &logLength, (GLchar*)log.c_str());

			GLint srcLength = 0;
			glGetShaderiv(subShader, GL_SHADER_SOURCE_LENGTH, &srcLength);
			string src;
			src.resize(srcLength);
			glGetShaderSource(subShader, srcLength, &srcLength, (GLchar*)src.c_str());
			std::cerr << src << std::endl << log << std::endl;
			throw std::runtime_error("Error compiling subshader");
		}
	}
}