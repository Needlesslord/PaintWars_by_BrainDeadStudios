#include "j1App.h"
#include "p2Log.h"
#include "j1ElementUI.h"
#include "j1Gui.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Button.h"



UIitem_Button::UIitem_Button(const char* text, Button_Type type, SDL_Rect idle_rect, SDL_Rect* rect_hover, SDL_Rect* rect_click, UI_Item* parent)
{
	button_rect[IDLE] = idle_rect;

	if (rect_hover == NULL)
	{
		button_rect[HOVER] = idle_rect;
	}
	else
	{
		button_rect[HOVER] = *rect_hover;
	}

	if (rect_click == NULL)
	{
		button_rect[CLICK] = *rect_hover;
	}
	else
	{
		button_rect[CLICK] = *rect_click;
	}


	button_text.create(text);
	button_type = type;
	this->parent = parent;
}

UIitem_Button::~UIitem_Button()
{
}

bool UIitem_Button::Start()
{
	

	if (button_text.Length() > 0)
		App->gui->CreateLabel({ pos.x + 10, pos.y + 5 }, button_text.GetString(), CONFIG, { 0,0,0,0 }, static_object, this);
	return true;
}

bool UIitem_Button::PostUpdate()
{
	
	bool ret = true;

	switch (state)
	{
	case IDLE:
		ret = App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &button_rect[IDLE]); //AQUI ESTA
		break;

	case HOVER:
		ret = App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &button_rect[HOVER]);
		break;

	case CLICK:
		ret = App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &button_rect[CLICK]);
		break;
	}

	return ret;
}

Button_Type UIitem_Button::GetType()
{
	return button_type;
}

bool UIitem_Button::OnHover()
{
	return position.x < mouse_position.x && position.y  < mouse_position.y && position.x + button_rect[state].w > mouse_position.x && position.y + button_rect[state].h > mouse_position.y;

}








