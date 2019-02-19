#pragma once

#include <cstdlib>  // size_t
#include <ctime>  // time_t
#include <string>  // string


constexpr std::size_t COLUMN_WIDTH = 10;	// Minimum column width for log columns


void SleepFor(std::size_t a_seconds);	// Puts the calling thread to sleep for the specified duration
std::time_t GetTime();	// Returns the current system time
std::string TimeToString(const std::tm* a_time);	// Converts the time struct to a string
std::string FormatStr(const char* a_fmt, ...);	// Formats the given args using the specified format
