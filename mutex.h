#include <mutex>  // mutex


typedef std::mutex mutex;


int pthread_mutex_init(mutex*, const void*);
int pthread_mutex_lock(mutex* a_mutex);
int pthread_mutex_unlock(mutex* a_mutex);
int pthread_mutex_destroy(mutex* a_mutex);
