#pragma once

#include <cstdlib>  // size_t
#include <fstream>  // ofstream

#include "Singleton.h"  // Singleton
#include "Util.h"  // ENDL, MAKE_STR, COLUMN_WIDTH


#define TRAFFIC_DIRECTOR_FMT %-*s\t%-*s ENDL


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


	static constexpr char FMT[] = MAKE_STR(TRAFFIC_DIRECTOR_FMT);
	static constexpr char TIME[] = "Time";
	static constexpr char STATE[] = "State";
	static constexpr char CAR_LOG[] = "car.log";
	static constexpr char FLAG_LOG[] = "flagperson.log";
	static constexpr std::size_t TIME_LEN = sizeof(TIME) - 1 > COLUMN_WIDTH ? sizeof(TIME) - 1 : COLUMN_WIDTH;
	static constexpr std::size_t STATE_LEN = sizeof(STATE) - 1 > COLUMN_WIDTH ? sizeof(STATE) - 1 : COLUMN_WIDTH;
	Mode _mode;
	std::ofstream _carFile;
	std::ofstream _flagFile;
};


constexpr decltype(TrafficDirector::FMT) TrafficDirector::FMT;
constexpr decltype(TrafficDirector::TIME) TrafficDirector::TIME;
constexpr decltype(TrafficDirector::STATE) TrafficDirector::STATE;
constexpr decltype(TrafficDirector::CAR_LOG) TrafficDirector::CAR_LOG;
constexpr decltype(TrafficDirector::FLAG_LOG) TrafficDirector::FLAG_LOG;
constexpr decltype(TrafficDirector::TIME_LEN) TrafficDirector::TIME_LEN;
constexpr decltype(TrafficDirector::STATE_LEN) TrafficDirector::STATE_LEN;
