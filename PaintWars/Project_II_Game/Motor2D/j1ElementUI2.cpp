#include "j1ElementUI.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1FontsUI.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Window.h"
#include "j1Audio.h"
#include "j1GUIv2.h"



#include "Brofiler/Brofiler.h"

bool UI_Item::PreUpdate(float dt)
{
	BROFILER_CATEGORY("UI Element PreUpdate();", Profiler::Color::Azure)
	switch (state)
	{
	case UI_State::IDLE:
		if (OnHover())
		{
			state = UI_State::HOVER;
		}
		break;

	case UI_State::HOVER:
		if (!OnHover())
		{
			state = UI_State::IDLE;
		}
		if (OnClick())
		{
			state = UI_State::CLICK;
		}
		break;

	case UI_State::CLICK:
		if (!OnClick())
		{
			state = UI_State::HOVER;
		}
		break;

	default:
		break;
	}

	
	return true;
}

bool UI_Item::Update(float dt)
{
	BROFILER_CATEGORY("UI Element Update();", Profiler::Color::Turquoise)
	
	
	
	

	return true;
}

bool UI_Item::OnClick()
{
	BROFILER_CATEGORY("UI Element OnClick();", Profiler::Color::Cyan)
	bool ret = false;
	
		if (OnHover())
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				App->audio->PlayFx(App->gui->fx_buton_pressed);
				ret = true;
			}

		}
	

	

	return ret;
}

bool UI_Item::SliderClick()
{
	BROFILER_CATEGORY("UI Element SliderClick();", Profiler::Color::Black)
	bool ret = false;

	if (OnHover())
	{
		bool ret = false;

		if ( OnHover())
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				
				ret = true;
			}
			
		}
		return ret;

	}

	return ret;
}
