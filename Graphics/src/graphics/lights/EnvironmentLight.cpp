#include "EnvironmentLight.h"
#include "../Shader.h"
#include "../FrameBuffer.h"
#include "../Camera.h"
#include "../primitives/Plane.h"

using namespace graphics::primitives;

namespace graphics
{
	namespace lights
	{
		EnvironmentLight::EnvironmentLight() :
			m_screenQuad(new Plane), m_color(Vector3(1, 1, 1)), m_intensity(1.0f)
		{

		}

		EnvironmentLight::EnvironmentLight(const Vector3& direction, const Vector3& color, float intensity) :
			m_screenQuad(new Plane), m_color(color), m_intensity(intensity)
		{

		}

		EnvironmentLight::EnvironmentLight(const EnvironmentLight& other) :
			m_screenQuad(new Plane), m_color(other.m_color), m_intensity(other.m_intensity)
		{

		}

		EnvironmentLight::~EnvironmentLight()
		{

		}

		EnvironmentLight& EnvironmentLight::operator=(const EnvironmentLight& other)
		{
			m_color = other.m_color;
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
			m_environmentShader->setValue("eyeVec", camera->direction());
			m_environmentShader->setValue("color", m_color);
			m_environmentShader->setValue("intensity", m_intensity);
			frameBuffer->bindTargets(m_environmentShader);
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
			Json::Value directionArray = Json::Value(Json::arrayValue);
			Json::Value colorArray = Json::Value(Json::arrayValue);
			for (size_t r = 0; r < 3; ++r)
			{
				colorArray.append(m_color[r]);
			}
			data["direction"] = directionArray;
			data["color"] = colorArray;
			data["intensity"] = m_intensity;
			return data;
		}

		void EnvironmentLight::deserialise(const Json::Value& data)
		{
			for (size_t r = 0; r < 3; ++r)
			{
				m_color[r] = (float)data["color"][r].asDouble();
			}
			m_intensity = (float)data["intensity"].asDouble();
		}
	}
}