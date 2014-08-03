#pragma once
#include "fwd.h"
#include "Mesh.h"
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
		void dirtyVertexBuffer();
		void dirtyIndexBuffer();

		std::vector<Vector3> m_vertices;
		std::vector<sf::Uint32> m_indices;

	private:
		void rebuildVertexBuffer();
		void rebuildIndexBuffer();

		bool m_vertexBufferDirty;
		bool m_indexBufferDirty;

		sf::Uint32 m_bufferVertices;
		sf::Uint32 m_bufferIndices;
	};
}
