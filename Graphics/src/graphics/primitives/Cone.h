#pragma once
#include "../fwd.h"
#include "../Mesh.h"

namespace graphics
{
	namespace primitives
	{
		class Cone : public Mesh
		{	
		public:
			Cone(float size = 1.0f, float angle = 45.0f, uint segments = 32);
			Cone(const Cone& other);
			virtual ~Cone();
			Cone& operator=(const Cone& other);

			static std::string TypeName();
			virtual std::string typeName() const;
			virtual serialisation::Serialisable* clone() const;
			virtual Json::Value serialise() const;
			virtual void deserialise(const Json::Value& data);

			virtual void createMesh();

			float size() const;
			float angle() const;
			uint segments() const;

			void setSize(float size);
			void setAngle(float angle);
			void setSegments(uint segments);

		private:
			float m_size;
			float m_angle;
			uint m_segments;
		};
	}
}