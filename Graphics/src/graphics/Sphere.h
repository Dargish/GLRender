#pragma once
#include "fwd.h"
#include "Mesh.h"

namespace graphics
{
	class Sphere : public Mesh
	{
	public:
		Sphere(float size = 1.0f, uint rings = 16, uint segments = 32);
		Sphere(const Sphere& other);
		virtual ~Sphere();
		Sphere& operator=(const Sphere& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		virtual void createMesh();

		float size() const;
		uint segments() const;
		uint rings() const;

		void setSize(float size);
		void setSegments(uint segments);
		void setRings(uint rings);

	private:
		uint indexOf(uint ring, uint segment) const;

		float m_size;
		uint m_rings;
		uint m_segments;
	};
}
