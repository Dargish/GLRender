#include "MySerialisable.h"
#include "MyFileSerialisable.h"

#include <iostream>

using namespace glrender;

int main()
{
	MySerialisable s;
	std::cerr << s.typeName() << std::endl;

	MyFileSerialisable f;
	std::cerr << f.typeName() << std::endl;

	return 0;
}
