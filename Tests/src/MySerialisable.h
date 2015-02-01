#pragma once

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
	MySerialisable(int value = -1);

	bool operator==(const MySerialisable& o) const;

private:
	int m_value;

	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive& ar, const unsigned version)
	{
		ar & m_value;
	}
};
