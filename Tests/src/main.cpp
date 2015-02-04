#include "MySerialisable.h"

// STL
#include <iostream>
#include <fstream>

// BOOST
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

int main()
{
	std::string fileName = "serialisation.test";

	MySerialisable s1(1);
	MySerialisable s2;

	{
		std::ofstream ofs(fileName.c_str());
		boost::archive::text_oarchive ar(ofs);
		ar & s1 & s2;
	}

	MySerialisable d1;
	MySerialisable d2;

	{
		std::ifstream ifs(fileName.c_str());
		boost::archive::text_iarchive ar(ifs);
		ar & d1 & d2;
	}

	std::cerr << "s1 == s2 = " << ((s1 == s2) ? "True" : "False") << std::endl;
	std::cerr << "s1 == d1 = " << ((s1 == d1) ? "True" : "False") << std::endl;
	std::cerr << "s2 == d2 = " << ((s2 == d2) ? "True" : "False") << std::endl;

	return 0;
}
