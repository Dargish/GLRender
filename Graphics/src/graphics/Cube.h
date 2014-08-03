#pragma once
#include "fwd.h"
#include "Primitive.h"

namespace graphics
{
	class Cube : public Primitive
	{
	public:
		Cube(float size = 1.0f);
		Cube(const Cube& other);
		virtual ~Cube();
		Cube& operator=(const Cube& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		void resize(float size);

	private:
		void createVertices();
		void createIndices();

		float m_size;
	};
}
