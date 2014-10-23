#include "DirectionalLight.h"
#include "../Shader.h"
#include "../FrameBuffer.h"
#include "../Camera.h"
#include "../primitives/ScreenQuad.h"
#include "../VertexBuffer.h"

using namespace graphics::primitives;

namespace graphics
{
	namespace lights
	{
		DirectionalLight::DirectionalLight() :
			m_screenQuad(new ScreenQuad), m_direction(Vector3(0, -1, 0)), m_color(Vector3(1, 1, 1)), m_intensity(1.0f)
		{

		}

		DirectionalLight::DirectionalLight(const Vector3& direction, const Vector3& color, float intensity) :
			m_screenQuad(new ScreenQuad), m_direction(direction), m_color(color), m_intensity(intensity)
		{

		}

		DirectionalLight::DirectionalLight(const DirectionalLight& other) :
			m_screenQuad(new ScreenQuad), m_direction(other.m_direction), m_color(other.m_color), m_intensity(other.m_intensity)
		{

		}

		DirectionalLight::~DirectionalLight()
		{

		}

		DirectionalLight& DirectionalLight::operator=(const DirectionalLight& other)
		{
			m_direction = other.m_direction;
			m_color = other.m_color;
			m_intensity = other.m_intensity;
			return *this;
		}

		void DirectionalLight::light(const FrameBuffer_Ptr frameBuffer, const Camera_Ptr& camera, float deltaTime)
		{
			if (!m_directionalShader)
			{
				m_directionalShader = Shader::Load("DirectionalLight");
			}
			Shader::Enable(m_directionalShader);
			//m_directionalShader->setValue("eyeVec", camera->direction());
			m_directionalShader->setValue("direction", m_direction);
			m_directionalShader->setValue("color", m_color);
			m_directionalShader->setValue("intensity", m_intensity);
			m_directionalShader->setValue("proj", camera->projMatrix());
			m_directionalShader->setValue("view", camera->viewMatrix());
			m_directionalShader->setValue("eyePos", camera->position());
			frameBuffer->bindTargets(m_directionalShader);
			m_screenQuad->setEyeVec(camera);
			m_screenQuad->draw(deltaTime);
			Shader::Disable(m_directionalShader);
		}

		std::string DirectionalLight::TypeName()
		{
			return "DirectionalLight";
		}

		std::string DirectionalLight::typeName() const
		{
			return DirectionalLight::TypeName();
		}

		serialisation::Serialisable* DirectionalLight::clone() const
		{
			return new DirectionalLight(*this);
		}

		Json::Value DirectionalLight::serialise() const
		{
			Json::Value data = Serialisable::serialise();
			Json::Value directionArray = Json::Value(Json::arrayValue);
			Json::Value colorArray = Json::Value(Json::arrayValue);
			for (size_t r = 0; r < 3; ++r)
			{
				directionArray.append(m_direction[r]);
				colorArray.append(m_color[r]);
			}
			data["direction"] = directionArray;
			data["color"] = colorArray;
			data["intensity"] = m_intensity;
			return data;
		}

		void DirectionalLight::deserialise(const Json::Value& data)
		{
			for (size_t r = 0; r < 3; ++r)
			{
				m_direction[r] = (float)data["direction"][r].asDouble();
				m_color[r] = (float)data["color"][r].asDouble();
			}
			m_intensity = (float)data["intensity"].asDouble();
		}
	}
}