#pragma once
#include "../fwd.h"
#include "Light.h"

namespace graphics
{
	namespace lights
	{
		class PointLight : public Light
		{
		public:
			PointLight();
			PointLight(const Vector3& position, const Vector3& color, float intensity);
			PointLight(const PointLight& other);
			virtual ~PointLight();
			PointLight& operator=(const PointLight& other);

			virtual void light(const FrameBuffer_Ptr frameBuffer, const Camera_Ptr& camera, float deltaTime);

			static std::string TypeName();
			virtual std::string typeName() const;
			virtual serialisation::Serialisable* clone() const;
			virtual Json::Value serialise() const;
			virtual void deserialise(const Json::Value& data);

		private:
			Shader_Ptr m_pointShader;
			primitives::Sphere_Ptr m_lightSphere;
			Vector3 m_position;
			Vector3 m_color;
			float m_intensity;
		};
	}
}