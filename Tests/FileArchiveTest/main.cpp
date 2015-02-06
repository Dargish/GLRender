#include <GLRender/FileArchive.h>

using namespace glr;

namespace boost
{
	namespace serialization
	{
		class access;
	}
}

class MySerialisable
{
public:
	MySerialisable(int value = -1) :
		m_value(value)
	{

	}

	bool operator==(const MySerialisable& o) const
	{
		return o.m_value == m_value;
	}

private:
	int m_value;

	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive& ar, const unsigned version)
	{
		ar & m_value;
	}
};


int main()
{
	MySerialisable s1(20);

	FileOArchive("FileArchiveTest.data").archive & s1;

	MySerialisable d1;

	FileIArchive("FileArchiveTest.data").archive & d1;

	assert(s1 == d1);

	return 0;
}
