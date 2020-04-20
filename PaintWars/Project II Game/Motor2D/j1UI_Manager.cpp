#include "j1App.h"
#include "j1UI_Manager.h"

#include "j1Render.h"
#include "j1Textures.h"
#include "j1FontsUI.h"
#include "j1Input.h"
#include "j1ButtonUI.h"
#include "j1TextUI.h"
#include "j1SpritesUI.h"

////////////////////////////////////////////////////////////                    /DISCLAIMER                    ///////////////////////////////////////////////////////////
//The very basic structure of the UI belongs to DOLIME CORPORATION (https://github.com/Sanmopre/DOLIME-CORP-PROJECT-II)
j1UI_Manager::j1UI_Manager() : j1Module()
{
	name = ("gui");
}

// Destructor
j1UI_Manager::~j1UI_Manager()
{}


bool j1UI_Manager::Awake(pugi::xml_node& config)
{
	bool ret = true;

	return ret;
}


bool j1UI_Manager::Start()
{



	return true;
}


bool j1UI_Manager::PreUpdate()
{
	bool ret = true;
	p2List_item<j1UIElement*>* tmp = GUI_ELEMENTS.start;
	while (tmp != nullptr)
	{
		ret = tmp->data->PreUpdate();
		tmp = tmp->next;
	}

	return ret;

}


bool j1UI_Manager::Update(float dt)
{

	bool ret = true;
	p2List_item<j1UIElement*>* tmp = GUI_ELEMENTS.start;
	while (tmp != nullptr)
	{
		ret = tmp->data->Update(dt);
		tmp = tmp->next;
	}

	return ret;

}


bool j1UI_Manager::PostUpdate()
{

	bool ret = true;

	p2List_item<j1UIElement*>* tmp = GUI_ELEMENTS.start;
	while (tmp != nullptr)
	{
		ret = tmp->data->PostUpdate();
		tmp = tmp->next;
	}
	return ret;

}



bool j1UI_Manager::CleanUp()
{
	LOG("Freeing GUI");

	for (p2List_item<j1UIElement*>* item = GUI_ELEMENTS.start; item; item = item->next)
	{
		item->data->CleanUp();
	}
	GUI_ELEMENTS.clear();
	return true;
}

SDL_Texture* j1UI_Manager::Get_Texture_From_Image(TEXTURE textureType)
{
	switch (textureType)
	{
	
	
	case TEXTURE::ATLAS:
		Atlas_Load = App->tex->Load("textures/UI/UI_atlas.png");
		return Atlas_Load;
		break;

	case TEXTURE::ATLAS_SPRITE:
		Atlas_Sprite_Load = App->tex->Load("textures/UI/UI_atlas.png");
		return Atlas_Sprite_Load;
		break;

	case TEXTURE::MINIMAP_FULL:
		Minimap_Full_Load = App->tex->Load("textures/UI/Minimap_UI_FULL.png");
		return Minimap_Full_Load;
		break;

	case TEXTURE::MINIMAP_MINI:
		Minimap_Mini_Load = App->tex->Load("textures/UI/Minimap_UI_MINI.png");
		return Minimap_Mini_Load;
		break;
	
	case TEXTURE::MINIMAP_CAMERA:
		Minimap_Camera_Load = App->tex->Load("textures/UI/Minimap_UI_CAMERA.png");
		return Minimap_Camera_Load;
		break;

	case TEXTURE::LOSE_SCREEN_SPRITE:
		Lose_Screen_Sprite_Load = App->tex->Load("textures/UI/Lose_Screen.png");
		return Lose_Screen_Sprite_Load;
		break;

	case TEXTURE::WIN_SCREEN_SPRITE:
		Win_Screen_Sprite_Load = App->tex->Load("textures/UI/Win_Screen.png");
		return Win_Screen_Sprite_Load;
		break;

	case TEXTURE::CONTINUE_LETTERS:
		Continue_Letters_Load = App->tex->Load("textures/UI/Continue.png");
		return Continue_Letters_Load;
		break;

	case TEXTURE::MAIN_IMAGE:
		Main_Image_Load = App->tex->Load("textures/UI/background.png");
		return Main_Image_Load;
		break;

	case TEXTURE::LOGO:
		Logo_Load = App->tex->Load("textures/Logo.png");
		return Logo_Load;
		break;

	case TEXTURE::LOGO_SPRITE:
		Logo_Sprite_Load = App->tex->Load("textures/Logo.png");
		return Logo_Sprite_Load;
		break;

	case TEXTURE::LOGO_LETTERS:
		Logo_Letters = App->tex->Load("textures/Logo_Start.png");
		return Logo_Letters;
		break;

	case TEXTURE::MINIMAP_BACK_SPRITE:
		Minimap_Back_Load = App->tex->Load("textures/Logo_Start.png");
		return Minimap_Back_Load;
		break;

    default:

		 LOG("SWITCH TO LOAD TEXTURES NOT WORKING?");
		 break;

	}
	
	
	
}



j1UIElement* j1UI_Manager::AddElement(TypeOfUI type, j1UIElement* parent, fPoint MapPosition, fPoint TextPositionOnImage, bool Interactable, bool Enabled, SDL_Rect RectArea, char* text, j1Module* Manager, TEXTURE textureType, FONT TypeOfFont, int LayerToBlit)
{

	j1UIElement* temp = nullptr;

	switch (type)
	{

	case TypeOfUI::GUI_BUTTON:
		temp = new j1ButtonUI();
		break;
	case TypeOfUI::GUI_LABEL:
		temp = new j1TextUI();
		break;
	case TypeOfUI::GUI_IMAGE:
		temp = new j1UISprites();
		break;
	
	}

	if (temp)
	{
		temp->parent = parent;
		temp->map_position = MapPosition;
		temp->init_map_position = MapPosition;
		temp->inside_position = TextPositionOnImage;
		temp->listener = Manager;
		temp->interactable = Interactable;
		temp->enabled = Enabled;
		temp->rect = RectArea;
		temp->text = text;
		temp->textureType = textureType;
		temp->fontType = TypeOfFont;
		temp->layer = LayerToBlit;


		GUI_ELEMENTS.add(temp)->data->Start();
	}

	return temp;
}

bool j1UI_Manager::Save(pugi::xml_node& file) const {

	return true;
}


bool j1UI_Manager::Load(pugi::xml_node& file) {

	return true;
}

void j1UI_Manager::UpdatePosition(j1UIElement* element, fPoint position, fPoint localPosition) {
	element->map_position = position;
	element->inside_position = localPosition;
}