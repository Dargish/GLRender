#pragma once
#include "Primitive.h"

namespace graphics
{
	class Cube : public Primitive
	{
	public:
		static Cube_Ptr Create(float size = 1.0f);

		Cube();
		virtual ~Cube();

		void resize(float size);

		virtual void serialise(Json::Value& jsonArray);
		virtual void deserialise(Json::Value& jsonDict);

	private:
		float m_size;
	};
}
