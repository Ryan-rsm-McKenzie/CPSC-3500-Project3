#include <cstdlib>  // size_t, atoi
#include <iostream>  // cout, endl
#include <utility>  // move
#include <vector>  // vector

#include "Bottleneck.h"  // Bottleneck
#include "TrafficDirector.h"  // TrafficDirector
#include "TrafficSimulator.h"  // TrafficSimulator
#include "Util.h"  // SleepFor
#include "Vehicle.h"  // Vehicle


typedef void* thread_callback_t(void*);


#if _WIN32
#include <thread>	// thread
#include "semaphore.h"  // semaphore


typedef std::thread thread_t;


void SpawnThread(std::vector<thread_t>& a_container, thread_callback_t* a_callback)
{
	a_container.emplace_back(a_callback, nullptr);
}


void JoinThread(thread_t& a_thread)
{
	a_thread.join();
}
#else
#include <pthread.h>  // pthread_t, pthread_create, pthread_join
#include <semaphore.h>  // sem_wait


typedef pthread_t thread_t;


void SpawnThread(std::vector<thread_t>& a_container, thread_callback_t* a_callback)	// Spawns a thread in the specified container using the specified callback
{
	a_container.emplace_back();
	pthread_create(&a_container.back(), 0, a_callback, 0);
}


void JoinThread(thread_t& a_thread)	// Joins the specified thread
{
	void* retVal;
	pthread_join(a_thread, &retVal);
}
#endif


volatile bool g_run = false;	// Indicates whether threads should continue main loop execution
volatile bool g_terminate = false;	// Indicates the simulator should wake all listeners in the semaphore


void* DirectorCallback(void*)	// Callback for the Director
{
	TrafficDirector director;
	semaphore* sem = Bottleneck::GetSingleton()->GetSemaphore();
	Vehicle::PrintHeader(director.GetCarLog());
	director.PrintHeader();
	while (g_run) {
		director.TimeStamp(false);
		sem_wait(sem);
		director.TimeStamp(true);
		director.Run();
	}
	return 0;
}


void* SimulatorCallback(void*)	// Callback for the Simulator
{
	TrafficSimulator simulator;
	while (g_run && !g_terminate) {
		simulator.Run();
		if (g_run) {
			SleepFor(20);
		}
	}
	while (g_terminate) {	// g_terminate must be true before g_run is false!!
		simulator.Notify();
	}
	return 0;
}


// enum for indexing thread array
enum
{
	kDirector = 0,
	kSimulator
};


int main(int argc, char* argv[])
{
	std::size_t secondsToRun = 0;
	if (argc != 2) {
		std::printf("Usage: <seconds-to-run>\n");
		return -1;
	} else {
		secondsToRun = std::atoi(argv[1]);
	}

	Bottleneck* bottleneck = Bottleneck::GetSingleton();

	g_terminate = false;
	g_run = true;
	std::vector<thread_t> threads;
	SpawnThread(threads, DirectorCallback);
	SpawnThread(threads, SimulatorCallback);

	while (secondsToRun--) {
		SleepFor(1);
		std::cout << "Running..." << std::endl;
	}

	g_terminate = true;
	g_run = false;
	JoinThread(threads[kDirector]);
	g_terminate = false;
	JoinThread(threads[kSimulator]);

	bottleneck->Free();
	return 0;
}
