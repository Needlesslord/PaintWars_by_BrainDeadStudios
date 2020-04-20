#include "ZoomToTexture.h"
#include "TransitionManager.h"
#include "j1Map.h"

ZoomToTexture::ZoomToTexture(SCENES next_scene, iPoint mouse_position, float step_duration, float zoom_scale) : Transition(next_scene, step_duration)
, zoom_scale(zoom_scale)
, mouse_position(mouse_position)
{
	InitZoomToTexture(mouse_position);
}

ZoomToTexture::~ZoomToTexture()
{

}

void ZoomToTexture::StepTransition()
{
	//current_cutoff += GetCutoffRate(step_duration);
	
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

void ZoomToTexture::Entering()
{
	current_cutoff += GetCutoffRate(step_duration);
	
	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MAX_CUTOFF;

		step = TRANSITION_STEP::CHANGING;
	}
}

void ZoomToTexture::Changing()
{
	App->scenes->SwitchScene(next_scene);

	target_to_zoom = App->scenes->current_scene->scene_texture;

	step = TRANSITION_STEP::EXITING;
}

void ZoomToTexture::Exiting()
{
	current_cutoff -= GetCutoffRate(step_duration);
	
	if (current_cutoff <= MIN_CUTOFF)
	{	
		step = TRANSITION_STEP::NONE;

		App->transition_manager->DeleteActiveTransition();
	}
}

void ZoomToTexture::ApplyZoom()
{
	zoom_rate = original_scale + current_cutoff * zoom_scale;															// If current_cutoff == 0.0f, then scale == original_scale.

	//App->render->AddBlitEvent(target_to_zoom, x_increase_rate, y_increase_rate, NULL, true, App->render->renderer, zoom_rate);
}

void ZoomToTexture::InitZoomToTexture(iPoint mouse_position)
{
	int x_offset;
	int y_offset;
	
	App->map->GetTileOffset(x_offset, y_offset);
	
	original_scale			= App->win->GetScale();																				// The minimum amount of zoom that there will be.	
	
	target_to_zoom			= App->scenes->current_scene->scene_texture;													// The texture to which scale will be incremented.
	
	float total_zoom		= original_scale + zoom_scale;																		// The maximum amount of zoom that there will be.
	
	float half_map_width = 1;//App->scenes>current_scene->map_width * 0.5f;												// Will be used to keep up with the zoom's rate of increase.
	float half_map_height = 1;//App->scenes->current_scene->map_height * 0.5f;										
	
	float x_increment		= Lerp(half_map_width, half_map_width * zoom_scale, zoom_rate);
	float y_increment		= Lerp(half_map_height, half_map_height * zoom_scale, zoom_rate);

	x_increase_rate			= -mouse_position.x - x_increment + x_offset;
	y_increase_rate			= -mouse_position.y + y_increment - y_offset;
	
	
	step = TRANSITION_STEP::ENTERING;
}