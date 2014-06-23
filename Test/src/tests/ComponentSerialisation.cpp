#include <boost/test/unit_test.hpp>
#include "ecs/components/TransformComponent.h"
#include <json/json.h>
#include "core/TypeDefs.h"

BOOST_AUTO_TEST_CASE(ComponentSerialisation)
{
	{
		Vector3 position(1, 2, 3);
		Vector3 rotation(4, 5, 6);
		Vector3 scale(7, 8, 9);
		ecs::TransformComponent t1(position, rotation, scale);
		Json::Value ca = Json::Value(Json::arrayValue);
		t1.serialise(ca);
		ecs::TransformComponent t2;
		t2.deserialise(ca[size_t(0)]);
		{
			Matrix4 t1t = t1.transform();
			Matrix4 t2t = t2.transform();
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