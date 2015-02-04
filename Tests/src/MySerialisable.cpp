#include "MySerialisable.h"

MySerialisable::MySerialisable(int value) :
	m_value(value)
{

}

bool MySerialisable::operator==(const MySerialisable& o) const
{
	return o.m_value == m_value;
}