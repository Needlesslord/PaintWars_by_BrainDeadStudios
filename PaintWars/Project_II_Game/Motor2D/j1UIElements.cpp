#include "j1UI_Manager.h"
#include "j1UIElements.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Textures.h"


j1UIElement::~j1UIElement()
{

}

bool j1UIElement::Start()
{


	return true;
}

bool j1UIElement::MouseOnRect()
{
	bool ret = false;

	SDL_Point mouse;
	App->input->GetMousePosition_UI(mouse.x, mouse.y);
	
	SDL_Rect intersect = { init_map_position.x / App->win->scale , init_map_position.y / App->win->scale, rect.w / App->win->scale, rect.h / App->win->scale };

	if (SDL_PointInRect(&mouse, &intersect) && this->enabled && this->interactable) {
		if (listener != nullptr)
		{
			this->listener->GUI_Event_Manager(GUI_Event::EVENT_HOVER, this);
		}
		ret = true;
	}

	return ret;
}


void j1UIElement::Mouse_On_Click()
{
	if (listener != nullptr)
	{
		this->listener->GUI_Event_Manager(GUI_Event::EVENT_ONCLICK, this);
	}
}



