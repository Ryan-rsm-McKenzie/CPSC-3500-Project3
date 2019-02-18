#pragma once


// Templated singleton pattern
// Requires template parameter be default constructible
template <typename T>
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;


	static T* GetSingleton()
	{
		if (!_singleton) {
			_singleton = new T();
		}
		return _singleton;
	}


	static void Free()
	{
		delete _singleton;
		_singleton = 0;
	}

protected:
	Singleton() {}


	static T* _singleton;
};


template <typename T> T* Singleton<T>::_singleton = 0;
