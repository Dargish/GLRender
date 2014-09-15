#pragma once
#include "fwd.h"
#include "Mesh.h"

namespace graphics
{
	class Torus : public Mesh
	{
	public:
		Torus(float size = 1.0f, float radius = 0.25f, uint rings = 16, uint segments = 32 );
		Torus(const Torus& other);
		virtual ~Torus();
		Torus& operator=(const Torus& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		virtual void createMesh();

		float size() const;
		float radius() const;
		uint rings() const;
		uint segments() const;

		void setSize(float size);
		void setRadius(float radius);
		void setRings(uint rings);
		void setSegments(uint segments);

	private:
		uint indexOf(uint ring, uint segment) const;

		float m_size;
		float m_radius;
		uint m_rings;
		uint m_segments;
	};
}
