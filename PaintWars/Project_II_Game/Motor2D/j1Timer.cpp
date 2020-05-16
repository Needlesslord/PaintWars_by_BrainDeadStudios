// ----------------------------------------------------
// j1Timer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "j1Timer.h"
#include "SDL\include\SDL_timer.h"
#include "p2Defs.h"

j1Timer::j1Timer()
{
	Start();
}

// ---------------------------------------------
void j1Timer::Start()
{
	running = true;
	started_at = SDL_GetTicks();
}

// ---------------------------------------------
void j1Timer::Stop()
{
	running = false;
	stopped_at = SDL_GetTicks();
}

void j1Timer::Resume()
{
	running = true;
	started_at = stopped_at;
}

// ---------------------------------------------
uint j1Timer::Read() const
{
	if (running == true)
	{
		return SDL_GetTicks() - started_at;
	}
	else
	{
		return stopped_at - started_at;
	}
}

float j1Timer::ReadSec() const
{
	return float(SDL_GetTicks() - started_at) / 1000.0f;
}
