#include "Transition.h"

Transition::Transition(SCENES next_scene, float step_duration, bool non_lerp ) : 
	next_scene(next_scene), 
	step_duration(step_duration), 
	non_lerp(non_lerp),
	cutoff_rate(0.0f),
	current_cutoff(0.0f)
{

}

Transition::~Transition()
{

}

void Transition::Start()
{

}

void Transition::StepTransition()
{

}

void Transition::CleanUp()
{

}

void Transition::Entering()
{
	
}

void Transition::Changing()
{

}

void Transition::Exiting()
{

}

float Transition::Lerp(float start, float end, float rate)								// Rate goes from 0.0f (0 %) to 1.0f (100 %) advancement per frame.
{																						// If Lerp(0.0f, 10.0f, 1.0f), then the advancement per frame will be of 10.0f.
	float increment = (end - start) * rate;												// Rate can also increase over time. (See GetCutoffRate() and Wipe.cpp line #81).

	return start + increment;
}

float Transition::N_Lerp(float start, float end, float rate, bool smash_in)				//Rate goes from 0 to rate*rate || (1 - rate) * (1 - rate)
{																						//Simillar to Lerp() but allows for ease-ins.
	float increment = 0;

	if (smash_in)																		
	{
		increment = (end - start) * rate * rate;										// Ease-Out Smash-In --> Slow out, Fast In
	}
	else
	{
		//float r = (1 - rate);															// Smash-Out Ease-In --> Fast out, Slow In. Simplified version.
		//increment = (end - start) * r * r;											// This one requires to receive the start-end values inverted.
		
		float r = 1 - ((1 - rate) * (1 - rate));										// Smash-Out Ease-In --> Fast out, Slow In. Full version.
		increment = (end - start) * r;													// This one accepts the parameters in the same order as Lerp.
	}																						

	return start + increment;
}

float Transition::GetCutoffRate(float step_duration, float dt)
{
	cutoff_rate = dt / step_duration;

	return cutoff_rate;
}