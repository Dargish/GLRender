#include "PointLight.h"
#include "../Shader.h"
#include "../FrameBuffer.h"
#include "../Camera.h"
#include "../primitives/Sphere.h"
#include "../VertexBuffer.h"
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

using namespace graphics::primitives;

namespace graphics
{
	namespace lights
	{
		PointLight::PointLight() :
			m_lightSphere(new Sphere), m_position(Vector3(0, -1, 0)), m_color(Vector3(1, 1, 1)), m_intensity(1.0f)
		{

		}

		PointLight::PointLight(const Vector3& position, const Vector3& color, float intensity) :
			m_lightSphere(new Sphere), m_position(position), m_color(color), m_intensity(intensity)
		{

		}

		PointLight::PointLight(const PointLight& other) :
			m_lightSphere(new Sphere), m_position(other.m_position), m_color(other.m_color), m_intensity(other.m_intensity)
		{

		}

		PointLight::~PointLight()
		{

		}

		PointLight& PointLight::operator=(const PointLight& other)
		{
			m_position = other.m_position;
			m_color = other.m_color;
			m_intensity = other.m_intensity;
			return *this;
		}

		void PointLight::light(const FrameBuffer_Ptr frameBuffer, const Camera_Ptr& camera, float deltaTime)
		{
			if (!m_pointShader)
			{
				m_pointShader = Shader::Load("PointLight");
			}
			Matrix4 positionMtx = glm::translate(m_position);

			// attenuatedIntensity = (I+a)/(1+bd^2)+a
			float a = 0.00025f;
			float b = 10.0f;
			float d = std::sqrt(m_intensity/(a*b)) * 1.1f;
			Matrix4 scaleMtx = glm::scale(Vector3(d, d, d));

			Shader::Enable(m_pointShader);
			m_pointShader->setValue("screenSize", camera->viewportSize());
			m_pointShader->setValue("lightPosition", m_position);
			m_pointShader->setValue("color", m_color);
			m_pointShader->setValue("intensity", m_intensity);
			m_pointShader->setValue("world", positionMtx * scaleMtx);
			m_pointShader->setValue("proj", camera->projMatrix());
			m_pointShader->setValue("view", camera->viewMatrix());
			m_pointShader->setValue("eyePos", camera->position());

			frameBuffer->bindTargets(m_pointShader);

			bool flipFaceCull = (glm::distance(camera->position(), m_position) < d);
			if (flipFaceCull)
			{
				glDisable(GL_CULL_FACE);
			}
			m_lightSphere->draw(deltaTime);
			if (flipFaceCull)
			{
				glEnable(GL_CULL_FACE);
			}
			Shader::Disable(m_pointShader);
		}

		std::string PointLight::TypeName()
		{
			return "PointLight";
		}

		std::string PointLight::typeName() const
		{
			return PointLight::TypeName();
		}

		serialisation::Serialisable* PointLight::clone() const
		{
			return new PointLight(*this);
		}

		Json::Value PointLight::serialise() const
		{
			Json::Value data = Serialisable::serialise();
			Json::Value positionArray = Json::Value(Json::arrayValue);
			Json::Value colorArray = Json::Value(Json::arrayValue);
			for (size_t r = 0; r < 3; ++r)
			{
				positionArray.append(m_position[r]);
				colorArray.append(m_color[r]);
			}
			data["position"] = positionArray;
			data["color"] = colorArray;
			data["intensity"] = m_intensity;
			return data;
		}

		void PointLight::deserialise(const Json::Value& data)
		{
			for (size_t r = 0; r < 3; ++r)
			{
				m_position[r] = (float)data["position"][r].asDouble();
				m_color[r] = (float)data["color"][r].asDouble();
			}
			m_intensity = (float)data["intensity"].asDouble();
		}
	}
}