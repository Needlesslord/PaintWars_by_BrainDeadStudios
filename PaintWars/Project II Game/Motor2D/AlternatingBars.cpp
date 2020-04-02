#include "AlternatingBars.h"
#include "TransitionManager.h"
#include "Color.h"


AlternatingBars::AlternatingBars(SCENES next_scene, float step_duration, bool non_lerp, int bar_number, bool vertical, bool random_colours, Color even_colour, Color odd_colour) 
	: Transition(next_scene, step_duration, non_lerp)
	, bar_number(bar_number)
	, win_width(0.0f)
	, win_height(0.0f)
	, vertical(vertical)
	, random_colours(random_colours)
	, even_colour(even_colour)
	, odd_colour(odd_colour)
{	
	InitAlternatingBars();
}

AlternatingBars::~AlternatingBars()
{

}

void AlternatingBars::StepTransition()
{
	current_cutoff += GetCutoffRate(step_duration);

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

	AlternateBars();
}

void AlternatingBars::Entering()
{
	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MIN_CUTOFF;
		
		step = TRANSITION_STEP::CHANGING;
	}
}

void AlternatingBars::Changing()
{
	App->scenes->SwitchScene(next_scene);
	
	step = TRANSITION_STEP::EXITING;
}

void AlternatingBars::Exiting()
{	
	if (current_cutoff >= MAX_CUTOFF)
	{
		step = TRANSITION_STEP::NONE;

		bars.clear();
		
		App->transition_manager->DeleteActiveTransition();
	}
}

void AlternatingBars::AlternateBars()
{
	if (!vertical)
	{
		TranslateHorizontalBars();
	}
	else
	{
		TranslateVerticalBars();
	}

	DrawBars();
}

void AlternatingBars::TranslateHorizontalBars()
{
	if (step == TRANSITION_STEP::ENTERING)
	{
		if (!non_lerp)
		{
			for (int i = 0; i < bars.size(); ++i)
			{
				if (i % 2 == 0)
				{
					bars[i].bar.x = Lerp(-win_width, 0, current_cutoff);
				}
				else
				{
					bars[i].bar.x = Lerp(win_width, 0, current_cutoff);
				}
			}
		}
		else
		{
			for (int i = 0; i < bars.size(); ++i)
			{
				if (i % 2 == 0)
				{
					//bars[i].bar.x = N_Lerp(-win_width, 0, current_cutoff, true);
					bars[i].bar.x = N_Lerp(-win_height, 0, current_cutoff);
				}
				else
				{
					//bars[i].bar.x = N_Lerp(win_width, 0, current_cutoff, true);
					bars[i].bar.x = N_Lerp(win_width, 0, current_cutoff);
				}
			}
		}
	}

	if (step == TRANSITION_STEP::EXITING)
	{
		if (!non_lerp)
		{
			for (int i = 0; i < bars.size(); ++i)
			{
				if (i % 2 == 0)
				{
					bars[i].bar.x = Lerp(0, win_width, current_cutoff);
				}
				else
				{
					bars[i].bar.x = Lerp(0, -win_width, current_cutoff);
				}
			}
		}
		else
		{
			for (int i = 0; i < bars.size(); ++i)
			{
				if (i % 2 == 0)
				{
					//bars[i].bar.x = N_Lerp(0, win_width, current_cutoff, true);
					bars[i].bar.x = N_Lerp(0, win_width, current_cutoff);
				}
				else
				{
					//bars[i].bar.x = N_Lerp(0, -win_width, current_cutoff, true);
					bars[i].bar.x = N_Lerp(0, -win_width, current_cutoff);
				}
			}
		}
	}
}

