#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#define MAX_CUTOFF 1.0f
#define MIN_CUTOFF 0.0f

#include "SDL/include/SDL.h"
#include "j1App.h"
#include "Color.h"
#include "j1SceneManager.h"
#include "j1Window.h"
#include "j1Render.h"


enum class TRANSITION_STEP
{
	NONE,
	ENTERING,
	CHANGING,
	EXITING
};

class Transition
{
public:
	Transition(SCENES next_scene, float step_duration, bool non_lerp = false);
	virtual ~Transition();

	virtual void Start();
	virtual void StepTransition();
	virtual void CleanUp();

public:
	virtual void Entering();														// Method that will be used to execute the ENTERING transition step.
	virtual void Changing();														// Method that will be used to execute the CHANGING transition step.
	virtual void Exiting();															// Method that will be used to execute the EXITING transition step.
	
	float Lerp(float start, float end, float rate);									// Method that will be used to linearly interpolate the speed of a given transition.
	float N_Lerp(float start, float end, float rate, bool smash_in = false);		// Method that will be used to non-linearly interpolate the speed of a given transition.
	float GetCutoffRate(float step_duration, float dt = 0.016);				// Method that returns the cutoff rate for a given transition. Will use dt as the standard increase.

public:
	TRANSITION_STEP step;															// All the steps that a given transition will go through.
	SCENES			next_scene;														// The scene that will be transitioned to.

	float			step_duration;													// The duration of each transtion step in seconds.
	float			current_cutoff;													// The amount of time that has elapsed since the start of the transition step.

	bool			non_lerp;														// Bool that defines whether or not a transition is linearly or non-linearly interpolated.

private:
	float			cutoff_rate;													// The rate at which the transition will elapse.
																					// Ranges from 0.0f to 1.0f  0.0 == step_start & 1.0f == step_end.
};

#endif // !__TRANSITION_H__