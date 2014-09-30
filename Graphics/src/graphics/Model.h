#pragma once
#include "fwd.h"
#include "Mesh.h"

namespace graphics
{
	class Model : public Mesh
	{
	public:
		static std::string ModelPath(const std::string& modelName);

		Model(const std::string& filePath = "");
		Model(const Model& other);
		virtual ~Model();
		Model& operator=(const Model& other);

		static std::string TypeName();
		virtual std::string typeName() const;
		virtual serialisation::Serialisable* clone() const;
		virtual Json::Value serialise() const;
		virtual void deserialise(const Json::Value& data);

		virtual void createMesh();

		const std::string& filePath() const;

		void setFilePath(const std::string& filePath);

	private:
		std::string m_filePath;
	};
}
