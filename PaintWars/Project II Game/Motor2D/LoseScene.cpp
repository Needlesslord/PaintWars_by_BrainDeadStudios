#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1GUIELements.h"
#include "j1GUI.h"
#include "j1SceneManager.h"
#include "LoseScene.h"
#include "TransitionManager.h"
#include "j1Audio.h"
#include "SDL_mixer\include\SDL_mixer.h"

LoseScene::LoseScene() : Scene(SCENES::LOSE_SCENE)
{

}

// Destructor
LoseScene::~LoseScene()
{

}

// Called before render is available
bool LoseScene::Awake(pugi::xml_node& config)
{
	LOG("Loading MenuScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool LoseScene::Start()
{
	bool ret = true;

	Lose_Scene_UI = App->gui->AddElement(GUItype::GUI_IMAGE, nullptr, { 0 , 0 }, { 0 , 0 }, false, true, { 0, 0, 1345, 672 }, nullptr, nullptr, false, false, SCROLL_TYPE::SCROLL_NONE, true, TEXTURE::LOSE_SCREEN);

	if (App->audio->PlayingLoseMusic != true) {
		Mix_HaltMusic();
		App->audio->PlayMusic("audio/music/LoseSceneMusic.ogg");
		App->audio->PlayingLoseMusic = true;
	}
	

	return ret;
}

// Called each loop iteration
bool LoseScene::PreUpdate()
{
	bool ret = true;

	return ret;
}

// Called each loop iteration
bool LoseScene::Update(float dt)
{
	bool ret = true;

	CameraDebugMovement(dt);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->scenes->SwitchScene(SCENES::START_SCENE);
	}

	return ret;
}

// Called each loop iteration
bool LoseScene::PostUpdate()
{
	bool ret = true;

	if (exit)
		ret = false;

	//ExecuteTransition();

	return ret;
}

// Called before quitting
bool LoseScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	



	//UI
	for (int i = 0; i < App->gui->GUI_ELEMENTS.count(); i++)
	{
		App->gui->GUI_ELEMENTS[i]->CleanUp();
	}




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


void LoseScene::GUI_Event_Manager(GUI_Event type, j1Element* element)
{

	
}





void LoseScene::ExecuteTransition()
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

		//	if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateExpandingBars(SCENES::SECOND_SCENE, 0.5f, true);
		//	}

		//	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
		//	{
		//		iPoint mouse_pos = App->input->GetMouseToWorld();

		//		App->transition_manager->CreateZoomToMouse(SCENES::SECOND_SCENE, mouse_pos, 0.5f, true);
		//	}

		//	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		//	{
		//		iPoint mouse_pos = App->input->GetMouseToWorld();

		//		App->transition_manager->CreateCameraToMouse(mouse_pos, 0.5f, true);
		//	}


		//	// --- TRANSITION WITH TEXTURE METHODS (NOT IMPLEMENTED)
		//	if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
		//	{
		//		if (scene_texture != nullptr)
		//		{
		//			App->transition_manager->CreateDissolve(SCENES::SECOND_SCENE, 1.0f);
		//		}
		//	}

		//	if (App->input->GetMouseButtonDown(SDL_BUTTON_MIDDLE) == KEY_DOWN)
		//	{
		//		iPoint mouse_pos = App->input->GetMouseToWorld();

		//		if (scene_texture != nullptr)
		//		{
		//			App->transition_manager->CreateZoomToTexture(SCENES::SECOND_SCENE, mouse_pos);
		//		}
		//	}
	}
}
