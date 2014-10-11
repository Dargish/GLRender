#pragma once
#include "../fwd.h"
#include "serialisation/Serialiser.h"

namespace graphics
{
	namespace lights
	{
		class Light : public serialisation::Serialisable
		{
		public:
			virtual ~Light();

			virtual void light(const FrameBuffer_Ptr frameBuffer, const Camera_Ptr& camera, float deltaTime) = 0;
		};
	}
}