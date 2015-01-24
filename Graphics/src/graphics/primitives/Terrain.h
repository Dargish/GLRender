#pragma once
#include "../fwd.h"
#include "../Mesh.h"

namespace graphics
{
	namespace primitives
	{
		class Terrain : public Mesh
		{
		public:
			Terrain(int subdivision = 4);
			Terrain(const Terrain& other);
			virtual ~Terrain();
			Terrain& operator=(const Terrain& other);

			static std::string TypeName();
			virtual std::string typeName() const;
			virtual serialisation::Serialisable* clone() const;
			virtual Json::Value serialise() const;
			virtual void deserialise(const Json::Value& data);

			virtual void createMesh();

			int subdivision() const;
			void setSubdivision(int subdivision);

		protected:
			virtual uint geometryType();

		private:
			float heightAt(float x, float y) const;

			int m_subdivision;
		};
	}
}
