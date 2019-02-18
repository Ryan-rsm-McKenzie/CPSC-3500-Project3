#include "Vehicle.h"

#include <ctime>  // localtime
#include <stdexcept>  // runtime_error
#include <string>  // to_string
#include <type_traits>  // underlying_type

#include "Util.h"  // TimeToString, GetTime, FormatStr


void Vehicle::TimeStampArrival()
{
	arrivalTime = GetTime();
}


void Vehicle::TimeStampStart()
{
	startTime = GetTime();
}


void Vehicle::TimeStampEnd()
{
	endTime = GetTime();
}


void Vehicle::PrintHeader(std::ofstream* a_file)
{
	(*a_file) << FormatStr(FMT,
						   CAR_ID_LEN, CAR_ID,
						   DIRECTION_LEN, DIRECTION,
						   ARRIVAL_TIME_LEN, ARRIVAL_TIME,
						   START_TIME_LEN, START_TIME,
						   END_TIME_LEN, END_TIME);
#if _DEBUG
	a_file->flush();
#endif
}


void Vehicle::Dump(std::ofstream* a_file) const
{
	std::string arrival = TimeToString(std::localtime(&arrivalTime));
	std::string start = TimeToString(std::localtime(&startTime));
	std::string end = TimeToString(std::localtime(&endTime));

	(*a_file) << FormatStr(FMT,
						   CAR_ID_LEN, std::to_string(id).c_str(),
						   DIRECTION_LEN, DirectionToString(direction),
						   ARRIVAL_TIME_LEN, arrival.c_str(),
						   START_TIME_LEN, start.c_str(),
						   END_TIME_LEN, end.c_str());
#if _DEBUG
	a_file->flush();
#endif
}


Vehicle::Vehicle() :
	id(0),
	direction(CardinalDirection::kInvalid),
	startTime(),
	arrivalTime(),
	endTime()
{}


Vehicle::~Vehicle()
{}


const char* Vehicle::DirectionToString(CardinalDirection a_direction) const
{
	switch (a_direction) {
	case CardinalDirection::kNorth:
		return "North";
	case CardinalDirection::kEast:
		return "East";
	case CardinalDirection::kSouth:
		return "South";
	case CardinalDirection::kWest:
		return "West";
	default:
		throw std::runtime_error("[ERROR] Encountered unknown cardinal direction (" + std::to_string(static_cast<std::underlying_type<decltype(a_direction)>::type>(a_direction)) + ")");
	}
}


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
