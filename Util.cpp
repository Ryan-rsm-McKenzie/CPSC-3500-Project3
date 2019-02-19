#include "Util.h"

#include <chrono>  // chrono
#include <cstdarg>  // va_list
#include <cstdio>  // snprintf
#include <cstdlib>  // size_t
#include <iomanip>  // put_time
#include <string>  // string
#include <vector>  // vector

#include <thread>  // this_thread
#if _WIN32
#include <thread>  // this_thread
#else
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif


void SleepFor(std::size_t a_seconds)
{
#if true
	std::this_thread::sleep_for(std::chrono::seconds(a_seconds));
#else
	pthread_mutex_t mutex;
	pthread_cond_t conditionvar;
	struct timespec timetoexpire;
	if (pthread_mutex_init(&mutex, NULL)) {
		return;
	}
	if (pthread_cond_init(&conditionvar, NULL)) {
		return;
	}
	//When to expire is an absolute time, so get the current time and add
	 //it to our delay time
	timetoexpire.tv_sec = (unsigned int)time(NULL) + a_seconds;
	timetoexpire.tv_nsec = 0;
	pthread_cond_timedwait(&conditionvar, &mutex, &timetoexpire);
#endif
}


std::time_t GetTime()
{
	return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}


std::string TimeToString(const std::tm* a_time)
{
	static char buf[9];
	std::snprintf(buf, sizeof(buf), "%02i:%02i:%02i", a_time->tm_hour, a_time->tm_min, a_time->tm_sec);
	return buf;
}


std::string FormatStr(const char* a_fmt, ...)
{
	std::va_list args1;
	va_start(args1, a_fmt);
	std::va_list args2;
	va_copy(args2, args1);
	std::vector<char> buf(std::vsnprintf(0, 0, a_fmt, args1) + 1);
	va_end(args1);
	std::vsnprintf(buf.data(), buf.size(), a_fmt, args2);
	va_end(args2);
	std::string str = buf.data();
	return str;
}
