#include "j1App.h"
#include "j1GUI.h"

#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"


j1GUI::j1GUI() : j1Module()
{
	name = ("gui");
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



	return true;
}


bool j1GUI::PreUpdate()
{
	bool ret = true;
	p2List_item<j1Element*>* tmp = GUI_ELEMENTS.start;
	while (tmp != nullptr)
	{
		ret = tmp->data->PreUpdate();
		tmp = tmp->next;
	}

	return ret;

}


bool j1GUI::Update(float dt)
{

	bool ret = true;
	p2List_item<j1Element*>* tmp = GUI_ELEMENTS.start;
	while (tmp != nullptr)
	{
		ret = tmp->data->Update(dt);
		tmp = tmp->next;
	}

	return ret;

}


bool j1GUI::PostUpdate()
{

	bool ret = true;

	p2List_item<j1Element*>* tmp = GUI_ELEMENTS.start;
	while (tmp != nullptr)
	{
		ret = tmp->data->PostUpdate();
		tmp = tmp->next;
	}
	return ret;

}



bool j1GUI::CleanUp()
{
	LOG("Freeing GUI");

	for (p2List_item<j1Element*>* item = GUI_ELEMENTS.start; item; item = item->next)
	{
		item->data->CleanUp();
	}
	GUI_ELEMENTS.clear();
	return true;
}

SDL_Texture* j1GUI::Load_Texture(TEXTURE textureType)
{
	switch (textureType)
	{
	case TEXTURE::BUTON:
		texture_load = App->tex->Load("textures/UI/UI_Test.png");
		break;
	
	case TEXTURE::OPTIONS:
		texture_load = App->tex->Load("textures/UI/UI_Test.png");
		break;
		
	case TEXTURE::ATLAS:
		texture_load = App->tex->Load("textures/UI/UI_atlas.png");
		break;

	case TEXTURE::MINIMAP_FULL:
		texture_load = App->tex->Load("textures/UI/Minimap_UI_FULL.png");
		break;

	case TEXTURE::MINIMAP_MINI:
		texture_load = App->tex->Load("textures/UI/Minimap_UI_MINI.png");
		break;

	case TEXTURE::MINIMAP_BACK:
		texture_load = App->tex->Load("textures/UI/Minimap_UI_BACK.png");
		break;

	case TEXTURE::MINIMAP_CAMERA:
		texture_load = App->tex->Load("textures/UI/Minimap_UI_CAMERA.png");
		break;

	case TEXTURE::LOSE_SCREEN:
		texture_load = App->tex->Load("textures/UI/Lose_Screen.png");
		break;

	case TEXTURE::WIN_SCREEN:
		texture_load = App->tex->Load("textures/UI/Win_Screen.png");
		break;

	case TEXTURE::CONTINUE_LETTERS:
		texture_load = App->tex->Load("textures/UI/Continue.png");
		break;

	case TEXTURE::MAIN_IMAGE:
		texture_load = App->tex->Load("textures/UI/background.png");
		break;

	case TEXTURE::LOGO:
		texture_load = App->tex->Load("textures/Logo.png");
		break;

	case TEXTURE::LOGO_LETTERS:
		texture_load = App->tex->Load("textures/Logo_Start.png");
		break;
	}


	return texture_load;
}



j1Element* j1GUI::AddElement(GUItype type, j1Element* parent, fPoint map_position, fPoint inside_position, bool interactable, bool enabled, SDL_Rect section, char* text, j1Module* listener, bool X_drag, bool Y_drag, SCROLL_TYPE scrollType, bool decor, TEXTURE textureType, FONT fontType, int layer)
{

	j1Element* temp = nullptr;

	switch (type)
	{

	case GUItype::GUI_BUTTON:
		temp = new j1Button();
		break;
	case GUItype::GUI_LABEL:
		temp = new j1Label();
		break;
	case GUItype::GUI_IMAGE:
		temp = new j1Image();
		break;
	
	}

	if (temp)
	{
		temp->parent = parent;
		temp->map_position = map_position;
		temp->init_map_position = map_position;
		temp->inside_position = inside_position;
		temp->listener = listener;
		temp->interactable = interactable;
		temp->X_drag = X_drag;
		temp->Y_drag = Y_drag;
		temp->decorative = decor;
		temp->enabled = enabled;
		temp->rect = section;
		temp->text = text;
		temp->textureType = textureType;
		temp->fontType = fontType;
		temp->layer = layer;


		GUI_ELEMENTS.add(temp)->data->Start();
	}

	return temp;
}

bool j1GUI::Save(pugi::xml_node& file) const {

	return true;
}


bool j1GUI::Load(pugi::xml_node& file) {

	return true;
}

void j1GUI::UpdatePosition(j1Element* element, fPoint position, fPoint localPosition) {
	element->map_position = position;
	element->inside_position = localPosition;
}