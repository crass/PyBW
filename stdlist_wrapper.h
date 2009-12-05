#pragma once
#include <list>

template<class T>
class ListWrapper
{
private:
	const std::list<T>* _list;
	typename std::list<T>::const_iterator _iter;
public:
	ListWrapper(const std::list<T> original)
		: _list( new const std::list<T>( original) )
	{
		_iter = _list->begin();
	}

	~ListWrapper()
	{
		delete _list;
	}

	int __len__()
	{
		return _list->size();
	}

	int _size()
	{
		return _list->size();
	}

	bool __contains__(T item)
	{
		for(std::list<T>::const_iterator iter = this->_list->begin(); 
				iter != this->_list->end(); iter++) {
			if (*iter == item) {
				return true;
			}
		}
		return false;
	}

	ListWrapper<T>* __iter__()
	{
		_iter = _list->begin();
		return new ListWrapper<T>(*_list);
	}

	T next()
	{
		if (_iter == _list->end())
		{
			return NULL;
		}

		return *(_iter++);
	}
};


template<class T>
class ListWrapper_PtrNext
{
private:
	const std::list<T>* _list;
	typename std::list<T>::const_iterator _iter;
public:
	ListWrapper_PtrNext(const std::list<T> original)
		: _list( new const std::list<T>( original) )
	{
		_iter = _list->begin();
	}

	~ListWrapper_PtrNext()
	{
		delete _list;
	}

	int __len__()
	{
		return _list->size();
	}

	int _size()
	{
		return _list->size();
	}

	bool __contains__(T item)
	{
		for(std::list<T>::const_iterator iter = this->_list->begin(); 
				iter != this->_list->end(); iter++) {
			if (*iter == item) {
				return true;
			}
		}
		return false;
	}

	ListWrapper_PtrNext<T>* __iter__()
	{
		_iter = _list->begin();
		return new ListWrapper_PtrNext<T>(*_list);
	}

	const T* next()
	{
		if (_iter == _list->end())
		{
			return NULL;
		}

		return &*(_iter++);
	}
};


