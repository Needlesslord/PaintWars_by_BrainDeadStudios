#include "j1GUIinputBox.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Window.h"

j1GUIinputBox::j1GUIinputBox(char* text)
{
	this->type = GUItype::GUI_INPUTBOX;

}

j1GUIinputBox::~j1GUIinputBox() {

}


bool j1GUIinputBox::Awake(pugi::xml_node&)
{

	return true;
}

bool j1GUIinputBox::Start()
{
	string = App->gui->ADD_ELEMENT(GUItype::GUI_LABEL, this, Map_Position, { 0,3 }, true, enabled, { Inside_Position.x,Inside_Position.y,50,50 }, text);
	return true;
}


bool j1GUIinputBox::PreUpdate()
{
	string->enabled = enabled;

	if (focus)
	{
		App->input->EnableTextInput();
	}

	else if (!focus)
		App->input->DisableTextInput();

	above = OnAbove();

	return true;
}

bool j1GUIinputBox::Update(float dt)
{

	if (above)
	{
		if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
			OnClick();
	}
	else {
		if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
			focus = false;
	}


	return true;
}

bool j1GUIinputBox::PostUpdate()
{
	if (enabled) {
		Draw();

		if (focus)
		{
			SDL_Rect rect = { (string->Map_Position.x + string->rect.w) * App->win->GetScale() , (string->Map_Position.y + Inside_Position.y) * App->win->GetScale(), 2,  string->rect.h + 10 };
			App->render->DrawQuad(rect, 255, 255, 255, 255, true, false);
		}
	}


	return true;
}

bool j1GUIinputBox::CleanUp()
{
	return true;
}

void j1GUIinputBox::OnClick()
{
	focus = true;

}

void j1GUIinputBox::OnRelease()
{

}


