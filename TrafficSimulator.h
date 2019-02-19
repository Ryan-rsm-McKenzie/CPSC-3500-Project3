#pragma once

#include <cstdint>  // uint_fast32_t
#include <cstdlib>  // size_t
#include <random>  // mt19937
#include <vector>  // vector

#include "Vehicle.h"  // Vehicle


class TrafficSimulator
{
public:
	TrafficSimulator();
	~TrafficSimulator();

	void Run();	// Acquires a lock on the bottleneck, spawns cars on either end, and notifies the director when done
	void Notify();	// Notifies a listener in the bottleneck semaphore

protected:
	bool Roll(std::uint_fast32_t a_chance);	// Rolls an evenly distributed dice out of 100


	static constexpr std::uint_fast32_t CAR_CHANCE = 80;	// Chance of another car spawning
	static constexpr std::uint_fast32_t NORTH_CHANCE = 50;	// Chance a car arrives from the north end
	std::mt19937 _rng;	// Random number generator
	std::size_t _nextID;	// ID to assign to the next spawned car
};
