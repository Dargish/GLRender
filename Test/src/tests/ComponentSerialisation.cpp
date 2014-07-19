#include <boost/test/unit_test.hpp>
#include "components/TransformComponent.h"
#include <json/json.h>
#include "core/TypeDefs.h"
#include "graphics/Transform.h"
#include "serialisation/Serialiser.h"

using namespace components;
using namespace serialisation;

BOOST_AUTO_TEST_CASE(ComponentSerialisation)
{
	{
		Vector3 position(1, 2, 3);
		Vector3 rotation(4, 5, 6);
		Vector3 scale(7, 8, 9);
		TransformComponent t1;
		t1.transform.reset( new graphics::Transform(position, rotation, scale) );
		Json::Value ca = t1.serialise();
		TransformComponent_Ptr t2(Serialiser::Deserialise<TransformComponent>(ca));
		{
			Matrix4 t1t = t1.transform->world();
			Matrix4 t2t = t2->transform->world();
			for (size_t c = 0; c < 4; ++c)
			{
				Matrix4::col_type& col1 = t1t[c];
				Matrix4::col_type& col2 = t2t[c];
				for (size_t r = 0; r < 4; ++r)
				{
					BOOST_REQUIRE_EQUAL(col1[r], col2[r]);
				}
			}
		}
	}
}