#include "Bottleneck.h"

#include <cassert>  // assert


Bottleneck::Locker::Locker(Bottleneck* a_obj)
{
	_obj = a_obj;
	pthread_mutex_lock(&_obj->_lock);
}


Bottleneck::Locker::~Locker()
{
	pthread_mutex_unlock(&_obj->_lock);
}


Bottleneck* Bottleneck::GetSingleton()
{
	if (!_singleton) {
		_singleton = new Bottleneck();
	}
	return _singleton;
}


void Bottleneck::Free()
{
#if _DEBUG
	assert(_singleton);
#endif
	delete _singleton;
	_singleton = 0;
}


semaphore* Bottleneck::GetSemaphore()
{
	return &_semaphore;
}


bool Bottleneck::HasQueuedVehicles() const
{
	return !_north.empty() || !_south.empty();
}


Bottleneck::size_type Bottleneck::GetNorthVehicleCount() const
{
	return _north.size();
}


Bottleneck::size_type Bottleneck::GetSouthVehicleCount() const
{
	return _south.size();
}


void Bottleneck::PushNorthVehicle(Vehicle a_vehicle)
{
	_north.push(a_vehicle);
}


void Bottleneck::PushSouthVehicle(Vehicle a_vehicle)
{
	_south.push(a_vehicle);
}


Vehicle Bottleneck::PopNorthVehicle()
{
	Vehicle ret = _north.front();
	_north.pop();
	return ret;
}


Vehicle Bottleneck::PopSouthVehicle()
{
	Vehicle ret = _south.front();
	_south.pop();
	return ret;
}


Bottleneck::Bottleneck()
{
	pthread_mutex_init(&_lock, 0);
	sem_init(&_semaphore, 0, 0);
}


Bottleneck::~Bottleneck()
{
	pthread_mutex_destroy(&_lock);
	sem_destroy(&_semaphore);
}


Bottleneck* Bottleneck::_singleton = 0;
