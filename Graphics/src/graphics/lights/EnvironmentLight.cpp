#include "EnvironmentLight.h"
#include "../Shader.h"
#include "../FrameBuffer.h"
#include "../Camera.h"
#include "../CubeMap.h"
#include "../primitives/ScreenQuad.h"

using namespace graphics::primitives;

namespace graphics
{
	namespace lights
	{
		EnvironmentLight::EnvironmentLight() :
			m_screenQuad(new ScreenQuad), m_cubeMap(new CubeMap), m_intensity(1.0f)
		{

		}

		EnvironmentLight::EnvironmentLight(const CubeMap_Ptr& cubeMap, float intensity) :
			m_screenQuad(new ScreenQuad), m_cubeMap(cubeMap), m_intensity(intensity)
		{

		}

		EnvironmentLight::EnvironmentLight(const EnvironmentLight& other) :
			m_screenQuad(new ScreenQuad), m_cubeMap(other.m_cubeMap), m_intensity(other.m_intensity)
		{

		}

		EnvironmentLight::~EnvironmentLight()
		{

		}

		EnvironmentLight& EnvironmentLight::operator=(const EnvironmentLight& other)
		{
			m_cubeMap = other.m_cubeMap;
			m_intensity = other.m_intensity;
			return *this;
		}

		void EnvironmentLight::light(const FrameBuffer_Ptr frameBuffer, const Camera_Ptr& camera, float deltaTime)
		{
			if (!m_environmentShader)
			{
				m_environmentShader = Shader::Load("EnvironmentLight");
			}
			Shader::Enable(m_environmentShader);
			m_environmentShader->setValue("screenSize", camera->viewportSize());
			m_environmentShader->setValue("cubeMap", m_cubeMap);
			m_environmentShader->setValue("intensity", m_intensity);
			m_environmentShader->setValue("proj", camera->projMatrix());
			m_environmentShader->setValue("view", camera->viewMatrix());
			m_environmentShader->setValue("eyePos", camera->position());

			frameBuffer->bindTargets(m_environmentShader);
			m_screenQuad->setEyeVec(camera);
			m_screenQuad->draw(deltaTime);
			Shader::Disable(m_environmentShader);
		}

		std::string EnvironmentLight::TypeName()
		{
			return "EnvironmentLight";
		}

		std::string EnvironmentLight::typeName() const
		{
			return EnvironmentLight::TypeName();
		}

		serialisation::Serialisable* EnvironmentLight::clone() const
		{
			return new EnvironmentLight(*this);
		}

		Json::Value EnvironmentLight::serialise() const
		{
			Json::Value data = Serialisable::serialise();
			data["cubeMap"] = m_cubeMap->name();
			data["intensity"] = m_intensity;
			return data;
		}

		void EnvironmentLight::deserialise(const Json::Value& data)
		{
			m_cubeMap.reset(new CubeMap(data["cubeMap"].asString()));
			m_intensity = (float)data["intensity"].asDouble();
		}
	}
}