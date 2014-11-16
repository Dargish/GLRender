#pragma once
#include "../fwd.h"
#include "Light.h"

namespace graphics
{
	namespace lights
	{
		class EnvironmentLight : public Light
		{
		public:
			EnvironmentLight();
			EnvironmentLight(const CubeMap_Ptr& cubeMap, float intensity);
			EnvironmentLight(const EnvironmentLight& other);
			virtual ~EnvironmentLight();
			EnvironmentLight& operator=(const EnvironmentLight& other);

			virtual void light(const FrameBuffer_Ptr frameBuffer, const Camera_Ptr& camera, float deltaTime);

			static std::string TypeName();
			virtual std::string typeName() const;
			virtual serialisation::Serialisable* clone() const;
			virtual Json::Value serialise() const;
			virtual void deserialise(const Json::Value& data);

		private:
			Shader_Ptr m_environmentShader;
			primitives::ScreenQuad_Ptr m_screenQuad;
			CubeMap_Ptr m_cubeMap;
			float m_intensity;
		};
	}
}