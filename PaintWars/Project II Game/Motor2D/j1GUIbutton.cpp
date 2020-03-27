#include "j1App.h"
#include "j1GUIButton.h"
#include "j1Input.h"
#include "j1GUI.h"


j1GUIButton::j1GUIButton() {
	this->type = GUItype::GUI_BUTTON;
}

j1GUIButton::~j1GUIButton() {

}


bool j1GUIButton::Awake(pugi::xml_node&)
{

	return true;
}

bool j1GUIButton::Start()
{
	if (text != nullptr)
		label = App->gui->ADD_ELEMENT(GUItype::GUI_LABEL, this, Map_Position, Inside_Position, true, true, { 0,0,0,0 }, text);

	return true;
}

bool j1GUIButton::PreUpdate()
{
	if (label != nullptr)
		label->enabled = enabled;

	above = OnAbove();

	return true;
}

bool j1GUIButton::Update(float dt)
{
	if (interactable)
	{
		if (above)
		{
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
				OnClick();

			if (App->input->GetMouseButtonDown(1) == KEY_REPEAT)
			{
				if (X_drag || Y_drag)
					dragging = true;

				iPoint mouseClick = { 0,0 };
				App->input->GetMousePosition(mouseClick.x, mouseClick.y);
				Drag = { mouseClick.x - (this->Map_Position.x), mouseClick.y - (this->Map_Position.y) };

			}

		}

		if (dragging) {

			if (App->input->GetMouseButtonDown(1) == KEY_IDLE || App->input->GetMouseButtonDown(1) == KEY_UP)
				dragging = false;
			else
			{
				Dragging();
				MovingIt(dt);
			}
		}
	}
	return true;
}

bool j1GUIButton::PostUpdate()
{
	if (enabled)
		Draw();

	return true;
}

bool j1GUIButton::CleanUp()
{
	return true;
}

void j1GUIButton::Dragging()
{

}

void j1GUIButton::MovingIt(float dt)
{

	iPoint MousePos = { 0,0 };
	App->input->GetMousePosition(MousePos.x, MousePos.y);

	iPoint currentPos = this->Map_Position;


	if (X_drag)
		this->Map_Position.x += ((MousePos.x - this->Map_Position.x) - Drag.x);

	if (Y_drag)
		this->Map_Position.y += ((MousePos.y - this->Map_Position.y) - Drag.y);


	if (parent != nullptr)
	{
		if (X_drag)
			this->Inside_Position.x += currentPos.x - this->Map_Position.x;

		if (Y_drag)
			this->Inside_Position.y += currentPos.y - this->Map_Position.y;

		if (X_drag)
			this->Map_Position.x = parent->Map_Position.x - Inside_Position.x;

		if (Y_drag)
			this->Map_Position.y = parent->Map_Position.y - Inside_Position.y;
	}

}

void j1GUIButton::OnRelease()
{

}
