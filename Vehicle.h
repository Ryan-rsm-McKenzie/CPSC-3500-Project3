#pragma once

#include <cstdlib>  // size_t
#include <ctime>  // time_t
#include <fstream>  // ofstream

#include "Util.h"  // COLUMN_WIDTH


struct Vehicle
{
public:
	enum class CardinalDirection
	{
		kInvalid,
		kNorth,
		kEast,
		kSouth,
		kWest
	};


	Vehicle();	// All variables begin in an invalid state
	~Vehicle();

	static void PrintHeader(std::ofstream* a_file);	// Prints the header for the car log
	void TimeStampArrival();	// Timestamps the arrival time with the current time
	void TimeStampStart();	// Timestamps the start time with the current time
	void TimeStampEnd();	// Timestamps the end time with the current time
	void Dump(std::ofstream* a_file) const;


	std::size_t id;	// Unique ID for identifying the car
	CardinalDirection direction;	// Direction the car is coming from
	std::time_t arrivalTime;	// Time the car arrived on the road
	std::time_t startTime;	// Time the car began crossing the bottleneck
	std::time_t endTime;	// Time the car finished crossing the bottleneck

protected:
	const char* DirectionToString(CardinalDirection a_direction) const;	// Converts the direction enum into a string


	static constexpr char FMT[] = "%-*s\t%-*s\t%-*s\t%-*s\t%-*s\n";	// Format string for logging
	static constexpr char CAR_ID[] = "Car-ID";	// Column header names
	static constexpr char DIRECTION[] = "Direction";
	static constexpr char ARRIVAL_TIME[] = "Arrival-Time";
	static constexpr char START_TIME[] = "Start-Time";
	static constexpr char END_TIME[] = "End-Time";
	static constexpr std::size_t CAR_ID_LEN = sizeof(CAR_ID) - 1 > COLUMN_WIDTH ? sizeof(CAR_ID) - 1 : COLUMN_WIDTH;	// Column widths
	static constexpr std::size_t DIRECTION_LEN = sizeof(DIRECTION) - 1 > COLUMN_WIDTH ? sizeof(DIRECTION) - 1 : COLUMN_WIDTH;
	static constexpr std::size_t ARRIVAL_TIME_LEN = sizeof(ARRIVAL_TIME) - 1 > COLUMN_WIDTH ? sizeof(ARRIVAL_TIME) - 1 : COLUMN_WIDTH;
	static constexpr std::size_t START_TIME_LEN = sizeof(START_TIME) - 1 > COLUMN_WIDTH ? sizeof(START_TIME) - 1 : COLUMN_WIDTH;
	static constexpr std::size_t END_TIME_LEN = sizeof(END_TIME) - 1 > COLUMN_WIDTH ? sizeof(END_TIME) - 1 : COLUMN_WIDTH;
};
