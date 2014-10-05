#pragma once
#include "ModelLoader.h"

namespace graphics
{
	class AssimpModelLoader : public ModelLoader
	{
	public:
		virtual ~AssimpModelLoader();

		virtual void load(const std::string& filePath, VertexBuffer_Ptr& vertexBuffer, IndexBuffer_Ptr& indexBuffer) const;
	};
}
