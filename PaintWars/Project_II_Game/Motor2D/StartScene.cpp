#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1UI_manager.h"
#include "j1SceneManager.h"
#include "StartScene.h"
#include "TransitionManager.h"
#include "j1Audio.h"
#include "j1Player.h"
#include "SDL_mixer\include\SDL_mixer.h"

StartScene::StartScene() : Scene(SCENES::START_SCENE)
{

}

// Destructor
StartScene::~StartScene()
{

}

// Called before render is available
bool StartScene::Awake(pugi::xml_node& config)
{
	LOG("Loading MenuScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool StartScene::Start()
{
	bool ret = true;
	App->scenes->IN_GAME_SCENE = false;

	backgroundImage = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0, 0 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes,TEXTURE::MAIN_IMAGE, FONT::FONT_MEDIUM, 1);


	continueButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 475, 190 }, { 30,25 }, true, true, { 0, 0, 263, 91 }, "CONTINUE", App->scenes, TEXTURE::ATLAS);
	continueButton->hover_rect = { 263, 0, 263, 91 };
	continueButton->click_rect = { 526, 0, 263, 91 };

	forestButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 485, 320 }, { 30,20 }, true, true, { 0, 334, 234, 79 }, "Forest", App->scenes, TEXTURE::ATLAS);
	forestButton->hover_rect = { 263, 334, 234, 79 };
	forestButton->click_rect = { 525, 334, 234, 79 };

	snowButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 485, 430 }, { 60,20 }, true, true, { 0, 334, 234, 79 }, "Snow", App->scenes,  TEXTURE::ATLAS);
	snowButton->hover_rect = { 263, 334, 234, 79 };
	snowButton->click_rect = { 525, 334, 234, 79 };

	volcanoButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 485, 540 }, { 20,20 }, true, true, { 0, 334, 234, 79 }, "Volcano", App->scenes, TEXTURE::ATLAS);
	volcanoButton->hover_rect = { 263, 334, 234, 79 };
	volcanoButton->click_rect = { 525, 334, 234, 79 };

	backButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 900, 640 }, { 50,15 }, true, true, { 0, 658, 207, 71 }, "BACK", App->scenes, TEXTURE::ATLAS);
	backButton->hover_rect = { 263, 658, 207, 71 };
	backButton->click_rect = { 525, 658, 207, 71 };

	//LOADING

	
	
	if (App->audio->PlayingMenuMusic != true) {
		App->audio->PlayMusic("audio/music/MainMenu_Music.ogg");
		App->audio->PlayingMenuMusic = true;
	}

	return ret;
}

// Called each loop iteration
bool StartScene::PreUpdate()
{
	bool ret = true;

	return ret;
}

// Called each loop iteration
bool StartScene::Update(float dt)
{
	bool ret = true;

	CameraDebugMovement(dt);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->scenes->SwitchScene(SCENES::GAME_SCENE);
	}

	return ret;
}

// Called each loop iteration
bool StartScene::PostUpdate()
{
	//App->player->Mouse_Cursor();
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	//ExecuteTransition();

	return ret;
}

// Called before quitting
bool StartScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	continueButton->CleanUp();
	forestButton->CleanUp();
	snowButton->CleanUp();
	volcanoButton->CleanUp();
	backButton->CleanUp();
	backgroundImage->CleanUp();

	RELEASE(backgroundImage);

	if (scene_texture != nullptr)
	{
		App->tex->UnLoad(scene_texture);
	}

	if (tileset_texture != nullptr)
	{
		App->tex->UnLoad(tileset_texture);
	}

	if (SDL_RenderClear(scene_renderer) == 0)
	{
		scene_renderer = nullptr;
	}

	if (scene_surface != nullptr)
	{
		SDL_FreeSurface(scene_surface);
	}

	return ret;
}


void StartScene::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{
	if (element == backButton && type == GUI_Event::EVENT_ONCLICK)
	{
		
		App->transition_manager->CreateSlide(SCENES::MENU_SCENE, 0.5f, true);

	}

	if (element == continueButton && type == GUI_Event::EVENT_ONCLICK)
	{
		
		if (App->scenes->Map_Forest_Active == true) {
			App->scenes->Load_Map_Forest = true;
			App->scenes->Load_Map_Snow = false;
			App->scenes->Load_Map_Volcano = false;
			App->scenes->Map_Forest_Active = false;
		}
		else if (App->scenes->Map_Snow_Active == true) {
			App->scenes->Load_Map_Snow = true;
			App->scenes->Load_Map_Forest = false;
			App->scenes->Load_Map_Volcano = false;
			App->scenes->Map_Snow_Active = false;
		}
		else if (App->scenes->Map_Volcano_Active == true) {
			App->scenes->Load_Map_Volcano = true;
			App->scenes->Load_Map_Forest = false;
			App->scenes->Load_Map_Snow = false;
			App->scenes->Map_Volcano_Active = false;
		}

		App->transition_manager->CreateSlide(SCENES::GAME_SCENE, 0.5f, true);

	}

	if ((element == snowButton || element == forestButton || element == volcanoButton) && type == GUI_Event::EVENT_ONCLICK)
	{
		
		if (element == forestButton) {
			LOG("GOING TO FOREST MAP");
			App->scenes->Load_Map_Forest = true;
			App->scenes->Load_Map_Snow = false;
			App->scenes->Load_Map_Volcano = false;
		}
		else if (element == snowButton) {
			LOG("GOING TO SNOW MAP");
			App->scenes->Load_Map_Snow = true;
			App->scenes->Load_Map_Forest = false;
			App->scenes->Load_Map_Volcano = false;
		}
		else if (element == volcanoButton) {
			LOG("GOING TO VOLCANO MAP");
			App->scenes->Load_Map_Volcano = true;
			App->scenes->Load_Map_Forest = false;
			App->scenes->Load_Map_Snow = false;
		}

		App->transition_manager->CreateSlide(SCENES::GAME_SCENE, 0.5f, true);
	}
}





void StartScene::ExecuteTransition()
{
	if (!App->transition_manager->is_transitioning)
	{
		if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
		{
			App->transition_manager->CreateCut(SCENES::GAME_SCENE);
		}

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			App->transition_manager->CreateFadeToColour(SCENES::GAME_SCENE);
		}

		
	}
}
