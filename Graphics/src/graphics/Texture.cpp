#include "Texture.h"
#include <SFML\Graphics\Image.hpp>

namespace graphics
{
	std::string Texture::TexturePath(const std::string& textureName)
	{
		return "Content/Textures/" + textureName;
	}

	Texture::Texture() :
		m_width(0), m_height(0), m_nChannels(0), m_textureType(TextureType::kInvalid)
	{
	}

	Texture::Texture(const std::string& filePath) :
		m_width(0), m_height(0), m_nChannels(0), m_textureType(TextureType::kInvalid)
	{
		load(filePath);
	}

	Texture::Texture(int width, int height, int nChannels, const TextureType::Enum& textureType /*= TextureType::kColor*/) :
		m_width(width), m_height(height), m_nChannels(nChannels), m_textureType(textureType)
	{
		resetData();
	}

	Texture::~Texture()
	{
	}

	void Texture::load(const std::string& filePath)
	{
		sf::Image image;
		if (image.loadFromFile(TexturePath(filePath)))
		{
			m_width = image.getSize().x;
			m_height = image.getSize().y;
			m_nChannels = 4;
			m_textureType = TextureType::kColor;
			resetData();
			const uchar* imagePixels = image.getPixelsPtr();
			UCharTextureData::Data& thisPixels = boost::dynamic_pointer_cast<UCharTextureData>(m_data)->data();
			//for (size_t i = 0; i < thisPixels.size(); ++i)
			//{
			//	thisPixels[i] = imagePixels[i];
			//}
			std::copy(imagePixels, imagePixels + m_data->size(), &thisPixels.front());
		}
	}

	const Texture::TextureType::Enum& Texture::textureType() const
	{
		return m_textureType;
	}

	TextureData_Ptr Texture::textureData()
	{
		return m_data;
	}

	TextureData_Const_Ptr Texture::textureData() const
	{
		return m_data;
	}

	int Texture::nChannels() const
	{
		return m_nChannels;
	}

	int Texture::width() const
	{
		return m_width;
	}

	int Texture::height() const
	{
		return m_height;
	}

	GLvoid* Texture::data() const
	{
		return m_data->dataPtr();
	}

	GLenum Texture::type() const
	{
		if (m_textureType == TextureType::kColor)
		{
			return GL_UNSIGNED_BYTE;
		}
		else if (m_textureType == TextureType::kFloat)
		{
			return GL_FLOAT;
		}
		return GL_NONE;
	}

	void Texture::resetData()
	{
		if (m_textureType == TextureType::kColor)
		{
			m_data.reset(new UCharTextureData);
		}
		else if (m_textureType == TextureType::kFloat)
		{
			m_data.reset(new FloatTextureData);
		}
		else
		{
			throw std::runtime_error("Unrecognised texture type");
		}
		m_data->resize(m_width * m_height * m_nChannels);
	}
}