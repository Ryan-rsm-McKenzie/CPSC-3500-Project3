#pragma once

#include <cstdlib>  // size_t
#include <fstream>  // ofstream

#include "Util.h"  // COLUMN_WIDTH


class TrafficDirector
{
public:
	TrafficDirector();
	~TrafficDirector();

	void Run();	// Acquires a lock on the bottleneck and directs queued cars through it
	void PrintHeader();	// Prints the director log header
	void TimeStamp(bool a_awake);	// Logs an event to the director log
	std::ofstream* GetCarLog();	// Returns the car log file

protected:
	enum class Mode
	{
		kInvalid,
		kNorth,
		kSouth
	};


	static constexpr char FMT[] = "%-*s\t%-*s\n";	// Format string for logging
	static constexpr char TIME[] = "Time";	// Column names
	static constexpr char STATE[] = "State";
	static constexpr char CAR_LOG[] = "car.log";
	static constexpr char FLAG_LOG[] = "flagperson.log";
	static constexpr std::size_t TIME_LEN = sizeof(TIME) - 1 > COLUMN_WIDTH ? sizeof(TIME) - 1 : COLUMN_WIDTH;	// Column widths
	static constexpr std::size_t STATE_LEN = sizeof(STATE) - 1 > COLUMN_WIDTH ? sizeof(STATE) - 1 : COLUMN_WIDTH;
	Mode _mode;	// Current direction traffic is spawning from
	std::ofstream _carFile;	// File to print car events to
	std::ofstream _flagFile;	// File to print director events to
};
