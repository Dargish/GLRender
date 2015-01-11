#include "PointLight.h"
#include "../Shader.h"
#include "../FrameBuffer.h"
#include "../Camera.h"
#include "../Transform.h"
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
			m_lightSphere(new Sphere), m_color(Vector3(1, 1, 1)), m_intensity(1.0f)
		{

		}

		PointLight::PointLight(const Vector3& color, float intensity) :
			m_lightSphere(new Sphere), m_color(color), m_intensity(intensity)
		{

		}

		PointLight::PointLight(const PointLight& other) :
			m_lightSphere(new Sphere), m_color(other.m_color), m_intensity(other.m_intensity)
		{

		}

		PointLight::~PointLight()
		{

		}

		PointLight& PointLight::operator=(const PointLight& other)
		{
			m_color = other.m_color;
			m_intensity = other.m_intensity;
			return *this;
		}

		void PointLight::light(const FrameBuffer_Ptr frameBuffer, const Transform_Ptr& transform, const Camera_Ptr& camera, float deltaTime)
		{
			if (!m_pointShader)
			{
				m_pointShader = Shader::Load("PointLight");
			}

			// attenuatedIntensity = (I+a)/(1+bd^2)+a
			float a = 0.00025f;
			float b = 10.0f;
			float d = std::sqrt(m_intensity/(a*b));

			transform->scale.x = d;
			transform->scale.y = d;
			transform->scale.z = d;

			Shader::Enable(m_pointShader);
			m_pointShader->setValue("screenSize", camera->viewportSize());
			m_pointShader->setValue("lightPosition", transform->position);
			m_pointShader->setValue("color", m_color);
			m_pointShader->setValue("intensity", m_intensity);
			m_pointShader->setValue("world", transform->world());
			m_pointShader->setValue("proj", camera->projMatrix());
			m_pointShader->setValue("view", camera->viewMatrix());
			m_pointShader->setValue("eyePos", camera->position());

			frameBuffer->bindTargets(m_pointShader);

			bool flipFaceCull = (glm::distance(camera->position(), transform->position) < d);
			if (flipFaceCull)
			{
				glFrontFace(GL_CW);
			}
			m_lightSphere->draw(deltaTime);
			if (flipFaceCull)
			{
				glFrontFace(GL_CCW);
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
			Json::Value colorArray = Json::Value(Json::arrayValue);
			for (size_t r = 0; r < 3; ++r)
			{
				colorArray.append(m_color[r]);
			}
			data["color"] = colorArray;
			data["intensity"] = m_intensity;
			return data;
		}

		void PointLight::deserialise(const Json::Value& data)
		{
			for (size_t r = 0; r < 3; ++r)
			{
				m_color[r] = (float)data["color"][r].asDouble();
			}
			m_intensity = (float)data["intensity"].asDouble();
		}
	}
}