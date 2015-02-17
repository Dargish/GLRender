#pragma once

#include <GLRender/World/Entity.h>

#include <vector>

namespace glr
{
	class System
	{
	public:
		virtual void update(float deltaTime) = 0;

	private:
	};
}