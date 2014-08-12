#include <boost/test/unit_test.hpp>
#include <boost/format.hpp>
#include "graphics/Cube.h"
#include "graphics/VertexBuffer.h"
#include <GL/glew.h>
#include <iostream>

using namespace graphics;

BOOST_AUTO_TEST_CASE(PrimitiveCreation)
{
	sf::Context context;
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		throw std::runtime_error((boost::format("glewInit() failed: %s") % glewGetErrorString(err)).str());
	}
	{
		graphics::Cube_Ptr cube(new Cube(2.0f));
		VertexPositionNormalBuffer_Ptr vBuffer = boost::dynamic_pointer_cast<VertexPositionNormalBuffer>(cube->vertexBuffer());
		VertexPositionNormalBuffer::BufferType& verts = vBuffer->data();
		BOOST_REQUIRE_EQUAL(verts.size(), 8);
		BOOST_REQUIRE_EQUAL(verts[0].position.x, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[0].position.y, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[0].position.z, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[1].position.x, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[1].position.y, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[1].position.z, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[2].position.x, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[2].position.y, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[2].position.z, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[3].position.x, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[3].position.y, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[3].position.z, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[4].position.x, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[4].position.y, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[4].position.z, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[5].position.x, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[5].position.y, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[5].position.z, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[6].position.x, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[6].position.y, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[6].position.z, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[7].position.x, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[7].position.y, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[7].position.z, -1.0f);
		cube->resize(4.0f);
		BOOST_REQUIRE_EQUAL(verts[0].position.x, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[0].position.y, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[0].position.z, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[1].position.x, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[1].position.y, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[1].position.z, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[2].position.x, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[2].position.y, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[2].position.z, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[3].position.x, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[3].position.y, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[3].position.z, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[4].position.x, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[4].position.y, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[4].position.z, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[5].position.x, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[5].position.y, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[5].position.z, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[6].position.x, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[6].position.y, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[6].position.z, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[7].position.x, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[7].position.y, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[7].position.z, -2.0f);

	}
}