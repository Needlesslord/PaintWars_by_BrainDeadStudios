#ifndef __ZOOM_TO_MOUSE_H__
#define __ZOOM_TO_MOUSE_H__

#include  "Transition.h"

class ZoomToMouse : public Transition
{
public:
	ZoomToMouse(SCENES next_scene, iPoint mouse_position, float step_duration, bool non_lerp, float zoom_scale);
	~ZoomToMouse();

	void StepTransition();

public:
	void Entering();
	void Changing();
	void Exiting();

	void ApplyZoom();
	float GetZoomRate() const;								// Will calculate the zoom rate. Will also check that the float does not get out of bounds.

	void InitZoomToMouse(iPoint mouse_position);

private:
	iPoint mouse_position;
	iPoint original_position;
	iPoint target_position;

	float original_scale;									// Represents the scale previous to being incerased by the zoom.
	float zoom_scale;										// Represents the increase percentage of the scale. zoom_scale = 1.0f --> 100% scale increase.
	float zoom_rate;										// Representes the pace at which the zoom will be increased.
};

#endif // !__ZOOM_TO_MOUSE_H__
