#pragma once

#include <cstdlib>  // size_t
#include <ctime>  // time_t
#include <string>  // string


#define MAKE_STR_HELPER(a_str) #a_str
#define MAKE_STR(a_str) MAKE_STR_HELPER(a_str)

#if _WIN32
#define ENDL \r\n
#else
#define ENDL \n
#endif


constexpr std::size_t COLUMN_WIDTH = 10;


void SleepFor(std::size_t a_seconds);
std::time_t GetTime();
std::string TimeToString(const std::tm* a_time);
std::string FormatStr(const char* a_fmt, ...);
