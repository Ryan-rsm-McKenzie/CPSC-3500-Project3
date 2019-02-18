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
};
