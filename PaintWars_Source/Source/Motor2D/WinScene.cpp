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
#include "WinScene.h"
#include "TransitionManager.h"
#include "j1Audio.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "j1EntityManager.h"
#include "j1Player.h"

WinScene::WinScene() : Scene(SCENES::WIN_SCENE)
{

}

// Destructor
WinScene::~WinScene()
{

}

// Called before render is available
bool WinScene::Awake(pugi::xml_node& config)
{
	LOG("Loading MenuScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool WinScene::Start()
{
	LOG("WIN SCENE Start");
	bool ret = true;
	FinishedPosition = false;
	App->scenes->IN_GAME_SCENE = false;
	Win_Scene_UI = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0 , 0 }, { 0 , 0 }, true, true, { 0, 0, 1278, 719 }, nullptr, nullptr, TEXTURE::WIN_SCREEN_SPRITE);

	ReturnVictorious = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 300, 600 }, { 0 , 0 }, true, true, { 322, 398,630 ,58 }, nullptr, App->scenes, TEXTURE::CONTINUE_LETTERS);
	ReturnVictorious->hover_rect = { 322, 237,630 ,58 };
	ReturnVictorious->click_rect = { 322, 237,630 ,58 };
	/*Win_Timer_Sec=App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 500, 150 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "Sec");
	Win_Timer_Min = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 150 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "Min");*/
	Win_Timer = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 500 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "Timer");

	//if (App->audio->PlayingWinMusic != true) {
	//	Mix_HaltMusic();
	//	App->audio->PlayingWinMusic = false;
	//	App->audio->PlayMusic("audio/music/music_scene_win.ogg"); 
	//	App->audio->PlayingWinMusic = true;
	//}


	static char conversorCharTimer[256];
	int Sec_Conversor = App->scenes->Timer_Seconds;
	int Min_Conversor = App->scenes->Timer_Minutes;
	sprintf_s(conversorCharTimer, 256, "%d/%d", Min_Conversor, Sec_Conversor);
	Win_Timer->text = conversorCharTimer;



	ResetPosition = true;
	return ret;
}

// Called each loop iteration
bool WinScene::PreUpdate()
{
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	bool ret = true;


	if (ResetPosition == true  ) {
		ReturnVictorious->map_position.x = -550;
		ResetPosition = false;
	}


	return ret;
}

// Called each loop iteration
bool WinScene::Update(float dt)
{
	bool ret = true;

	CameraDebugMovement(dt);
	

	/*App->scenes->Timer_Seconds = App->player->gameTimer.ReadSec();
	App->scenes->Timer_Minutes = 0;
	for (int i = 0; i < 17; i++) {
		if (App->scenes->Timer_Seconds > 59) {
			App->scenes->Timer_Seconds -= 60;
			if (App->scenes->Timer_Minutes == i)
				App->scenes->Timer_Minutes++;
		}
	}*/

	/*Win_Timer->map_position;
	App->render->camera.x= Win_Timer->map_position.x;
	App->render->camera.y = Win_Timer->map_position.y;*/


	


	


	if (ReturnVictorious->map_position.x < 300 && App->transition_manager->is_transitioning==false) {
		ReturnVictorious->map_position = ReturnVictorious->map_position = { ReturnVictorious->map_position.x +5,ReturnVictorious->map_position.y };
		
	}
	else if (App->transition_manager->is_transitioning == false) {
		FinishedPosition = true; //ONLY ONE CHANGE TO TRUE IS NEEDED BECAUSE ALL BUTTONS GET TO THEIR POSITION AT THE SAME MOMENT
	}
	
	return ret; 
}

// Called each loop iteration
bool WinScene::PostUpdate()
{
	App->player->Mouse_Cursor();
	bool ret = true;

	if (exit)
		ret = false;

	//ExecuteTransition();
	fPoint MousePos = App->input->GetMouseWorldPosition();

	LOG("Mouse x at WIN SCENE %f", MousePos.x);

	LOG("Mouse y at WIN SCENE %f", MousePos.y);
	return ret;
}

// Called before quitting
bool WinScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;





	//UI
	for (int i = 0; i < App->gui->GUI_ELEMENTS.count(); i++)
	{
		App->gui->GUI_ELEMENTS[i]->CleanUp();
	}

	RELEASE(Win_Scene_UI);




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


void WinScene::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{
	if (FinishedPosition == true) {
		if (element == ReturnVictorious && type == GUI_Event::EVENT_ONCLICK)
		{
			Mix_HaltMusic();
			if (App->audio->PlayingMenuMusic != true) {
				App->audio->PlayMusic("audio/music/music_scene_mainMenu.ogg");
				App->audio->PlayingMenuMusic = true;
			}
			App->audio->PlayingWinMusic = false;
			App->entities->CleanUp();
			App->transition_manager->CreateSlide(SCENES::MENU_SCENE, 0.5f, true);
		}
	}
}





void WinScene::ExecuteTransition()
{
	
}

