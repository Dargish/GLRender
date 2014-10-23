#pragma once
#include "../fwd.h"
#include "../Mesh.h"

namespace graphics
{
	namespace primitives
	{
		class ScreenQuad : public Mesh
		{
		public:
			ScreenQuad();
			ScreenQuad(const ScreenQuad& other);
			virtual ~ScreenQuad();
			ScreenQuad& operator=(const ScreenQuad& other);

			static std::string TypeName();
			virtual std::string typeName() const;
			virtual serialisation::Serialisable* clone() const;
			virtual Json::Value serialise() const;
			virtual void deserialise(const Json::Value& data);

			virtual void createMesh();

			void setEyeVec(const Camera_Ptr& camera);
		};
	}
}