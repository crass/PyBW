#pragma once
#include <utility>

template<class T1, class T2>
class PairWrapper
{
public:
	T1 _first;
	T2 _second;

	PairWrapper(const std::pair<T1, T2> original)
		: _first( original.first), _second( original.second )
	{
	}

	T1 first() const
	{
		return _first;
	}

	T2 second() const
	{
		return _second;
	}
};

