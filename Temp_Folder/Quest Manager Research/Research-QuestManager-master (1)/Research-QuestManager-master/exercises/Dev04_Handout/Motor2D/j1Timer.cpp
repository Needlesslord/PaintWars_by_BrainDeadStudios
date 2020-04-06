// ----------------------------------------------------
// j1Timer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "j1Timer.h"
#include "SDL\include\SDL_timer.h"

// ---------------------------------------------
j1Timer::j1Timer()
{
	Start();
}

// ---------------------------------------------
void j1Timer::Start()									//As we need to be faster rather than precise with this one we will use SDL_GetTicks() instead of SDL_GetPerformanceCounter. 
{
	started_at = SDL_GetTicks();						//Records the amount of ticks (in milliseconds) whenever the function is called. Used to set the start of the timer.
}

// ---------------------------------------------
uint32 j1Timer::Read() const
{
	return SDL_GetTicks() - started_at;					//Returns the amount of time (in milliseconds) that has passed since Start() function call.
}

// ---------------------------------------------
float j1Timer::ReadSec() const
{
	return (SDL_GetTicks() - started_at) / 1000.0f;		//Returns the amount of time that has passed from Start method call until this method's call. As data is received in ms, it is converted to seconds.
}