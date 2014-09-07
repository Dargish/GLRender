#pragma once
#include "fwd.h"
#include "TextureBuffer.h"
#include <map>
#include <vector>

namespace graphics
{
	class TextureData
	{
	public:
		~TextureData() { }

		virtual size_t size() const = 0;
		virtual void resize(size_t size) = 0;
		virtual void* dataPtr() const = 0;
	};


	template<class DATATYPE>
	class TypedTextureData : public TextureData
	{
	public:
		typedef DATATYPE DataType;
		typedef std::vector<DataType> Data;
		~TypedTextureData() { }

		inline DATATYPE get(size_t index)
		{
			return m_data[index];
		}

		inline void set(size_t index, DATATYPE value)
		{
			m_data[index] = value;
		}

		virtual size_t size() const
		{
			return m_data.size();
		}

		virtual void resize(size_t size)
		{
			m_data.resize(size, DATATYPE(0));
		}

		virtual void* dataPtr() const
		{
			return (void*)&m_data.front();
		}

		Data& data()
		{
			return m_data;
		}

		const Data& data() const
		{
			return m_data;
		}

	private:
		Data m_data;
	};

	typedef TypedTextureData<uchar> UCharTextureData;
	typedef boost::shared_ptr<UCharTextureData> UCharTextureData_Ptr;
	typedef boost::shared_ptr<const UCharTextureData> UCharTextureData_Const_Ptr;
	typedef TypedTextureData<float> FloatTextureData;
	typedef boost::shared_ptr<FloatTextureData> FloatTextureData_Ptr;
	typedef boost::shared_ptr<const FloatTextureData> FloatTextureData_Const_Ptr;


	class ActivateTexture
	{
	public:
		ActivateTexture(int textureUnit);
		~ActivateTexture();

	private:
		int m_oldTextureUnit;
	};


	class Texture : public TextureBuffer
	{
	public:
		struct TextureType
		{
			enum Enum
			{
				kInvalid = 0,
				kColor = 1,
				kFloat = 2
			};
		};

		Texture();
		Texture(int width, int height, int nChannels, const TextureType::Enum& textureType = TextureType::kColor);
		virtual ~Texture();

		virtual void* data() const;
		virtual uint type() const;

		const TextureType::Enum& textureType() const;

		TextureData_Ptr textureData();
		TextureData_Const_Ptr textureData() const;

	protected:
		void resetData();
		TextureType::Enum m_textureType;

		TextureData_Ptr m_data;
	};
}
