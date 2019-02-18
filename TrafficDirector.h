#pragma once

#include <cstdlib>  // size_t
#include <fstream>  // ofstream

#include "Singleton.h"  // Singleton
#include "Util.h"  // ENDL, MAKE_STR, COLUMN_WIDTH


#define TRAFFIC_DIRECTOR_FMT %-*s\t%-*s ENDL


namespace TrafficDirectorLiterals
{
	static constexpr char FMT[] = MAKE_STR(TRAFFIC_DIRECTOR_FMT);
	static constexpr char TIME[] = "Time";
	static constexpr char STATE[] = "State";
	static constexpr char CAR_LOG[] = "car.log";
	static constexpr char FLAG_LOG[] = "flagperson.log";
	static constexpr std::size_t TIME_LEN = sizeof(TIME) - 1 > COLUMN_WIDTH ? sizeof(TIME) - 1 : COLUMN_WIDTH;
	static constexpr std::size_t STATE_LEN = sizeof(STATE) - 1 > COLUMN_WIDTH ? sizeof(STATE) - 1 : COLUMN_WIDTH;
}


class TrafficDirector : public Singleton<TrafficDirector>
{
	friend class Singleton<TrafficDirector>;
public:
	void Run();
	void PrintHeader();
	void TimeStamp(bool a_awake);
	std::ofstream* GetCarLog();

protected:
	enum class Mode
	{
		kInvalid,
		kNorth,
		kSouth
	};


	TrafficDirector();
	~TrafficDirector();


	Mode _mode;
	std::ofstream _carFile;
	std::ofstream _flagFile;
};
