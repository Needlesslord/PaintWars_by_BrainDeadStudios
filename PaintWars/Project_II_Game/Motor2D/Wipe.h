#ifndef __WIPE_H__
#define __WIPE_H__

#include "Transition.h"
#include "Color.h"

class Wipe : public Transition
{
public:
	Wipe(SCENES next_scene, float step_duration, bool non_lerp, bool vertical, bool wipe_from_right, bool wipe_from_bottom, Color wipe_colour);
	~Wipe();

	void StepTransition();

public:
	void Entering();
	void Changing();
	void Exiting();

	void TranslateWipe();
	void HorizontalWipe();											// Will horizontally interpolate a wipe from left to right or right to left.
	void VerticalWipe();											// Will vertically interpolate a wipe from the top to bottom or bottom to top.
	void DrawWipe();

	void InitWipe();

private:
	SDL_Rect	screen;
	Color		wipe_colour;

	bool		vertical;											// Will determine whether or not the wipe transition will be vertical.
	bool		wipe_from_right;									// Will determine whether or not the wipe transition will come from the right.
	bool		wipe_from_bottom;									// Will determine whether or not the wipe transition will come from the bototm.
};

#endif // !__WIPE_H__