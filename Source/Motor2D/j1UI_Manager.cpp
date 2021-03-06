#include "j1App.h"
#include "j1UI_Manager.h"

#include "j1Render.h"
#include "j1Textures.h"
#include "j1FontsUI.h"
#include "j1Input.h"
#include "j1ButtonUI.h"
#include "j1TextUI.h"
#include "j1SpritesUI.h"

////////////////////////////////////////////////////////////                    /DISCLAIMER                    ////////////////////////////////////////////////////////////////
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
		Texture_To_Load = App->tex->Load("textures/UI/UI_atlas.png");
		return Texture_To_Load;
		break;

	case TEXTURE::ATLAS_SPRITE:
		Texture_To_Load = App->tex->Load("textures/UI/UI_atlas.png");
		return Texture_To_Load;
		break;

	// minimaps
	case TEXTURE::MINIMAP_ENTITIES:
		Texture_To_Load = App->tex->Load("textures/UI/UI_minimap_entities.png");
		return  Texture_To_Load;
		break;

	case TEXTURE::MINIMAP_FULL_FOREST:
		Texture_To_Load = App->tex->Load("textures/UI/UI_minimap_forest_full.png");
		return Texture_To_Load;
		break;

	case TEXTURE::MINIMAP_MINI_FOREST:
		Texture_To_Load = App->tex->Load("textures/UI/UI_minimap_forest_mini.png");
		return Texture_To_Load;
		break;

	case TEXTURE::MINIMAP_FULL_SNOW:
		Texture_To_Load = App->tex->Load("textures/UI/UI_minimap_snow_full.png");
		return Texture_To_Load;
		break;

	case TEXTURE::MINIMAP_MINI_SNOW:
		Texture_To_Load = App->tex->Load("textures/UI/UI_minimap_snow_mini.png");
		return Texture_To_Load;
		break;

	case TEXTURE::MINIMAP_FULL_VOLCANO:
		Texture_To_Load = App->tex->Load("textures/UI/UI_minimap_volcano_full.png");
		return Texture_To_Load;
		break;

	case TEXTURE::MINIMAP_MINI_VOLCANO:
		Texture_To_Load = App->tex->Load("textures/UI/UI_minimap_volcano_mini.png");
		return Texture_To_Load;
		break;
	//end minimaps
	
	case TEXTURE::MINIMAP_CAMERA:
		Texture_To_Load = App->tex->Load("textures/UI/UI_minimap_camera.png");
		return Texture_To_Load;
		break;

	case TEXTURE::LOSE_SCREEN_SPRITE:
		Texture_To_Load = App->tex->Load("textures/UI/UI_screen_lose.png");
		return Texture_To_Load;
		break;

	case TEXTURE::WIN_SCREEN_SPRITE:
		Texture_To_Load = App->tex->Load("textures/UI/UI_screen_win.png");
		return Texture_To_Load;
		break;

	case TEXTURE::CONTINUE_LETTERS:
		Texture_To_Load = App->tex->Load("textures/UI/UI_buttons_continue.png");
		return Texture_To_Load;
		break;

	case TEXTURE::MAIN_IMAGE:
		Texture_To_Load = App->tex->Load("textures/UI/UI_background.png");
		return Texture_To_Load;
		break;

	case TEXTURE::LOGO:
		Texture_To_Load = App->tex->Load("textures/logo_paintwars.png");
		return Texture_To_Load;
		break;

	case TEXTURE::LOGO_SPRITE:
		Texture_To_Load = App->tex->Load("textures/logo_paintwars.png");
		return Texture_To_Load;
		break;

	case TEXTURE::LOGO_LETTERS:
		Texture_To_Load = App->tex->Load("textures/UI/UI_buttons_logoStart.png");
		return Texture_To_Load;
		break;

	case TEXTURE::TEAM_LOGO:
		Texture_To_Load = App->tex->Load("textures/logo_braindeadStudios.png");
		return Texture_To_Load;
		break;

	case TEXTURE::MINIMAP_BACK_SPRITE:
		Texture_To_Load = App->tex->Load("texturesUI/UI_buttons_logoStart.png");
		return Texture_To_Load;
		break;

	case TEXTURE::BACKGROUND_FOREST:
		Texture_To_Load = App->tex->Load("textures/UI/UI_background_forest.png");
		return Texture_To_Load;
		break;

	case TEXTURE::BACKGROUND_SNOW:
		Texture_To_Load = App->tex->Load("textures/UI/UI_background_snow.png");
		return Texture_To_Load;
		break;

	case TEXTURE::BACKGROUND_VOLCANO:
		Texture_To_Load = App->tex->Load("textures/UI/UI_background_volcano.png");
		return Texture_To_Load;
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