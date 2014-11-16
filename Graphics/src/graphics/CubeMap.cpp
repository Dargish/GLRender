#include "CubeMap.h"
#include "TextureFile.h"
#include <GL/glew.h>
#include "Shader.h"

namespace graphics
{
	CubeMap::CubeMap()
	{

	}

	CubeMap::CubeMap(const std::string& name)
	{
		load(name);
	}

	CubeMap::CubeMap(const CubeMap& other) :
		m_textures(other.m_textures)
	{
		m_fromFile = other.m_fromFile;
	}

	CubeMap::~CubeMap()
	{

	}

	CubeMap& CubeMap::operator= (const CubeMap& other)
	{
		m_textures = other.m_textures;
		m_fromFile = other.m_fromFile;
		return *this;
	}

	std::string CubeMap::TypeName()
	{
		return "CubeMap";
	}

	std::string CubeMap::typeName() const
	{
		return CubeMap::TypeName();
	}

	serialisation::Serialisable* CubeMap::clone() const
	{
		return new CubeMap(*this);
	}
	
	std::string CubeMap::pathFromName(const std::string& name) const
	{
		return "Content/CubeMaps/" + name + ".cmap";
	}
	
	uint CubeMap::generateBuffer()
	{
		uint buf = 0;
		glGenTextures(1, &buf);
		return buf;
	}

	void CubeMap::deleteBuffer()
	{
		uint buf = buffer();
		if (buf != 0)
		{
			glDeleteTextures(1, &buf);
		}
	}

	void CubeMap::bind()
	{
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glBindTexture(GL_TEXTURE_CUBE_MAP, buffer());
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		Shader::CheckGLError();
		if (isDirty())
		{
			for (size_t i = 0; i < 6; ++i)
			{
				m_textures[i] = TextureFile::Load(m_sidePaths[i]);
			}

			GLenum internalFormat = m_textures[0]->internalFormat();
			GLenum format = m_textures[0]->format();
			int width = m_textures[0]->width();
			int height = m_textures[0]->height();
			GLenum type = m_textures[0]->type();

			GLsizei mipCount = GLsizei(std::log2(std::min(width, height))) - 1;

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, mipCount);

			glTexStorage2D(GL_TEXTURE_CUBE_MAP, mipCount, internalFormat, width, height);
			for (size_t i = 0; i < 6; ++i)
			{			
				GLvoid* data = m_textures[i]->data();

				//glTexImage2D(
				//	GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				//	0,
				//	internalFormat,
				//	width,
				//	height,
				//	0,
				//	format,
				//	type,
				//	data
				//	);

				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, 0, width, height, format, type, data);
				Shader::CheckGLError();
			}
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			Shader::CheckGLError();

			clean();
		}
	}

	void CubeMap::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	bool CubeMap::empty() const
	{
		return m_textures[0].get() == NULL;
	}

	void CubeMap::serialiseToData(Json::Value& data) const
	{
		Json::Value sidesArray = Json::Value(Json::arrayValue);
		for (size_t i = 0; i < 6; ++i)
		{
			sidesArray.append(m_sidePaths[i]);
		}
		data["sides"] = sidesArray;
	}

	void CubeMap::deserialiseFromData(const Json::Value& data)
	{
		Json::Value sidesArray = data["sides"];
		for (size_t i = 0; i < 6; ++i)
		{
			m_sidePaths[i] = sidesArray[i].asString();
		}
	}
}
