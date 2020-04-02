#include "j1GUI.h"
#include "j1GUIelement.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "j1SceneManager.h"


j1GUIelement::~j1GUIelement()
{
	
}

bool j1GUIelement::Start()
{

	return true;
}


void j1GUIelement::Draw()
{
	if (above && interactable)
	{
		App->render->AddBlitEvent(2, texture, Map_Position.x, Map_Position.y - App->render->camera.y, hover_tex, false, true);
	}
	else 
	{
		App->render->AddBlitEvent(2, texture, Map_Position.x, Map_Position.y - App->render->camera.y, rect, false, true);
	}
}


bool j1GUIelement::OnAbove()
{
	bool ret = false;

	fPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);

	SDL_Rect intersect = { Map_Position.x / App->win->scale , Map_Position.y / App->win->scale, rect.w, rect.h };

	SDL_Point m;
	m.x = mouse.x;
	m.y = mouse.y;

	if (SDL_PointInRect(&m, &intersect) && this->enabled && this->interactable) {
		if (listener != nullptr)
		{
			this->listener->GUI_Event_Manager(GUI_Event::EVENT_HOVER, this);
		}
		ret = true;
	}

	return ret;
}


void j1GUIelement::OnClick()
{
	if (listener != nullptr)
	{
		this->listener->GUI_Event_Manager(GUI_Event::EVENT_ONCLICK, this);
	}
}


void j1GUIelement::OnRelease()
{

}

void j1GUIelement::Dragging()
{

}
