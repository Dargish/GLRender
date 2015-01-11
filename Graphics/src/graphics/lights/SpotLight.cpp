#include "SpotLight.h"
#include "../Shader.h"
#include "../FrameBuffer.h"
#include "../Camera.h"
#include "../Transform.h"
#include "../primitives/Cone.h"
#include "../VertexBuffer.h"
#include <core/MathUtils.h>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

using namespace graphics::primitives;

namespace graphics
{
	namespace lights
	{
		SpotLight::SpotLight() :
			m_lightCone(new Cone), m_color(Vector3(1, 1, 1)), m_intensity(1.0f)
		{

		}

		SpotLight::SpotLight(const Vector3& color, float intensity, float angle) :
			m_lightCone(new Cone), m_color(color), m_intensity(intensity)
		{
			m_lightCone->setAngle(angle);
		}

		SpotLight::SpotLight(const SpotLight& other) :
			m_lightCone(new Cone), m_color(other.m_color), m_intensity(other.m_intensity)
		{
			m_lightCone->setAngle(other.angle());
		}

		SpotLight::~SpotLight()
		{

		}

		SpotLight& SpotLight::operator=(const SpotLight& other)
		{
			m_color = other.m_color;
			m_intensity = other.m_intensity;
			m_lightCone->setAngle(other.angle());
			return *this;
		}

		void SpotLight::light(const FrameBuffer_Ptr frameBuffer, const Transform_Ptr& transform, const Camera_Ptr& camera, float deltaTime)
		{
			if (!m_spotShader)
			{
				m_spotShader = Shader::Load("SpotLight");
			}

			// attenuatedIntensity = (I+a)/(1+bd^2)+a
			float a = 0.00025f;
			float b = 10.0f;
			float d = std::sqrt(m_intensity / (a*b));

			transform->scale.x = d;
			transform->scale.y = d;
			transform->scale.z = d;

			Shader::Enable(m_spotShader);
			m_spotShader->setValue("screenSize", camera->viewportSize());
			m_spotShader->setValue("lightPosition", transform->position);
			m_spotShader->setValue("direction", transform->direction());
			m_spotShader->setValue("color", m_color);
			m_spotShader->setValue("intensity", m_intensity);
			m_spotShader->setValue("spotAngle", cos(degreesToRadians(angle())));
			m_spotShader->setValue("world", transform->world());
			m_spotShader->setValue("proj", camera->projMatrix());
			m_spotShader->setValue("view", camera->viewMatrix());
			m_spotShader->setValue("eyePos", camera->position());

			frameBuffer->bindTargets(m_spotShader);

			bool flipFaceCull = (glm::distance(camera->position(), transform->position) < d);
			if (flipFaceCull)
			{
				glFrontFace(GL_CW);
			}
			m_lightCone->draw(deltaTime);
			if (flipFaceCull)
			{
				glFrontFace(GL_CCW);
			}
			Shader::Disable(m_spotShader);
		}

		std::string SpotLight::TypeName()
		{
			return "SpotLight";
		}

		std::string SpotLight::typeName() const
		{
			return SpotLight::TypeName();
		}

		serialisation::Serialisable* SpotLight::clone() const
		{
			return new SpotLight(*this);
		}

		Json::Value SpotLight::serialise() const
		{
			Json::Value data = Serialisable::serialise();
			Json::Value colorArray = Json::Value(Json::arrayValue);
			for (size_t r = 0; r < 3; ++r)
			{
				colorArray.append(m_color[r]);
			}
			data["color"] = colorArray;
			data["intensity"] = m_intensity;
			data["angle"] = m_lightCone->angle();
			return data;
		}

		void SpotLight::deserialise(const Json::Value& data)
		{
			for (size_t r = 0; r < 3; ++r)
			{
				m_color[r] = (float)data["color"][r].asDouble();
			}
			m_intensity = (float)data["intensity"].asDouble();
			m_lightCone->setAngle((float)data["angle"].asDouble());
		}

		float SpotLight::angle() const
		{
			return m_lightCone->angle();
		}

		void SpotLight::setAngle(float angle)
		{
			m_lightCone->setAngle(angle);
		}
	}
}