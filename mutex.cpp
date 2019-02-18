#include "mutex.h"


int pthread_mutex_init(mutex*, const void*)
{
	return 0;
}


int pthread_mutex_lock(mutex* a_mutex)
{
	a_mutex->lock();
	return 0;
}


int pthread_mutex_unlock(mutex* a_mutex)
{
	a_mutex->unlock();
	return 0;
}


int pthread_mutex_destroy(mutex*)
{
	return 0;
}
