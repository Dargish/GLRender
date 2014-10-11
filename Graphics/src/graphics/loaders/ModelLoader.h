#pragma once
#include "../fwd.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"

namespace graphics
{
	namespace loaders
	{
		class ModelLoader
		{
		public:
			virtual ~ModelLoader();

			virtual void load(const std::string& filePath, VertexBuffer_Ptr& vertexBuffer, IndexBuffer_Ptr& indexBuffer) const = 0;
		};
	}
}
