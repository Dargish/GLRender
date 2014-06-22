#pragma once

#include "fwd.h"
#include "Mesh.h"
#include "core/TypeDefs.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector3.hpp>
#include <vector>

namespace graphics
{
	class Primitive : public Mesh
	{
	public:
		Primitive();
		virtual ~Primitive();

		std::vector<Vector3>& vertices();
		const std::vector<Vector3>& vertices() const;

		std::vector<sf::Uint32>& indices();
		const std::vector<sf::Uint32>& indices() const;

		virtual void draw(float deltaTime);

	protected:
		void rebuildBuffers();

		std::vector<Vector3> m_vertices;
		std::vector<sf::Uint32> m_indices;

	private:
		sf::Uint32 m_bufferVertices;
		sf::Uint32 m_bufferIndices;
	};
}
