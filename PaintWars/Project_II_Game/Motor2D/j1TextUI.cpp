#include "j1UIElements.h"
#include "j1UI_Manager.h"
#include "j1App.h"
#include "j1FontsUI.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1TextUI.h"


j1TextUI::j1TextUI()
{
	this->type = TypeOfUI::GUI_LABEL;
}

j1TextUI::~j1TextUI() {

}

bool j1TextUI::Start()
{
	if(fontType == FONT::FONT_MEDIUM)
		font_name = App->fonts->Load("textures/font.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
	else if (fontType == FONT::FONT_MEDIUM_WHITE)
		font_name = App->fonts->Load("textures/font_white.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
	else if(fontType == FONT::FONT_SMALL)
		font_name = App->fonts->Load("textures/font_small.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
	else if (fontType == FONT::FONT_SMALL_WHITE)
		font_name = App->fonts->Load("textures/font_small_white.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
	else if (fontType == FONT::FONT_EXTRA_SMALL)
		font_name = App->fonts->Load("textures/font_extra_small.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
	else if (fontType == FONT::FONT_EXTRA_SMALL_WHITE)
		font_name = App->fonts->Load("textures/font_extra_small_white.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
	

	return true;
}


bool j1TextUI::PreUpdate()
{

	return true;
}

bool j1TextUI::Update(float dt)
{

	if (enabled)
		App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y, font_name, text, layer);


	return true;
}

bool j1TextUI::PostUpdate()
{

	return true;
}

bool j1TextUI::CleanUp()
{
	App->fonts->UnLoad(font_name);
	text = " ";

	return true;
}


