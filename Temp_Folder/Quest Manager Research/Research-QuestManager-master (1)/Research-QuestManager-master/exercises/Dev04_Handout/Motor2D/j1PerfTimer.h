#ifndef __j1PERFTIMER_H__
#define __j1PERFTIMER_H__

#include "p2Defs.h"

class j1PerfTimer
{
public:

	// Constructor
	j1PerfTimer();

	void Start();
	double ReadMs() const;
	uint64 ReadTicks() const;

private:
	uint64			started_at;
	static uint64	frequency;	//As frequency will be the same across all timers, we declare it as static. That way, when frequency is initialized, the variable will carry its values through function calls instead of being reset to 0.
};

#endif //__j1PERFTIMER_H__
