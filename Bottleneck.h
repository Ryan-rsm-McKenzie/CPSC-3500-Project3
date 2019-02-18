#pragma once

#include <queue>  // queue

#include "Singleton.h"  // Singleton

struct Vehicle;


#if _WIN32
#include "mutex.h"  // mutex
#else
#include "pthread.h"
typedef pthread_mutex_t mutex;
#endif


// Bidrectional road with a single lane, i.e. a "bottleneck"
// Class should be mutated using thread safe locker
class Bottleneck : public Singleton<Bottleneck>
{
	friend class Singleton<Bottleneck>;
	friend struct Locker;
public:
	using VehicleQueue = std::queue<Vehicle*>;
	using size_type = VehicleQueue::size_type;


	struct Locker
	{
	public:
		Locker() = delete;
		Locker(Bottleneck* a_obj);
		~Locker();

	protected:
		Bottleneck* _obj;
	};


	bool HasQueuedVehicles() const;
	size_type GetNorthVehicleCount() const;
	size_type GetSouthVehicleCount() const;
	void PushNorthVehicle(Vehicle* a_vehicle);
	void PushSouthVehicle(Vehicle* a_vehicle);
	Vehicle* PopNorthVehicle();
	Vehicle* PopSouthVehicle();

protected:
	Bottleneck();
	~Bottleneck();


	VehicleQueue _north;
	VehicleQueue _south;
	mutable mutex _lock;
};
