#pragma once
#include <map>

template<class K, class V>
class MapIterator
{
private:
	const std::map<K, V> _map;
	typename std::map<K, V>::const_iterator _iter;
	std::pair<K, V> _current;
public:
	MapIterator(const std::map<K, V> original)
		: _map( original )
	{
		this->_iter = this->_map.begin();
	}

	~MapIterator()
	{
	}
    
	K next()
	{
		if (this->_iter == this->_map.end())
		{
			return NULL;
		}

		this->_current = *this->_iter;
		this->_iter++;
		return _current.first;
	}

	K getKey()
	{
		return this->_current.first;
	}

	V getValue()
	{
		return this->_current.second;
	}

	MapIterator<K,V>* __iter__()
	{
		return new MapIterator<K,V>(_map);
	}

};


template<class K, class V>
class MapWrapper
{
private:
	const std::map<K, V> _map;
public:
	MapWrapper(const std::map<K, V> original)
		: _map( original )
	{
	}

	~MapWrapper()
	{
	}

	int __len__()
	{
		return this->_map.size();
	}

	MapIterator<K,V>* __iter__()
	{
		return new MapIterator<K,V>(_map);
	}

};


/////
//


template<class K, class V>
class MapIterator_PtrNext
{
private:
	const std::map<K, V> _map;
	typename std::map<K, V>::const_iterator _iter;
	//const std::pair<K, V>* _current;
public:
	MapIterator_PtrNext(const std::map<K, V> original)
		: _map( original )
	{
		this->_iter = this->_map.begin();
	}

	~MapIterator_PtrNext()
	{
	}
    
	const K* next()
	{
		if (this->_iter == this->_map.end())
		{
			return NULL;
		}

		const K* first = & this->_iter->first;
		this->_iter++;
		return first;
	}

	const K* getKey()
	{
		const K* k = &this->_iter->first;
		return k;
	}

	const V* getValue()
	{
		const V* v = &this->_iter->second;
		return v;
	}

	MapIterator_PtrNext<K,V>* __iter__()
	{
		return new MapIterator_PtrNext<K,V>(_map);
	}

};


template<class K, class V>
class MapWrapper_PtrNext
{
private:
	const std::map<K, V> _map;
public:
	MapWrapper_PtrNext(const std::map<K, V> original)
		: _map( original )
	{
	}

	~MapWrapper_PtrNext()
	{
	}

	int __len__()
	{
		return this->_map.size();
	}

	MapIterator_PtrNext<K,V>* __iter__()
	{
		return new MapIterator_PtrNext<K,V>(_map);
	}

};
