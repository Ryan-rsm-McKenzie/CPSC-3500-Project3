#pragma once

#include <condition_variable>  // condition_variable
#include <cstdlib>  // size_t
#include <mutex>  // mutex


// https://stackoverflow.com/a/4793662
class semaphore
{
public:
	semaphore();

	void notify_one();
	void wait();
	bool try_wait();

protected:
	mutable std::mutex _mutex;
	std::condition_variable _condition;
	volatile std::size_t _count;	// init'd locked
};


int sem_init(semaphore*, int, unsigned int);
int sem_wait(semaphore* a_sem);
int sem_post(semaphore* a_sem);
int sem_destroy(semaphore*);
