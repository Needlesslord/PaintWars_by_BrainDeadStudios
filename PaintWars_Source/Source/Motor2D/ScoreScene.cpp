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
#include "ScoreScene.h"
#include "TransitionManager.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "j1Audio.h"
#include "j1Player.h"

ScoreScene::ScoreScene() : Scene(SCENES::SCORE_SCENE)
{

}

// Destructor
ScoreScene::~ScoreScene()
{

}

// Called before render is available
bool ScoreScene::Awake(pugi::xml_node& config)
{
	LOG("Loading Score Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool ScoreScene::Start()
{
	bool ret = true;


	



	BackgroundImage = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0, 0 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes, TEXTURE::MAIN_IMAGE);
	BackButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 900, 630 }, { 50,15 }, true, true, { 0, 658, 207, 71 }, "BACK", App->scenes, TEXTURE::ATLAS);
	BackButton->hover_rect = { 263, 658, 207, 71 };
	BackButton->click_rect = { 525, 658, 207, 71 };

	ScoreTextLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, BackgroundImage, { 500 , 100 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "Last Score", nullptr, TEXTURE::ATLAS, FONT::FONT_MEDIUM);

	ScoreLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 500, 500 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "SCORE AMOUNT");

	
	if (App->audio->PlayingLogoMusic != true) {
		App->audio->PlayingLogoMusic = false;
		App->audio->PlayMusic("audio/music/music_scene_paintwars.ogg");
		App->audio->PlayingLogoMusic = true;
	}

	static char conversorCharTimer[256];
	int Sec_Conversor = App->scenes->Timer_Seconds;
	int Min_Conversor = App->scenes->Timer_Minutes;
	sprintf_s(conversorCharTimer, 256, "%d/%d", Min_Conversor, Sec_Conversor);
	ScoreLabel->text = conversorCharTimer;

	return ret;
}

// Called each loop iteration
bool ScoreScene::PreUpdate()
{
	bool ret = true;

	return ret;
}

// Called each loop iteration
bool ScoreScene::Update(float dt)
{
	bool ret = true;

	CameraDebugMovement(dt);

	
	App->player->Mouse_Cursor();



	return ret;
}

// Called each loop iteration
bool ScoreScene::PostUpdate()
{
	bool ret = true;

	if (exit)
		ret = false;

	//ExecuteTransition();

	return ret;
}

// Called before quitting
bool ScoreScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	
	BackButton->CleanUp();
	ScoreTextLabel->CleanUp();
	ScoreLabel->CleanUp();

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


void ScoreScene::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{
	if (element == BackButton && type == GUI_Event::EVENT_ONCLICK)
	{
		//Mix_PlayChannel(-1, App->audio->Click_Logo_Sound, 0);  /*Mix_VolumeChunk(Click_Logo_Sound, 50);*/

		App->transition_manager->CreateAlternatingBars(SCENES::MENU_SCENE);

	}
}




void ScoreScene::ExecuteTransition()
{
	
}
