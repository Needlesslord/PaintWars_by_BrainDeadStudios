#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1UIElements.h"
#include "j1UI_manager.h"
#include "j1SceneManager.h"
#include "TeamLogoScene.h"
#include "TransitionManager.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "j1Audio.h"

TeamLogoScene::TeamLogoScene() : Scene(SCENES::TEAM_LOGO_SCENE)
{

}

// Destructor
TeamLogoScene::~TeamLogoScene()
{

}

// Called before render is available
bool TeamLogoScene::Awake(pugi::xml_node& config)
{
	LOG("Loading GameLogoScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TeamLogoScene::Start()
{
	bool ret = true;
	App->scenes->IN_GAME_SCENE = false;
	teamLogoButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 0, 0 }, { 0,0 }, true, true, { 0, 0, 1280, 720 }, nullptr, App->scenes, TEXTURE::TEAM_LOGO, FONT::FONT_MEDIUM_WHITE, 1);
	teamLogoButton->hover_rect = { 0, 0, 1280, 720 };
	teamLogoButton->click_rect = { 0, 0, 1280, 720 };

	Mix_PlayChannel(-1, App->audio->braindead_sound, 0);

	



	return ret;
}

// Called each loop iteration
bool TeamLogoScene::PreUpdate()
{
	bool ret = true;

	return ret;
}

// Called each loop iteration
bool TeamLogoScene::Update(float dt)
{
	bool ret = true;
	
	CameraDebugMovement(dt);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->audio->Click_Logo_Sound;  /*Mix_VolumeChunk(Click_Logo_Sound, 50);*/
		App->scenes->SwitchScene(SCENES::MENU_SCENE);
	}




	return ret;
}

// Called each loop iteration
bool TeamLogoScene::PostUpdate()
{
	bool ret = true;

	if ( exit)
		ret = false;

	//ExecuteTransition();

	return ret;
}

// Called before quitting
bool TeamLogoScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	teamLogoButton->CleanUp();

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


void TeamLogoScene::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{
	if (element == teamLogoButton && type == GUI_Event::EVENT_ONCLICK)
	{
		App->audio->Click_Logo_Sound;  /*Mix_VolumeChunk(Click_Logo_Sound, 50);*/

		App->transition_manager->CreateAlternatingBars(SCENES::GAME_LOGO_SCENE);
		
	}
}




void TeamLogoScene::ExecuteTransition()
{
	if (!App->transition_manager->is_transitioning)
	{
		/*if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
		{
			App->transition_manager->CreateCut(SCENES::GAME_SCENE);
		}*/

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			App->transition_manager->CreateFadeToColour(SCENES::GAME_SCENE);
		}

			if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
			{
				App->transition_manager->CreateSlide(SCENES::GAME_SCENE, 0.5f, true);
			}

			if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
			{
				//App->transition_manager->CreateSlide(SCENES::SECOND_SCENE, 0.5f, true, true);
			}

			if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
			{
				//App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 0.5f, true);
			}

			if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
			{
				//App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 0.5f, true, true);
			}

			if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
			{
				//App->transition_manager->CreateAlternatingBars(SCENES::SECOND_SCENE, 0.5f, true);
			}

		
		}
	}