void AlternatingBars::TranslateVerticalBars()
{	
	if (step == TRANSITION_STEP::ENTERING)
	{
		if (!non_lerp)
		{
			for (int i = 0; i < bars.size(); ++i)
			{
				if (i % 2 == 0)
				{
					bars[i].bar.y = Lerp(-win_height, 0, current_cutoff);
				}
				else
				{
					bars[i].bar.y = Lerp(win_height, 0, current_cutoff);
				}
			}
		}
		else
		{
			for (int i = 0; i < bars.size(); ++i)
			{
				if (i % 2 == 0)
				{
					//bars[i].bar.y = N_Lerp(-win_height, 0, current_cutoff, true);
					bars[i].bar.y = N_Lerp(-win_height, 0, current_cutoff);
				}
				else
				{
					//bars[i].bar.y = N_Lerp(win_height, 0, current_cutoff, true);
					bars[i].bar.y = N_Lerp(win_height, 0, current_cutoff);
				}
			}
		}
	}

	if (step == TRANSITION_STEP::EXITING)
	{
		if (!non_lerp)
		{
			for (int i = 0; i < bars.size(); ++i)
			{
				if (i % 2 == 0)
				{
					bars[i].bar.y = Lerp(0, win_height, current_cutoff);
				}
				else
				{
					bars[i].bar.y = Lerp(0, -win_height, current_cutoff);
				}
			}
		}
		else
		{
			for (int i = 0; i < bars.size(); ++i)
			{
				if (i % 2 == 0)
				{
					//bars[i].bar.y = N_Lerp(0, win_height, current_cutoff, true);
					bars[i].bar.y = N_Lerp(0, win_height, current_cutoff);
				}
				else
				{
					//bars[i].bar.y = N_Lerp(0, -win_height, current_cutoff, true);
					bars[i].bar.y = N_Lerp(0, -win_height, current_cutoff);
				}
			}
		}
	}
}

void AlternatingBars::DrawBars()
{
	for (int i = 0; i < bars.size(); ++i)
	{
		SDL_SetRenderDrawColor(App->render->renderer, bars[i].colour.r, bars[i].colour.g, bars[i].colour.b, 255);
		SDL_RenderFillRect(App->render->renderer, &bars[i].bar);
	}
}

void AlternatingBars::InitAlternatingBars()
{	
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	
	App->win->GetWindowSize(win_width, win_height);

	for (int i = 0; i < bar_number; ++i)
	{
		Bar new_bar;

		if (!vertical)
		{
			AssignHorizontalBar(new_bar, win_width, win_height, i);
		}
		else
		{
			AssignVerticalBar(new_bar, win_width, win_height, i);
		}
		
		AssignBarColour(new_bar, i);

		bars.push_back(new_bar);
	}

	step = TRANSITION_STEP::ENTERING;
}

void AlternatingBars::AssignHorizontalBar(Bar& new_bar, const int& win_width, const int& win_height, const int& index)
{
	int bar_width = win_width;
	
	float bar_num		= bar_number;																// As bar_number is an integer, when win_height is divided by it
 	float height_ratio	= win_height / bar_num;														// the decimals are cut off. By creating 2 float buffers and using
	int bar_height		= ceil(height_ratio);														// the ceil() function, an approximation is made to the real number.
	
	if (index % 2 == 0)
	{
		new_bar.bar = { -win_width, bar_height * index, bar_width, bar_height };
	}
	else
	{
		new_bar.bar = { win_width, bar_height * index, bar_width, bar_height };
	}
}

void AlternatingBars::AssignVerticalBar(Bar& new_bar, const int& win_width, const int& win_height, const int& index)
{
	int bar_height = win_height;

	float bar_num = bar_number;																		// As bar_number is an integer, when win_width is divided by it
	float width_ratio = win_width / bar_num;														// the decimals are cut off. By creating 2 float buffers and using
	int bar_width = ceil(width_ratio);																// the ceil() function, an approximation is made to the real number.

	if (index % 2 == 0)
	{
		new_bar.bar = { bar_width * index, -win_height, bar_width, bar_height };
	}
	else
	{
		new_bar.bar = { bar_width * index, win_height, bar_width, bar_height };
	}
}

void AlternatingBars::AssignBarColour(Bar& new_bar, const int& index)
{
	if (random_colours)
	{
		new_bar.colour = GetRandomColour();
		
	}
	else
	{
		if (index % 2 == 0)
		{
			new_bar.colour = even_colour;
		}
		else
		{
			new_bar.colour = odd_colour;
		}
	}
}