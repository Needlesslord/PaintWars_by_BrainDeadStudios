#include "j1GUI.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1GUIbutton.h"
#include "j1GUIinputBox.h"
#include "j1GUIlabel.h"
#include "j1GUIimage.h"

#include "j1GUIscrollBar.h"


j1GUI::j1GUI() : j1Module()
{
	name.create("gui");
}

// Destructor
j1GUI::~j1GUI()
{}


bool j1GUI::Awake(pugi::xml_node& config)
{
	bool ret = true;

	return ret;
}


bool j1GUI::Start()
{
	bool ret = true;
	std::list<j1GUIelement*>::iterator tmp = GUI_ELEMENTS.begin();
	while (tmp != GUI_ELEMENTS.end())
	{
		ret = (*tmp)->Start();
		tmp++;
	}

	return ret;
}


bool j1GUI::PreUpdate()
{
	bool ret = true;
	std::list<j1GUIelement*>::iterator tmp = GUI_ELEMENTS.begin();
	while (tmp != GUI_ELEMENTS.end())
	{
		ret = (*tmp)->PreUpdate();
		tmp++;
	}

	return ret;

}


bool j1GUI::Update(float dt)
{

	bool ret = true;
	std::list<j1GUIelement*>::iterator tmp = GUI_ELEMENTS.begin();
	while (tmp != GUI_ELEMENTS.end())
	{
		ret = (*tmp)->Update(dt);
		tmp++;
	}

	return ret;

}


bool j1GUI::PostUpdate()
{

	bool ret = true;

	std::list<j1GUIelement*>::iterator tmp = GUI_ELEMENTS.begin();
	while (tmp != GUI_ELEMENTS.end())
	{
		ret = (*tmp)->PostUpdate();
		tmp++;
	}
	return ret;

}



bool j1GUI::CleanUp()
{
	LOG("Freeing GUI");

	for (std::list<j1GUIelement*>::iterator item = GUI_ELEMENTS.begin(); item != GUI_ELEMENTS.end(); item++)
	{
		(*item)->CleanUp();
	}
	GUI_ELEMENTS.clear();
	return true;
}



j1GUIelement* j1GUI::ADD_ELEMENT(GUItype type, j1GUIelement* parent, iPoint Map_Position, iPoint Inside_Position, bool interactable, bool enabled, SDL_Rect section, char* text, j1Module* listener, bool X_drag, bool Y_drag, SCROLL_TYPE scrollType, bool decor)
{

	j1GUIelement* temp = nullptr;

	switch (type)
	{

	case GUItype::GUI_BUTTON:
		temp = new j1GUIButton();
		break;
	case GUItype::GUI_INPUTBOX:
		temp = new j1GUIinputBox(text);
		break;
	case GUItype::GUI_LABEL:
		temp = new j1GUIlabel();
		break;
	case GUItype::GUI_IMAGE:
		temp = new j1GUIimage();
		break;
	case GUItype::GUI_SCROLLBAR:
		temp = new j1GUIscrollBar(scrollType);
		break;
	}

	if (temp)
	{
		temp->parent = parent;
		temp->Map_Position = Map_Position;
		temp->Inside_Position = Inside_Position;
		temp->listener = listener;
		temp->interactable = interactable;
		temp->X_drag = X_drag;
		temp->Y_drag = Y_drag;
		temp->decorative = decor;
		temp->enabled = enabled;
		temp->rect = section;
		temp->text = text;

		GUI_ELEMENTS.push_back(temp);
	}

	return temp;
}

bool j1GUI::Save(pugi::xml_node& file) const {

	return true;
}


bool j1GUI::Load(pugi::xml_node& file) {

	return true;
}

void j1GUI::Update_Position(j1GUIelement* element, iPoint position, iPoint localPosition) {
	element->Map_Position = position;
	element->Inside_Position = localPosition;
}