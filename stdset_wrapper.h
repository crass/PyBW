#pragma once
#include <set>

template<class T>
class SetWrapper
{
private:
	const std::set<T>& _set;
	typename std::set<T>::const_iterator _iter;
public:
	SetWrapper(const std::set<T>& original)
		: _set( original )
	{
		_iter = _set.begin();
	}

	~SetWrapper()
	{
	}

	int __len__()
	{
		return _set.size();
	}

	bool __contains__(T item)
	{
		std::set<T>::const_iterator iter = this->_set.find(item);
		return iter != this->_set.end();
	}

	SetWrapper<T>* __iter__()
	{
		_iter = _set.begin();
		return new SetWrapper<T>(_set);
	}

	T next()
	{
		if (_iter == _set.end())
		{
			return NULL;
		}

		return *(_iter++);
	}

};

template<class T>
class SetWrapper_PtrNext
{
private:
	const std::set<T>& _set;
	typename std::set<T>::const_iterator _iter;
public:
	SetWrapper_PtrNext(const std::set<T>& original)
		: _set( original )
	{
		_iter = _set.begin();
	}

	~SetWrapper_PtrNext()
	{
	}

	int __len__()
	{
		return _set.size();
	}

	bool __contains__(T item)
	{
		std::set<T>::const_iterator iter = this->_set.find(item);
		return iter != this->_set.end();
	}

	SetWrapper_PtrNext<T>* __iter__()
	{
		_iter = _set.begin();
		return new SetWrapper_PtrNext<T>(_set);
	}

	const T* next()
	{
		if (_iter == _set.end())
		{
			return NULL;
		}

		return &*(_iter++);
	}
};
