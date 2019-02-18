#pragma once

#include <cstdint>  // uint_fast32_t
#include <cstdlib>  // size_t
#include <random>  // mt19937
#include <vector>  // vector

#include "Singleton.h"  // Singleton

struct Vehicle;


#if _WIN32
#include "semaphore.h"  // semaphore
#else
#include <semaphore.h>  // sem_t
typedef sem_t semaphore;
#endif


class TrafficSimulator : public Singleton<TrafficSimulator>
{
	friend class Singleton<TrafficSimulator>;
public:
	void Run();
	void Notify();
	semaphore* GetSemaphore();

protected:
	TrafficSimulator();
	~TrafficSimulator();

	bool Roll(std::uint_fast32_t a_chance);


	static constexpr std::uint_fast32_t CAR_CHANCE = 80;
	static constexpr std::uint_fast32_t NORTH_CHANCE = 50;
	std::mt19937 _rng;
	std::vector<Vehicle*> _cars;
	std::size_t _nextID;
	semaphore _semaphore;
};


constexpr decltype(TrafficSimulator::CAR_CHANCE) TrafficSimulator::CAR_CHANCE;
constexpr decltype(TrafficSimulator::NORTH_CHANCE) TrafficSimulator::NORTH_CHANCE;
