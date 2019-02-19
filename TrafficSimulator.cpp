#include "TrafficSimulator.h"

#include "Bottleneck.h"  // Bottleneck


TrafficSimulator::TrafficSimulator() :
	_nextID(1)
{}


TrafficSimulator::~TrafficSimulator()
{}


void TrafficSimulator::Run()
{
	{
		Bottleneck* bottleneck = Bottleneck::GetSingleton();
		Bottleneck::Locker locker(bottleneck);
		Vehicle car;
		do {
			car.id = _nextID++;
			car.TimeStampArrival();
			if (Roll(NORTH_CHANCE)) {
				car.direction = Vehicle::CardinalDirection::kNorth;
				bottleneck->PushNorthVehicle(car);
			} else {
				car.direction = Vehicle::CardinalDirection::kSouth;
				bottleneck->PushSouthVehicle(car);
			}
		} while (Roll(CAR_CHANCE));
	}
	Notify();
}


void TrafficSimulator::Notify()
{
	sem_post(Bottleneck::GetSingleton()->GetSemaphore());
}


bool TrafficSimulator::Roll(std::uint_fast32_t a_chance)
{
	return (_rng() % 100) <= a_chance;
}


constexpr decltype(TrafficSimulator::CAR_CHANCE) TrafficSimulator::CAR_CHANCE;
constexpr decltype(TrafficSimulator::NORTH_CHANCE) TrafficSimulator::NORTH_CHANCE;
