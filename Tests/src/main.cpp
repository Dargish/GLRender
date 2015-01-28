#include "MySerialisable.h"

#include <iostream>

using namespace glrender;

int main()
{
	MySerialisable s;
	std::cerr << TypeNameTraits<MySerialisable>::Name << std::endl;
	std::cerr << s.typeName() << std::endl;
	return 0;
}
