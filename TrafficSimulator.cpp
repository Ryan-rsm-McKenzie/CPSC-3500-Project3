#include "TrafficSimulator.h"

#include "Bottleneck.h"  // Bottleneck
#include "Vehicle.h"  // Vehicle


static constexpr std::uint_fast32_t CAR_CHANCE = 80;
static constexpr std::uint_fast32_t NORTH_CHANCE = 50;


void TrafficSimulator::Run()
{
	if (Roll(CAR_CHANCE)) {
		{
			Bottleneck* bottleneck = Bottleneck::GetSingleton();
			Bottleneck::Locker locker(bottleneck);
			do {
				_cars.push_back(new Vehicle());
				_cars.back()->id = _nextID++;
				_cars.back()->TimeStampArrival();
				if (Roll(NORTH_CHANCE)) {
					_cars.back()->direction = Vehicle::CardinalDirection::kNorth;
					bottleneck->PushNorthVehicle(_cars.back());
				} else {
					_cars.back()->direction = Vehicle::CardinalDirection::kSouth;
					bottleneck->PushSouthVehicle(_cars.back());
				}
			} while (Roll(CAR_CHANCE));
		}
		Notify();
	}
}


void TrafficSimulator::Notify()
{
	sem_post(&_semaphore);
}


semaphore* TrafficSimulator::GetSemaphore()
{
	return &_semaphore;
}


TrafficSimulator::TrafficSimulator() :
	_nextID(1)
{
	sem_init(&_semaphore, 0, 0);
}


TrafficSimulator::~TrafficSimulator()
{
	for (auto& car : _cars) {
		delete car;
	}
}


bool TrafficSimulator::Roll(std::uint_fast32_t a_chance)
{
	return (_rng() % 100) <= a_chance;
}
