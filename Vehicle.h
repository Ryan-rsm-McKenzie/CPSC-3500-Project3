#pragma once

#include <cstdlib>  // size_t
#include <ctime>  // time_t
#include <fstream>  // ofstream

#include "Util.h"  // ENDL, MAKE_STR, COLUMN_WIDTH


#define VEHICLE_FMT %-*s\t%-*s\t%-*s\t%-*s\t%-*s ENDL


struct Vehicle
{
	friend class TrafficSimulator;
public:
	enum class CardinalDirection
	{
		kInvalid,
		kNorth,
		kEast,
		kSouth,
		kWest
	};


	static void PrintHeader(std::ofstream* a_file);
	void TimeStampArrival();
	void TimeStampStart();
	void TimeStampEnd();
	void Dump(std::ofstream* a_file) const;


	std::size_t id;
	CardinalDirection direction;
	std::time_t arrivalTime;
	std::time_t startTime;
	std::time_t endTime;

protected:
	// Hidden to delegate instantiation to a single class
	Vehicle();
	~Vehicle();

	const char* DirectionToString(CardinalDirection a_direction) const;


	static constexpr char FMT[] = MAKE_STR(VEHICLE_FMT);
	static constexpr char CAR_ID[] = "Car-ID";
	static constexpr char DIRECTION[] = "Direction";
	static constexpr char ARRIVAL_TIME[] = "Arrival-Time";
	static constexpr char START_TIME[] = "Start-Time";
	static constexpr char END_TIME[] = "End-Time";
	static constexpr std::size_t CAR_ID_LEN = sizeof(CAR_ID) - 1 > COLUMN_WIDTH ? sizeof(CAR_ID) - 1 : COLUMN_WIDTH;
	static constexpr std::size_t DIRECTION_LEN = sizeof(DIRECTION) - 1 > COLUMN_WIDTH ? sizeof(DIRECTION) - 1 : COLUMN_WIDTH;
	static constexpr std::size_t ARRIVAL_TIME_LEN = sizeof(ARRIVAL_TIME) - 1 > COLUMN_WIDTH ? sizeof(ARRIVAL_TIME) - 1 : COLUMN_WIDTH;
	static constexpr std::size_t START_TIME_LEN = sizeof(START_TIME) - 1 > COLUMN_WIDTH ? sizeof(START_TIME) - 1 : COLUMN_WIDTH;
	static constexpr std::size_t END_TIME_LEN = sizeof(END_TIME) - 1 > COLUMN_WIDTH ? sizeof(END_TIME) - 1 : COLUMN_WIDTH;
};


constexpr decltype(Vehicle::FMT) Vehicle::FMT;
constexpr decltype(Vehicle::CAR_ID) Vehicle::CAR_ID;
constexpr decltype(Vehicle::DIRECTION) Vehicle::DIRECTION;
constexpr decltype(Vehicle::ARRIVAL_TIME) Vehicle::ARRIVAL_TIME;
constexpr decltype(Vehicle::START_TIME) Vehicle::START_TIME;
constexpr decltype(Vehicle::END_TIME) Vehicle::END_TIME;
constexpr decltype(Vehicle::CAR_ID_LEN) Vehicle::CAR_ID_LEN;
constexpr decltype(Vehicle::DIRECTION_LEN) Vehicle::DIRECTION_LEN;
constexpr decltype(Vehicle::ARRIVAL_TIME_LEN) Vehicle::ARRIVAL_TIME_LEN;
constexpr decltype(Vehicle::START_TIME_LEN) Vehicle::START_TIME_LEN;
constexpr decltype(Vehicle::END_TIME_LEN) Vehicle::END_TIME_LEN;
