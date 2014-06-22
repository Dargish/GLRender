#include "Cube.h"

namespace graphics
{
	Cube_Ptr Cube::Create(float size /*= 1.0f*/)
	{
		Cube_Ptr cube(new Cube);
		cube->resize(size);
		return cube;
	}

	Cube::Cube() :
		m_size(0.0f)
	{
	}

	Cube::~Cube()
	{
	}

	void Cube::resize(float size)
	{
		m_size = size;
		if (m_vertices.size() != 8)
		{
			m_vertices.resize(8);
		}
		float halfSize = m_size * 0.5f;
		for (size_t i = 0; i < 8; ++i)
		{
			m_vertices[i] = Vector3(i & 1 ? -halfSize : halfSize, i & 2 ? -halfSize : halfSize, i & 4 ? -halfSize : halfSize);
		}
		if (m_indices.size() != 16)
		{
			m_indices.resize(16);
		}
		m_indices[0] = 7;
		m_indices[1] = 5;
		m_indices[2] = 6;
		m_indices[3] = 4;
		m_indices[4] = 2;
		m_indices[5] = 0;
		m_indices[6] = 3;
		m_indices[7] = 1;
		m_indices[8] = 0;
		m_indices[9] = 4;
		m_indices[10] = 1;
		m_indices[11] = 5;
		m_indices[12] = 3;
		m_indices[13] = 7;
		m_indices[14] = 2;
		m_indices[15] = 6;
		rebuildBuffers();
	}

	void Cube::serialise(Json::Value& jsonArray)
	{

	}

	void Cube::deserialise(Json::Value& jsonDict)
	{

	}
}
