#include "ZoomToMouse.h"
#include "TransitionManager.h"
#include "j1Map.h"

ZoomToMouse::ZoomToMouse(SCENES next_scene, iPoint mouse_position, float step_duration, bool non_lerp, float zoom_scale) : Transition(next_scene, step_duration, non_lerp)
, zoom_scale(zoom_scale)
, mouse_position(mouse_position)
{
	InitZoomToMouse(mouse_position);
}

ZoomToMouse::~ZoomToMouse()
{

}

void ZoomToMouse::StepTransition()
{
	switch (step)
	{
	case TRANSITION_STEP::ENTERING:

		Entering();

		break;

	case TRANSITION_STEP::CHANGING:

		Changing();

		break;

	case TRANSITION_STEP::EXITING:

		Exiting();

		break;
	}

	ApplyZoom();
}

void ZoomToMouse::Entering()
{
	current_cutoff += GetCutoffRate(step_duration);

	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MAX_CUTOFF;

		step = TRANSITION_STEP::CHANGING;
	}
}

void ZoomToMouse::Changing()
{
	App->scenes->SwitchScene(next_scene);
	
	step = TRANSITION_STEP::EXITING;
}

void ZoomToMouse::Exiting()
{
	current_cutoff -= GetCutoffRate(step_duration);

	if (current_cutoff <= MIN_CUTOFF)
	{
		step = TRANSITION_STEP::NONE;

		App->transition_manager->DeleteActiveTransition();
	}
}

void ZoomToMouse::ApplyZoom()
{
	zoom_rate = GetZoomRate();																				// If current_cutoff == 0.0f, then scale == original_scale.

	if (!non_lerp)
	{
		App->render->camera.x = Lerp(original_position.x, target_position.x, current_cutoff);				// Zoom rate goes from 1 to 2 to 1, so there is no need to
		App->render->camera.y = Lerp(original_position.y, target_position.y, current_cutoff);				// separate the zoom in different steps.
	}
	else
	{
		//App->render->camera.x = N_Lerp(original_position.x, target_position.x, current_cutoff, true);
		//App->render->camera.y = N_Lerp(original_position.y, target_position.y, current_cutoff, true);

		App->render->camera.x = N_Lerp(original_position.x, target_position.x, current_cutoff);
		App->render->camera.y = N_Lerp(original_position.y, target_position.y, current_cutoff);
	}

	SDL_RenderSetScale(App->render->renderer, zoom_rate, zoom_rate);
}

float ZoomToMouse::GetZoomRate() const
{
	float rate = original_scale + zoom_scale * current_cutoff;

	if (rate > original_scale + zoom_scale)
	{
		rate = original_scale + zoom_scale;
	}

	if (rate < original_scale)
	{
		rate = original_scale;
	}

	return rate;
}

void ZoomToMouse::InitZoomToMouse(iPoint mouse_position)
{
	original_scale = App->win->GetScale();

	original_position.x = App->render->camera.x;
	original_position.y = App->render->camera.y;
	
	target_position.x = (-mouse_position.x) + App->render->camera.w * 0.25f;					// Adjusting the final position of the camera taking into account the mouse position.
	target_position.y = (-mouse_position.y) + App->render->camera.h * 0.25f;					// Adjusting the final position of the camera taking into account the mouse position.

	step = TRANSITION_STEP::ENTERING;
}