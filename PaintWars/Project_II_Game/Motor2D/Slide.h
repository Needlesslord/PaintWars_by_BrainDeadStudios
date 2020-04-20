#ifndef __SLIDE_H__
#define __SLIDE_H__

#include "Transition.h"
#include "Color.h"

class Slide : public Transition
{
public:
	Slide(SCENES next_scene, float step_duration, bool non_lerp, bool vertical, bool slide_from_right, bool slide_from_bottom, Color slide_colour);
	~Slide();

	void StepTransition();

public:
	void Entering();
	void Changing();
	void Exiting();

	void TranslateSlide();
	void HorizontalSlide();											// Will horizontally interpolate a slide from left to right or right to left.
	void VerticalSlide();											// Will vertically interpolate a slide from the top to bottom or bottom to top.
	void DrawSlide();

	void InitSlide();

private:
	SDL_Rect	screen;
	Color		slide_colour;

	bool		vertical;											// Will determine whether or not the slide transition will be vertical or not.
	bool		slide_from_right;									// Will determine whether or not the slide transition will come from the right or not.
	bool		slide_from_bottom;									// Will determine whether or not the slide transition will come from the bototm or not.
};

#endif // !__SLIDE_H__