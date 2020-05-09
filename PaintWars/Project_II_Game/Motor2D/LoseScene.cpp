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
#include "LoseScene.h"
#include "TransitionManager.h"
#include "j1Audio.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "j1EntityManager.h"
#include "j1Player.h"

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
	FinishedPosition = false;
	App->scenes->IN_GAME_SCENE = false;
	Lose_Scene_UI = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0 , 0 }, { 0 , 0 }, true, true, { 0, 0, 1278, 719}, nullptr, nullptr, TEXTURE::LOSE_SCREEN_SPRITE);
	
	TryAgain = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 275, 600 }, { 30,25 }, true, true, { 285, 575,712 ,62 },nullptr, App->scenes, TEXTURE::CONTINUE_LETTERS);
	TryAgain->hover_rect = { 285, 97,712 ,62 };
	TryAgain->click_rect = { 285, 97,712 ,62 };
	Lose_Timer = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 500 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "Timer");

	if (App->audio->PlayingLoseMusic != true) {
		Mix_HaltMusic();
		App->audio->PlayingMenuMusic = false;
		App->audio->PlayMusic("audio/music/LoseSceneMusic.ogg");
		App->audio->PlayingLoseMusic = true;
	}
	


	static char conversorCharTimer[256];
	int Sec_Conversor = App->scenes->Timer_Seconds;
	int Min_Conversor = App->scenes->Timer_Minutes;
	sprintf_s(conversorCharTimer, 256, "%d/%d", Min_Conversor, Sec_Conversor);
	Lose_Timer->text = conversorCharTimer;


	ResetPosition = true;

	return ret;
}

// Called each loop iteration
bool LoseScene::PreUpdate()
{
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	bool ret = true;

	if (ResetPosition == true) {
		TryAgain->map_position.x = -550;
		ResetPosition = false;
	}
	return ret;
}

// Called each loop iteration
bool LoseScene::Update(float dt)
{
	bool ret = true;

	CameraDebugMovement(dt);

	if (TryAgain->map_position.x < 275 && App->transition_manager->is_transitioning == false) {
		TryAgain->map_position = TryAgain->map_position = { TryAgain->map_position.x + 5,TryAgain->map_position.y };
		
	}
	else if (App->transition_manager->is_transitioning == false) {
		FinishedPosition = true; //ONLY ONE CHANGE TO TRUE IS NEEDED BECAUSE ALL BUTTONS GET TO THEIR POSITION AT THE SAME MOMENT
	}


	



	return ret;
}

// Called each loop iteration
bool LoseScene::PostUpdate()
{
	App->player->Mouse_Cursor();
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
		//RELEASE(App->gui->GUI_ELEMENTS[i]);
	}
	
	RELEASE(Lose_Scene_UI);




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


void LoseScene::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{
	if (FinishedPosition == true) {
		if (element == TryAgain && type == GUI_Event::EVENT_ONCLICK)
		{
			Mix_HaltMusic();
			if (App->audio->PlayingMenuMusic != true) {
				App->audio->PlayMusic("audio/music/MainMenu_Music.ogg");
				App->audio->PlayingMenuMusic = true;
			}
			App->entities->CleanUp();
			App->audio->PlayingLoseMusic = false;
			App->transition_manager->CreateSlide(SCENES::MENU_SCENE, 0.5f, true);
		}
	}
}





void LoseScene::ExecuteTransition()
{
	//if (!App->transition_manager->is_transitioning)
	//{
	//	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
	//	{
	//		App->transition_manager->CreateCut(SCENES::GAME_SCENE);
	//	}

	//	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	//	{
	//		App->transition_manager->CreateFadeToColour(SCENES::GAME_SCENE);
	//	}

	//	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
	//	{
	//		App->transition_manager->CreateSlide(SCENES::GAME_SCENE, 0.5f, true);
	//	}

	//	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	//	{
	//		//App->transition_manager->CreateSlide(SCENES::SECOND_SCENE, 0.5f, true, true);
	//	}

	//	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	//	{
	//		//App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 0.5f, true);
	//	}

	//	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
	//	{
	//		//App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 0.5f, true, true);
	//	}

	//	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
	//	{
	//		//App->transition_manager->CreateAlternatingBars(SCENES::SECOND_SCENE, 0.5f, true);
	//	}

	//	//	if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
	//	//	{
	//	//		App->transition_manager->CreateExpandingBars(SCENES::SECOND_SCENE, 0.5f, true);
	//	//	}

	//	//	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	//	//	{
	//	//		iPoint mouse_pos = App->input->GetMouseToWorld();

	//	//		App->transition_manager->CreateZoomToMouse(SCENES::SECOND_SCENE, mouse_pos, 0.5f, true);
	//	//	}

	//	//	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	//	//	{
	//	//		iPoint mouse_pos = App->input->GetMouseToWorld();

	//	//		App->transition_manager->CreateCameraToMouse(mouse_pos, 0.5f, true);
	//	//	}


	//	//	// --- TRANSITION WITH TEXTURE METHODS (NOT IMPLEMENTED)
	//	//	if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
	//	//	{
	//	//		if (scene_texture != nullptr)
	//	//		{
	//	//			App->transition_manager->CreateDissolve(SCENES::SECOND_SCENE, 1.0f);
	//	//		}
	//	//	}

	//	//	if (App->input->GetMouseButtonDown(SDL_BUTTON_MIDDLE) == KEY_DOWN)
	//	//	{
	//	//		iPoint mouse_pos = App->input->GetMouseToWorld();

	//	//		if (scene_texture != nullptr)
	//	//		{
	//	//			App->transition_manager->CreateZoomToTexture(SCENES::SECOND_SCENE, mouse_pos);
	//	//		}
	//	//	}
	//}
}

