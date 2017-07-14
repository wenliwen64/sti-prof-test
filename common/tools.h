#ifndef common_tools_h
#define common_tools_h

#include <cstdlib>
#include <cstdio>
#include <time.h>


#define TO_STRING(x) #x

#ifndef NDEBUG
#define DEBUG_CODE(x) do { x } while (0)
#define NDEBUG_STR TO_STRING(yes)
#else
#define DEBUG_CODE(x)
#define NDEBUG_STR TO_STRING(no)
#endif


namespace tools {


    void print(timespec ts)
    {
	std::printf("%lld.%.9ld\n", (long long) ts.tv_sec, ts.tv_nsec);
    }


    timespec time_diff(timespec time_start, timespec time_end)
    {
	timespec temp;

	if ((time_end.tv_nsec - time_start.tv_nsec) < 0)
	{
	    temp.tv_sec = time_end.tv_sec - time_start.tv_sec - 1;
	    temp.tv_nsec = 1000000000 + time_end.tv_nsec - time_start.tv_nsec;
	}
	else
	{
	    temp.tv_sec = time_end.tv_sec - time_start.tv_sec;
	    temp.tv_nsec = time_end.tv_nsec - time_start.tv_nsec;
	}

	return temp;
    }


    void time_add(timespec& time_cumul, timespec time_add)
    {
	if (time_cumul.tv_nsec + time_add.tv_nsec > 999999999)
	{
	    time_cumul.tv_sec  += time_add.tv_sec + 1;
	    time_cumul.tv_nsec += time_add.tv_nsec - 1000000000;
	}
	else
	{
	    time_cumul.tv_sec  += time_add.tv_sec;
	    time_cumul.tv_nsec += time_add.tv_nsec;
	}
    }


    double my_rand(const double min, const double max)
    {
	return ( std::rand()/(static_cast<double>(RAND_MAX)+1) ) * (max-min) + min;
    }


}

#endif
