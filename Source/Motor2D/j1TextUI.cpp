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

		font_name_black = App->fonts->Load("textures/fonts/font_black.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
		font_name_white = App->fonts->Load("textures/fonts/font_white.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
		font_name_black_small = App->fonts->Load("textures/fonts/font_black_small.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
		font_name_white_small = App->fonts->Load("textures/fonts/font_white_small.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
		font_name_black_extra_small = App->fonts->Load("textures/fonts/font_black_extra_small.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
		font_name_white_extra_small = App->fonts->Load("textures/fonts/font_white_extra_small.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
		font_name_red = App->fonts->Load("textures/fonts/font_red_extra_small.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
		font_name_red_small = App->fonts->Load("textures/fonts/font_red_small.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);
		font_name_red_extra_small = App->fonts->Load("textures/fonts/font_red.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef ghijklmnopqrstuvwxyz0123456789=/-", 2);

	return true;
}

bool j1TextUI::PreUpdate()
{

	return true;
}

bool j1TextUI::Update(float dt)
{
	if (enabled)
	{
		switch (fontType) {

		case  FONT::FONT_MEDIUM:

			App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y, font_name_black, text, layer);
			break;

		case FONT::FONT_MEDIUM_WHITE:
			App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y, font_name_white, text, layer);
			break;

		case FONT::FONT_SMALL:
			App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y, font_name_black_small, text, layer);
			break;

		case FONT::FONT_SMALL_WHITE:
			App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y, font_name_white_small, text, layer);
			break;

		case FONT::FONT_EXTRA_SMALL:
			App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y, font_name_black_extra_small, text, layer);
			break;

		case FONT::FONT_EXTRA_SMALL_WHITE:
			App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y, font_name_white_extra_small, text, layer);
			break;

		case FONT::FONT_EXTRA_SMALL_RED:
			App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y, font_name_red, text, layer);
			break;

		case FONT::FONT_SMALL_RED:
			App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y, font_name_red_small, text, layer);
			break;

		case  FONT::FONT_MEDIUM_RED:

			App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y, font_name_red_extra_small, text, layer);
			break;

		}

		
	}


	return true;
}

bool j1TextUI::PostUpdate()
{

	return true;
}

bool j1TextUI::CleanUp()
{
	App->fonts->UnLoad(font_name_black);
	App->fonts->UnLoad(font_name_black_small);
	App->fonts->UnLoad(font_name_black_extra_small);
	App->fonts->UnLoad(font_name_white);
	App->fonts->UnLoad(font_name_white_small);
	App->fonts->UnLoad(font_name_white_extra_small);
	App->fonts->UnLoad(font_name_red);
	App->fonts->UnLoad(font_name_red_small);
	App->fonts->UnLoad(font_name_red_extra_small);
	text = " ";

	return true;
}


