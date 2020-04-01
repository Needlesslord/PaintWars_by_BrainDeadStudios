#include "TransitionManager.h"
#include "CameraToMouse.h"
#include "Cut.h"
#include "FadeToColour.h"
#include "Slide.h"
#include "Wipe.h"
#include "AlternatingBars.h"
#include "ExpandingBars.h"
#include "ZoomToMouse.h"
#include "ZoomToTexture.h"
#include "Dissolve.h"

TransitionManager::TransitionManager() : active_transition(nullptr), is_transitioning(false)
{

}

TransitionManager::~TransitionManager()
{

}

bool TransitionManager::PostUpdate()
{
	bool ret = true;

	if (active_transition != nullptr)
	{
		active_transition->StepTransition();
	}

	return ret;
}

bool TransitionManager::CleanUp()
{
	bool ret = true;
	
	if (active_transition != nullptr)
	{
		delete active_transition;
		active_transition = nullptr;
	}

	return ret;
}

void TransitionManager::DeleteActiveTransition()
{
	is_transitioning = false;

	delete active_transition;

	active_transition = nullptr;
}

Transition* TransitionManager::CreateCut(SCENES next_scene)
{
	if (!is_transitioning)
	{
		active_transition = new Cut(next_scene);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateFadeToColour(SCENES next_scene, float step_duration, Color fade_colour)
{	
	if (!is_transitioning)
	{
		active_transition = new FadeToColour(next_scene, step_duration, fade_colour);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateSlide(SCENES next_scene, float step_duration, bool non_lerp, bool vertical, bool slide_from_right, bool slide_from_bottom, Color slide_colour)
{
	if (!is_transitioning)
	{
		active_transition = new Slide(next_scene, step_duration, non_lerp, vertical, slide_from_right, slide_from_bottom, slide_colour);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateWipe(SCENES next_scene, float step_duration, bool non_lerp, bool vertical, bool wipe_from_right, bool wipe_from_bottom, Color fade_colour)
{
	if (!is_transitioning)
	{
		active_transition = new Wipe(next_scene, step_duration, non_lerp, vertical, wipe_from_right, wipe_from_bottom, fade_colour);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateAlternatingBars(SCENES next_scene, float step_duration, bool non_lerp, int bar_number, bool vertical, bool random_colours, Color even_colour, Color odd_colour)
{
	if (!is_transitioning)
	{
		active_transition = new AlternatingBars(next_scene, step_duration, non_lerp, bar_number, vertical, random_colours, even_colour, odd_colour);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateExpandingBars(SCENES next_scene, float step_duration, bool non_lerp, int bar_number, bool vertical, bool random_colours, Color even_colour, Color odd_colour)
{
	if (!is_transitioning)
	{
		active_transition = new ExpandingBars(next_scene, step_duration, non_lerp, bar_number, vertical, random_colours, even_colour, odd_colour);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateZoomToMouse(SCENES next_scene, iPoint mouse_position, float step_duration, bool non_lerp, float zoom_scale)
{
	if (!is_transitioning)
	{
		active_transition = new ZoomToMouse(next_scene, mouse_position, step_duration, non_lerp, zoom_scale);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateCameraToMouse(iPoint mouse_position, float step_duration, bool non_lerp)
{
	if (!is_transitioning)
	{
		active_transition = new CameraToMouse(mouse_position, step_duration, non_lerp);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateZoomToTexture(SCENES next_scene, iPoint mouse_position, float step_duration, float zoom_scale)
{
	if (!is_transitioning)
	{
		active_transition = new ZoomToTexture(next_scene, mouse_position, step_duration, zoom_scale);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateDissolve(SCENES next_scene, float step_duration)
{
	if (!is_transitioning)
	{
		active_transition = new Dissolve(next_scene, step_duration);

		is_transitioning = true;
	}

	return active_transition;
}