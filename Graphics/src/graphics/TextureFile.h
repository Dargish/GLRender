#pragma once
#include "Texture.h"
#include "serialisation/Serialiser.h"

namespace graphics
{
	class TextureFile : public Texture
	{
	public:
		static std::string TexturePath(const std::string& filePath);
		static TextureFile_Ptr& Load(const std::string& filePath);

		virtual ~TextureFile();

		const std::string& filePath();

	private:
		typedef std::map<std::string, TextureFile_Ptr> TextureFileCache;
		static TextureFileCache s_textureCache;

		TextureFile(const std::string& filePath);

		std::string m_filePath;
	};
}
