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


	Mode _mode;
	std::ofstream _carFile;
	std::ofstream _flagFile;
};
