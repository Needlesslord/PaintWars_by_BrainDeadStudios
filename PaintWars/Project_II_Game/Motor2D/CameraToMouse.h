#ifndef __CAMERA_TO_MOUSE
#define __CAMERA_TO_MOUSE

#define MAX_TIME 1.0f

#include "Transition.h"

class CameraToMouse : public Transition
{
public:
	CameraToMouse(iPoint mouse_position, float step_duration, bool non_lerp);
	~CameraToMouse();

	void StepTransition();

public:
	void Entering();
	void Exiting();

	void TranslateCamera();

	void InitCameraToMouse(iPoint mouse_position);

private:
	iPoint	origin;																// Original position of the camera at the start of the transition.
	iPoint	mouse_position;														// Position of the mouse at the start of the transition. Will be the target position of the transition.

	fPoint	next_pos;															// Will store the values returned by the interpolation methods before they are assigned to the camera position.
};

#endif // !__CAMERA_TO_MOUSE

