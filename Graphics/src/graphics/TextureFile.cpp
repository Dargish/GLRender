#include "TextureFile.h"
#include <SFML\Graphics\Image.hpp>

namespace graphics
{
	TextureFile::TextureFileCache TextureFile::s_textureCache;

	std::string TextureFile::TexturePath(const std::string& filePath)
	{
		return "Content/Textures/" + filePath;
	}

	TextureFile_Ptr& TextureFile::Load(const std::string& filePath)
	{
		TextureFileCache::iterator it = s_textureCache.find(filePath);
		if (it != s_textureCache.end())
		{
			return it->second;
		}
		else
		{
			TextureFile_Ptr texture(new TextureFile(filePath));
			s_textureCache[filePath] = texture;
			return s_textureCache[filePath];
		}
	}

	TextureFile::TextureFile(const std::string& filePath)
	{
		m_filePath = filePath;
		sf::Image image;
		if (image.loadFromFile(TexturePath(m_filePath)))
		{
			m_width = image.getSize().x;
			m_height = image.getSize().y;
			m_nChannels = 4;
			m_textureType = TextureType::kColor;
			resetData();
			const uchar* imagePixels = image.getPixelsPtr();
			UCharTextureData::Data& thisPixels = boost::dynamic_pointer_cast<UCharTextureData>(m_data)->data();
			std::copy(imagePixels, imagePixels + m_data->size(), &thisPixels.front());
		}
	}

	TextureFile::~TextureFile()
	{
	}

	const std::string& TextureFile::filePath()
	{
		return m_filePath;
	}
}