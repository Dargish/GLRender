#pragma once
#include "../fwd.h"
#include "Light.h"

namespace graphics
{
	namespace lights
	{
		class DirectionalLight : public Light
		{
		public:
			DirectionalLight();
			DirectionalLight(const Vector3& direction, const Vector3& color, float intensity);
			DirectionalLight(const DirectionalLight& other);
			virtual ~DirectionalLight();
			DirectionalLight& operator=(const DirectionalLight& other);

			virtual void light(const FrameBuffer_Ptr frameBuffer, const Camera_Ptr& camera, float deltaTime);

			static std::string TypeName();
			virtual std::string typeName() const;
			virtual serialisation::Serialisable* clone() const;
			virtual Json::Value serialise() const;
			virtual void deserialise(const Json::Value& data);

		private:
			Shader_Ptr m_directionalShader;
			primitives::Plane_Ptr m_screenQuad;
			Vector3 m_direction;
			Vector3 m_color;
			float m_intensity;
		};
	}
}