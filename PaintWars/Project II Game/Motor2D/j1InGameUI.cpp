#include "j1App.h"
#include "j1InGameUI.h"
#include "j1Window.h"
#include "j1GUI.h"
#include "j1SceneManager.h"




j1InGameUI::j1InGameUI() : j1Module()
{

	name = ("InGameUI");
}


j1InGameUI::~j1InGameUI()
{

}

bool j1InGameUI::Awake(pugi::xml_node& config)
{

	return true;
}


bool j1InGameUI::Start()
{
	MiddleScreenW = App->win->width/2 - 100;
	MiddleScreenH = App->win->height/ 2 - 100;
	width = App->win->width;
	Add_UI();
	return true;
}

bool j1InGameUI::PreUpdate()
{

	return true;
}


bool j1InGameUI::Update(float dt)
{

	return true;
}

bool j1InGameUI::CleanUp()
{

	return true;

}

//UI FUNCTIONS
void j1InGameUI::Add_UI()
{
	//menu.optionsButton = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, {width - 200,50 }, { 0,0 }, true, true, { 0,0,100,50 },"", this);
	//menu.continueButton = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, {width-200,500 }, { 0,0 }, true, false, { 0, 0,100,50 }, "", this);
	
}


void j1InGameUI::Activate_Menu()
{
	menu.continueButton->enabled = !menu.continueButton->enabled;
}

void j1InGameUI::GUI_Event_Manager(GUI_Event type, j1GUIelement* element)
{
	switch (type)
	{

	case GUI_Event::EVENT_ONCLICK:
	{
		if (element == menu.continueButton) {
			Activate_Menu();
		}
		if (element == menu.optionsButton) {
			Activate_Menu();
		}
	}}
}