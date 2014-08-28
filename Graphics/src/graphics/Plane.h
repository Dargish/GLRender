#pragma once
#include "Primitive.h"

namespace graphics
{
	class Plane : public Primitive
	{
	public:
		Plane(float size = 1.0f);
		Plane(const Plane& other);
		virtual ~Plane();
		Plane& operator=(const Plane& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		void resize(float size);

	private:
		void createMesh();

		float m_size;
	};
}
