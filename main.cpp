#include "Bottleneck.h"  // Bottleneck
#include "TrafficDirector.h"  // TrafficDirector
#include "TrafficSimulator.h"  // TrafficSimulator
#include "Util.h"  // SleepFor
#include "Vehicle.h"  // Vehicle

#include <cstdlib>  // size_t, atoi
#include <iostream>  // cout, endl
#include <utility>  // move
#include <vector>  // vector


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


void SpawnThread(std::vector<thread_t>& a_container, thread_callback_t* a_callback)
{
	a_container.emplace_back();
	pthread_create(&a_container.back(), 0, a_callback, 0);
}


void JoinThread(thread_t& a_thread)
{
	void* retVal;
	pthread_join(a_thread, &retVal);
}
#endif


volatile bool g_run = false;
volatile bool g_terminate = false;


void* DirectorCallback(void*)
{
	TrafficDirector* director = TrafficDirector::GetSingleton();
	semaphore* sem = TrafficSimulator::GetSingleton()->GetSemaphore();
	Vehicle::PrintHeader(director->GetCarLog());
	director->PrintHeader();
	while (g_run) {
		director->TimeStamp(false);
		sem_wait(sem);
		director->TimeStamp(true);
		director->Run();
	}
	return 0;
}


void* SimulatorCallback(void*)
{
	TrafficSimulator* simulator = TrafficSimulator::GetSingleton();
	while (g_run && !g_terminate) {
		simulator->Run();
		if (g_run) {
			SleepFor(20);
		}
	}
	while (g_terminate) {
		simulator->Notify();
	}
	return 0;
}


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
	TrafficDirector* director = TrafficDirector::GetSingleton();
	TrafficSimulator* simulator = TrafficSimulator::GetSingleton();

	g_run = true;
	g_terminate = false;
	std::vector<thread_t> threads;
	SpawnThread(threads, DirectorCallback);
	SpawnThread(threads, SimulatorCallback);

	for (std::size_t i = 0; i < secondsToRun; ++i) {
		SleepFor(1);
		std::cout << "Running..." << std::endl;
	}

	g_run = false;
	g_terminate = true;
	JoinThread(threads[kDirector]);
	g_terminate = false;
	JoinThread(threads[kSimulator]);

	bottleneck->Free();
	director->Free();
	simulator->Free();
	return 0;
}
