#include "j1GUIElements.h"
#include "j1GUI.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Window.h"


j1Label::j1Label()
{
	this->type = GUItype::GUI_LABEL;
}

j1Label::~j1Label() {

}

bool j1Label::Start()
{
	font_name = App->fonts->Load("textures/NameTile.png", "ABCDEFGHIJKLMNOPQRSTUWYZ0123456789-= ", 1);
	return true;
}


bool j1Label::PreUpdate()
{

	return true;
}

bool j1Label::Update(float dt)
{

	if (enabled)
		App->fonts->BlitText(map_position.x + inside_position.x, map_position.y + inside_position.y , 1, text);


	return true;
}

bool j1Label::PostUpdate()
{

	return true;
}

bool j1Label::CleanUp()
{
	App->tex->UnLoad(texture);
	return true;
}