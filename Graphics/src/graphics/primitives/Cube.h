#pragma once
#include "../fwd.h"
#include "../Mesh.h"

namespace graphics
{
	namespace primitives
	{
		class Cube : public Mesh
		{
		public:
			Cube(float size = 1.0f, bool smooth = false);
			Cube(const Cube& other);
			virtual ~Cube();
			Cube& operator=(const Cube& other);

			static std::string TypeName();
			virtual std::string typeName() const;
			virtual serialisation::Serialisable* clone() const;
			virtual Json::Value serialise() const;
			virtual void deserialise(const Json::Value& data);

			virtual void createMesh();

			float size() const;
			bool smooth() const;

			void setSize(float size);
			void setSmooth(bool smooth);

		private:
			float m_size;
			bool m_smooth;
		};
	}
}