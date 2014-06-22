#include <boost/test/unit_test.hpp>
#include "ecs/components/TransformComponent.h"
#include <json/json.h>
#include "core/TypeDefs.h"

BOOST_AUTO_TEST_CASE(ComponentSerialisation)
{
	{
		Matrix4 t(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f);
		ecs::TransformComponent t1(t);
		Json::Value ca = Json::Value(Json::arrayValue);
		t1.serialise(ca);
		ecs::TransformComponent t2;
		t2.deserialise(ca[size_t(0)]);
		{
			for (size_t c = 0; c < 4; ++c)
			{
				Matrix4::col_type& col1 = t1.transform[c];
				Matrix4::col_type& col2 = t2.transform[c];
				for (size_t r = 0; r < 4; ++r)
				{
					BOOST_REQUIRE_EQUAL(col1[r], col2[r]);
				}
			}
		}
	}
}