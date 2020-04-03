#include "j1GUIElements.h"
#include "j1GUI.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Window.h"

j1InputBox::j1InputBox(char* text)
{
	this->type = GUItype::GUI_INPUTBOX;

}

j1InputBox::~j1InputBox() {

}

bool j1InputBox::Start()
{
	string = App->gui->AddElement(GUItype::GUI_LABEL, this, map_position, { 0,3 }, true, enabled, { (int)inside_position.x, (int)inside_position.y, 50, 0 }, text);
	return true;
}


bool j1InputBox::PreUpdate()
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

bool j1InputBox::Update(float dt)
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

bool j1InputBox::PostUpdate()
{
	if (enabled) {
		Draw();

		if (focus)
		{
			SDL_Rect rect = { (string->map_position.x + string->rect.w) * App->win->GetScale() , (string->map_position.y + inside_position.y) * App->win->GetScale(), 2,  string->rect.h + 10 };
			App->render->DrawQuad(rect, 255, 255, 255, 255, true, false);
		}
	}


	return true;
}

bool j1InputBox::CleanUp()
{
	return true;
}

void j1InputBox::OnClick()
{
	focus = true;

}

void j1InputBox::OnRelease()
{

}


