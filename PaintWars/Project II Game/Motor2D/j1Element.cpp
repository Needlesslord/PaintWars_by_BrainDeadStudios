#include "j1GUI.h"
#include "j1GUIElements.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Window.h"
//#include "j1Scene.h"
#include "j1Textures.h"


j1Element::~j1Element()
{

}

bool j1Element::Start()
{


	return true;
}


void j1Element::Draw()
{


}


bool j1Element::OnAbove()
{
	bool ret = false;

	SDL_Point mouse;
	App->input->GetMousePosition_UI(mouse.x, mouse.y);
	
	SDL_Rect intersect = { map_position.x / App->win->scale , map_position.y / App->win->scale, rect.w / App->win->scale, rect.h / App->win->scale };

	if (SDL_PointInRect(&mouse, &intersect) && this->enabled && this->interactable) {
		if (listener != nullptr)
		{
			this->listener->GUI_Event_Manager(GUI_Event::EVENT_HOVER, this);
		}
		ret = true;
	}

	return ret;
}


void j1Element::OnClick()
{
	if (listener != nullptr)
	{
		this->listener->GUI_Event_Manager(GUI_Event::EVENT_ONCLICK, this);
	}
}


void j1Element::OnRelease()
{

}

void j1Element::Dragging()
{

}
