#include "Bottleneck.h"


Bottleneck::Locker::Locker(Bottleneck* a_obj)
{
	_obj = a_obj;
	pthread_mutex_lock(&_obj->_lock);
}


Bottleneck::Locker::~Locker()
{
	pthread_mutex_unlock(&_obj->_lock);
}


Bottleneck::Bottleneck()
{
	pthread_mutex_init(&_lock, 0);
}


Bottleneck::~Bottleneck()
{
	pthread_mutex_destroy(&_lock);
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


void Bottleneck::PushNorthVehicle(Vehicle* a_vehicle)
{
	_north.push(a_vehicle);
}


void Bottleneck::PushSouthVehicle(Vehicle* a_vehicle)
{
	_south.push(a_vehicle);
}


Vehicle* Bottleneck::PopNorthVehicle()
{
	Vehicle* ret = _north.front();
	_north.pop();
	return ret;
}


Vehicle* Bottleneck::PopSouthVehicle()
{
	Vehicle* ret = _south.front();
	_south.pop();
	return ret;
}
