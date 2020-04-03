#include <iostream>
#include <vector>
#include "j1App.h"
#include "j1InGameUI.h"
#include "j1Window.h"
#include "j1GUI.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1EntityManager.h"
#include "Entity.h"
#include "j1SceneManager.h"



j1InGameUI::j1InGameUI() : j1Module()
{

	//name.create("InGameUI");
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

	type_0 = 0;
	type_1 = 0;
	type_2 = 0;

	font_name = App->fonts->Load("textures/NameTile.png", "ABCDEFGHIJKLMNOPQRSTUWYZ0123456789-= ", 1);
	
	MiddleScreenW = App->win->width/2 - 100;
	MiddleScreenH = App->win->height/ 2 - 100;
	width = App->win->width;

	selected_offset = 0;
	selected_total = 0;

	//CREATES UI

	Add_UI();

	return true;
}

bool j1InGameUI::PreUpdate()
{

	return true;
}

bool j1InGameUI::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		Activate_Menu();
		
	}

	return true;
}

bool j1InGameUI::CleanUp()
{

	return true;

}

//UI FUNCTIONS
void j1InGameUI::Add_UI()
{
	//MENU
	menu.Menu_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, {width -50,10 }, { 0,0 }, true, true, { 0,0,40,40 }, "", this,false, false, SCROLL_TYPE::SCROLL_NONE,true, TEXTURE::OPTIONS);
	menu.Return_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH-140 }, { 0,30 }, true, false, { 0,0,200,65 }, "MORE RESOURCES", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.Resume_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH -60}, { 60,30 }, true, false, { 0,0,200,65 }, "RESUME", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.Exit_button = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH + 15 }, {60,30 }, true, false, { 0,0,200,65 }, "FULLSCREEN", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.Save = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH +90 }, { 60,30 }, true, false, { 0,0,200,65 }, "QUIT", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.Load = App->gui->AddElement(GUItype::GUI_BUTTON, nullptr, { MiddleScreenW + 25,MiddleScreenH +165}, { 35,30 }, true, false, { 0,0,200,65 }, "MAIN MENU", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	menu.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, { MiddleScreenW - 50,0 }, { 0,0 }, true, false, { 0, 0,350,500 },"", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::IMAGE);



	///////////////////////////////
	menu.Scroll = App->gui->AddElement(GUItype::GUI_SCROLLBAR, nullptr, { 190, 70 }, { 0,0 }, false, false, { 0, 0, 260, 7 }, nullptr, this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::SCROLL);
	///////////////////////////////
	
	//UI BASICS ALWAYS ACTIVE
	basics.Image = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, {0,520 }, { 0,0 }, true, true, { 0, 0,1280,200 }, "", this, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::BUTON);
	



}

void j1InGameUI::Activate_Menu()
{
	menu.Resume_button->enabled = !menu.Resume_button->enabled;
	menu.Return_button->enabled = !menu.Return_button->enabled;
	menu.Exit_button->enabled = !menu.Exit_button->enabled;
	menu.Load->enabled = !menu.Load->enabled;
	menu.Save->enabled = !menu.Save->enabled;
	menu.Image->enabled = !menu.Image->enabled;
	menu.Scroll->enabled = !menu.Scroll->enabled;
}

void j1InGameUI::GUI_Event_Manager(GUI_Event type, j1Element* element)
{
 clicking_ui = true;
	switch (type)
	{

	case GUI_Event::EVENT_ONCLICK:
	{

		if (element == menu.Return_button)
			

		

		if (element == menu.Save) {
			quit = true;
		}
		if (element == menu.Resume_button) {
			Activate_Menu();
		}
		if (element == menu.Menu_button) {
			
			Activate_Menu();
		}
	
	
	}
	}
}

bool j1InGameUI::PostUpdate()
{
	clicking_ui = false;

	bool ret = true;
	if (quit == true) {
		return false;
	}
	return ret;
}

void j1InGameUI::Activate_Necessary_UI() {
	basics.Image->enabled = true;
	basics.Resources->enabled = true;
	menu.Menu_button->enabled = true;

}