#include "semaphore.h"

#include <mutex>  // lock_guard, unique_lock


semaphore::semaphore() :
	_count(0)
{}


void semaphore::notify_one()
{
	std::lock_guard<decltype(_mutex)> lock(_mutex);
	++_count;
	_condition.notify_one();
}


void semaphore::wait()
{
	std::unique_lock<decltype(_mutex)> lock(_mutex);
	while (!_count) {	// Handle spurious wake-ups.
		_condition.wait(lock);
	}
	--_count;
}


bool semaphore::try_wait()
{
	std::lock_guard<decltype(_mutex)> lock(_mutex);
	if (_count) {
		--_count;
		return true;
	}
	return false;
}


int sem_init(semaphore*, int, unsigned int)
{
	return 0;
}


int sem_wait(semaphore* a_sem)
{
	a_sem->wait();
	return 0;
}


int sem_post(semaphore* a_sem)
{
	a_sem->notify_one();
	return 0;
}


int sem_destroy(semaphore*)
{
	return 0;
}
