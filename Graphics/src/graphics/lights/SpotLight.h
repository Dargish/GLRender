#pragma once
#include "../fwd.h"
#include "Light.h"

namespace graphics
{
	namespace lights
	{
		class SpotLight : public Light
		{
		public:
			SpotLight();
			SpotLight(const Vector3& color, float intensity, float angle);
			SpotLight(const SpotLight& other);
			virtual ~SpotLight();
			SpotLight& operator=(const SpotLight& other);

			virtual void light(
				const FrameBuffer_Ptr frameBuffer, 
				const Transform_Ptr& transform, 
				const Camera_Ptr& camera, 
				float deltaTime);

			static std::string TypeName();
			virtual std::string typeName() const;
			virtual serialisation::Serialisable* clone() const;
			virtual Json::Value serialise() const;
			virtual void deserialise(const Json::Value& data);

			float angle() const;
			void setAngle(float angle);

		private:
			Shader_Ptr m_spotShader;
			primitives::Cone_Ptr m_lightCone;
			Vector3 m_color;
			float m_intensity;
		};
	}
}