#include "j1GUIscrollBar.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Audio.h"


j1GUIscrollBar::j1GUIscrollBar(SCROLL_TYPE TypeInput) {

	this->type = GUItype::GUI_SCROLLBAR;
	Type = TypeInput;
}

j1GUIscrollBar::~j1GUIscrollBar() {

}


bool j1GUIscrollBar::Awake(pugi::xml_node&)
{

	return true;
}


bool j1GUIscrollBar::Start()
{



	Button = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, this, Map_Position, Inside_Position, true, true, { 432, 36, 14 , 16 }, nullptr, this->listener, true, false);
	Button->Map_Position.y = Map_Position.y - Button->rect.h / 2 + this->rect.h / 2;
	Value = 0;

	if (this->Type == SCROLL_TYPE::SCROLL_MUSIC)
	{

	}

	return true;
}

bool j1GUIscrollBar::PreUpdate()
{

	Button->enabled = enabled;
	above = OnAbove();

	return true;
}

bool j1GUIscrollBar::Update(float dt)
{
	if (interactable) {
		if (above)
		{
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
				OnClick();
		}
	}

	return true;
}

bool j1GUIscrollBar::PostUpdate()
{
	ScrollLimits();
	Value = -((float(-Button->Inside_Position.x) / (float(-this->rect.w) + float(Button->rect.w))) * 128);

	if (this->Type == SCROLL_TYPE::SCROLL_MUSIC)
	{

	}

	if (enabled)
		Draw();

	return true;
}



bool j1GUIscrollBar::CleanUp()
{
	return true;
}


void j1GUIscrollBar::ScrollLimits() {

	if (Button->Inside_Position.x > 0)
	{
		Button->Inside_Position.x = 0;

		Button->Map_Position.x = Button->parent->Map_Position.x - Button->Inside_Position.x;

	}
	else if (Button->Inside_Position.x < (-this->rect.w + Button->rect.w))
	{
		Button->Inside_Position.x = -this->rect.w + Button->rect.w;

		Button->Map_Position.x = Button->parent->Map_Position.x - Button->Inside_Position.x;

	}

}