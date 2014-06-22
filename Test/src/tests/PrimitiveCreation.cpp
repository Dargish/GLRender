#include <boost/test/unit_test.hpp>
#include <boost/format.hpp>
#include "graphics/Cube.h"
#include <GL/glew.h>
#include <iostream>

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
		graphics::Cube_Ptr cube = graphics::Cube::Create(2.0f);
		std::vector<Vector3>& verts = cube->vertices();
		BOOST_REQUIRE_EQUAL(verts.size(), 8);
		BOOST_REQUIRE_EQUAL(verts[0].x, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[0].y, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[0].z, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[1].x, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[1].y, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[1].z, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[2].x, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[2].y, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[2].z, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[3].x, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[3].y, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[3].z, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[4].x, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[4].y, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[4].z, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[5].x, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[5].y, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[5].z, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[6].x, 1.0f);
		BOOST_REQUIRE_EQUAL(verts[6].y, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[6].z, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[7].x, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[7].y, -1.0f);
		BOOST_REQUIRE_EQUAL(verts[7].z, -1.0f);
		cube->resize(4.0f);
		BOOST_REQUIRE_EQUAL(verts[0].x, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[0].y, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[0].z, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[1].x, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[1].y, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[1].z, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[2].x, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[2].y, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[2].z, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[3].x, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[3].y, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[3].z, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[4].x, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[4].y, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[4].z, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[5].x, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[5].y, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[5].z, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[6].x, 2.0f);
		BOOST_REQUIRE_EQUAL(verts[6].y, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[6].z, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[7].x, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[7].y, -2.0f);
		BOOST_REQUIRE_EQUAL(verts[7].z, -2.0f);

	}
}