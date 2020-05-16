#ifndef __DISSOLVE_H__
#define __DISSOLVE_H__

#define MAX_ALPHA 255.0f
#define MIN_ALPHA 0.0f

#include "Transition.h"

class Dissolve : public Transition
{
public:
	Dissolve(SCENES next_scene, float step_duration);
	~Dissolve();

	void StepTransition();

public:
	void Entering();
	void Changing();
	void Exiting();

	void ApplyDissolve();

	void InitDissolve();

private:
	float dissolve_rate;							// Pace at which the textures will dissolve / undissolve.

	float dissolving_alpha;							// Alpha for the texture that will dissolve.
	float condensing_alpha;							// Alpha for the texture that will condense.
};

#endif // !__DISSOLVE_H__