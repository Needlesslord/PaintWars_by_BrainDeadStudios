#include "Slide.h"
#include "TransitionManager.h"

Slide::Slide(SCENES next_scene, float step_duration, bool non_lerp, bool vertical, bool slide_from_right, bool slide_from_bottom, Color slide_colour)
	: Transition(next_scene, step_duration, non_lerp)
	, vertical(vertical)
	, slide_from_right(slide_from_right)
	, slide_from_bottom(slide_from_bottom)
	, slide_colour(slide_colour)
{
	InitSlide();
}

Slide::~Slide()
{

}

void Slide::StepTransition()
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

	TranslateSlide();
}

void Slide::Entering()
{
	current_cutoff += GetCutoffRate(step_duration);

	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MAX_CUTOFF;

		step = TRANSITION_STEP::CHANGING;
	}
}

void Slide::Changing()
{
	App->scenes->SwitchScene(next_scene);

	step = TRANSITION_STEP::EXITING;
}

void Slide::Exiting()
{
	current_cutoff -= GetCutoffRate(step_duration);

	if (current_cutoff <= MIN_CUTOFF)
	{
		current_cutoff = MIN_CUTOFF;
		
		step = TRANSITION_STEP::NONE;

		App->transition_manager->DeleteActiveTransition();
	}
}

void Slide::TranslateSlide()
{
	if (!vertical)
	{
		HorizontalSlide();
	}
	else
	{
		VerticalSlide();
	}

	DrawSlide();
}

void Slide::HorizontalSlide()
{
	if (!slide_from_right)
	{
		if (!non_lerp)
		{
			screen.x = Lerp(-screen.w, 0, current_cutoff);									// Horizontal linearly interpolated slide coming from the left.
		}
		else
		{
			//screen.x = N_Lerp(-screen.w, 0, current_cutoff, true);
			screen.x = N_Lerp(-screen.w, 0, current_cutoff);								// Horizontal non-linearly interpolated slide coming from the left.
		}
	}
	else
	{
		if (!non_lerp)
		{
			screen.x = Lerp(screen.w, 0, current_cutoff);									// Horizontal linearly interpolated slide coming from the right.
		}
		else
		{
			//screen.x = N_Lerp(screen.w, 0, current_cutoff, true);
			screen.x = N_Lerp(screen.w, 0, current_cutoff);									// Horizontal non-linearly interpolated slide coming from the right.
		}
	}
}

void Slide::VerticalSlide()
{
	if (!slide_from_bottom)
	{
		if (!non_lerp)
		{
			screen.y = Lerp(-screen.h, 0, current_cutoff);									// Vertical linearly interpolated slide coming from the top.
		}
		else
		{
			//screen.y = N_Lerp(-screen.h, 0, current_cutoff, true);
			screen.y = N_Lerp(-screen.h, 0, current_cutoff);								// Vertical non-linearly interpolated slide coming from the top.
		}
	}
	else
	{
		if (!non_lerp)
		{
			screen.y = Lerp(screen.h, 0, current_cutoff);									// Vertical linearly interpolated slide coming from the bottom.
		}
		else
		{
			//screen.y = N_Lerp(screen.h, 0, current_cutoff, true);
			screen.y = N_Lerp(screen.h, 0, current_cutoff);									// Vertical non-linearly interpolated slide coming from the bottom.
		}
	}
}

void Slide::DrawSlide()
{
	SDL_SetRenderDrawColor(App->render->renderer, slide_colour.r, slide_colour.g, slide_colour.b, 255);
	SDL_RenderFillRect(App->render->renderer, &screen);
}

void Slide::InitSlide()
{
	App->win->GetWindowRect(screen);

	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	step = TRANSITION_STEP::ENTERING;
}