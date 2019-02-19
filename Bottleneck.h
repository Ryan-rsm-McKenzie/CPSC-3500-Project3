#pragma once

#include <queue>  // queue

#include "Vehicle.h"  // Vehicle


#if _WIN32
#include "mutex.h"  // mutex
#include "semaphore.h"  // semaphore
#else
#include <pthread.h>  // pthread_mutex_t
#include <semaphore.h>  // sem_t


typedef sem_t semaphore;
typedef pthread_mutex_t mutex;
#endif


// Bidrectional road with a single lane, i.e. a "bottleneck"
// Class should be mutated using thread safe locker
class Bottleneck
{
	friend class Locker;
public:
	using VehicleQueue = std::queue<Vehicle>;
	using size_type = VehicleQueue::size_type;


	// Locks the Bottleneck on construction and automatically unlocks on destruction
	class Locker
	{
	public:
		Locker() = delete;	// Locker must be constructed using object to lock
		Locker(Bottleneck* a_obj);	// Locks object
		~Locker();	// Unlocks object

	protected:
		Bottleneck* _obj;	// Object to lock
	};


	static Bottleneck* GetSingleton();	// Returns the singleton instance
	static void Free();	// Frees the singleton instance

	semaphore* GetSemaphore();	// Returns the semaphore associated with the class
	bool HasQueuedVehicles() const;	// Returns true if vehicles are waiting in either queue, else false
	size_type GetNorthVehicleCount() const;	// Returns the number of vehicles queued in the north queue
	size_type GetSouthVehicleCount() const;	// Returns the number of vehicles queued in the south queue
	void PushNorthVehicle(Vehicle a_vehicle);	// Pushes the vehicle to the north queue
	void PushSouthVehicle(Vehicle a_vehicle);	// Pushes the vehicle to the south queue
	Vehicle PopNorthVehicle();	// Removes a vehicle from the front of the north queue, unspecified behaviour if empty
	Vehicle PopSouthVehicle();	// Removes a vehicle from the front of the south queue, unspecified behaviour if empty

protected:
	Bottleneck();	// Initializes mutex and semaphore
	~Bottleneck();	// Destroys mutex and semaphore


	static Bottleneck* _singleton;	// Singleton instance
	VehicleQueue _north;	// Queue of vehicles on the north end of the road
	VehicleQueue _south;	// Queue of vehicles on the south end of the road
	mutable mutex _lock;	// Lock for synchronizing access
	mutable semaphore _semaphore;	// Semaphore for blocking threads while both queues are empty
};
