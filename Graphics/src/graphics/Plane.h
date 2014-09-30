#pragma once
#include "fwd.h"
#include "Mesh.h"

namespace graphics
{
	class Plane : public Mesh
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

		virtual void createMesh();

		float size() const;
		void setSize(float size);

	private:
		float m_size;
	};
}
