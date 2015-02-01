#include "MySerialisable.h"
#include "MyFileSerialisable.h"

#include <iostream>

using namespace glr;

int main()
{
	MySerialisable s;
	std::cerr << s.typeName() << std::endl;

	MyFileSerialisable f;
	std::cerr << f.typeName() << std::endl;

	f.save("Test1");

	return 0;
}
