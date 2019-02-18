#include "TrafficDirector.h"

#include <cassert>  // assert
#include <stdexcept>  // runtime_error
#include <string>  // to_string
#include <type_traits>  // underlying_type

#include "Bottleneck.h"  // Bottleneck
#include "Util.h"  // SleepFor, TimeToString, FormatStr
#include "Vehicle.h"  // Vehicle


static constexpr char FMT[] = MAKE_STR(TRAFFIC_DIRECTOR_FMT);
static constexpr char TIME[] = "Time";
static constexpr char STATE[] = "State";
static constexpr char CAR_LOG[] = "car.log";
static constexpr char FLAG_LOG[] = "flagperson.log";
static constexpr std::size_t TIME_LEN = sizeof(TIME) - 1 > COLUMN_WIDTH ? sizeof(TIME) - 1 : COLUMN_WIDTH;
static constexpr std::size_t STATE_LEN = sizeof(STATE) - 1 > COLUMN_WIDTH ? sizeof(STATE) - 1 : COLUMN_WIDTH;


void TrafficDirector::Run()
{
	Bottleneck* bottleneck = Bottleneck::GetSingleton();
	Bottleneck::Locker locker(bottleneck);
	if (bottleneck->HasQueuedVehicles()) {
		_mode = bottleneck->GetNorthVehicleCount() > bottleneck->GetSouthVehicleCount() ? Mode::kNorth : Mode::kSouth;
		Vehicle* car = 0;
		do {
			switch (_mode) {
			case Mode::kNorth:
				{
					car = bottleneck->PopNorthVehicle();
					car->TimeStampStart();
					SleepFor(1);
					car->TimeStampEnd();
					if (bottleneck->GetNorthVehicleCount() == 0 || bottleneck->GetSouthVehicleCount() >= 10) {
						_mode = Mode::kSouth;
					}
				}
				break;
			case Mode::kSouth:
				{
					car = bottleneck->PopSouthVehicle();
					car->TimeStampStart();
					SleepFor(1);
					car->TimeStampEnd();
					if (bottleneck->GetSouthVehicleCount() == 0 || bottleneck->GetNorthVehicleCount() >= 10) {
						_mode = Mode::kNorth;
					}
				}
				break;
			default:
				throw std::runtime_error("[ERROR] Encountered unknown mode (" + std::to_string(static_cast<std::underlying_type<decltype(_mode)>::type>(_mode)) + ")");
			}
			car->Dump(&_carFile);
		} while (bottleneck->HasQueuedVehicles());
	}
}


void TrafficDirector::PrintHeader()
{
	_flagFile << FormatStr(FMT,
						   TIME_LEN, TIME,
						   STATE_LEN, STATE);
#if _DEBUG
	_flagFile.flush();
#endif
}


void TrafficDirector::TimeStamp(bool a_awake)
{
	std::time_t time = GetTime();
	std::string timeStr = TimeToString(std::localtime(&time));

	_flagFile << FormatStr(FMT,
						   TIME_LEN, timeStr.c_str(),
						   STATE_LEN, (a_awake ? "Awake" : "Asleep"));
#if _DEBUG
	_flagFile.flush();
#endif
}


std::ofstream* TrafficDirector::GetCarLog()
{
	return &_carFile;
}


TrafficDirector::TrafficDirector() :
	_mode(Mode::kInvalid),
	_carFile(CAR_LOG),
	_flagFile(FLAG_LOG)
{
	assert(_carFile.is_open());
	assert(_flagFile.is_open());
}


TrafficDirector::~TrafficDirector()
{}
