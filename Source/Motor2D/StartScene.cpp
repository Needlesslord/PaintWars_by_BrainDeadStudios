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
	FinishedPosition = false;
	ResetPosition = true;
	App->scenes->IN_GAME_SCENE = false;

	backgroundImage = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0, 0 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes,TEXTURE::MAIN_IMAGE, FONT::FONT_MEDIUM, 1);

	//if(saved_game)
	//else
		//blocked button continue
	continueButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 475, 100 }, { 30,25 }, true, true, { 0, 0, 263, 91 }, "CONTINUE", App->scenes, TEXTURE::ATLAS);

	forestButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 485, 230 }, { 60,20 }, true, true, { 0, 334, 234, 79 }, "Forest", App->scenes, TEXTURE::ATLAS);
	forestButton->hover_rect = { 263, 334, 234, 79 };
	forestButton->click_rect = { 525, 334, 234, 79 };

	snowButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 485, 340 }, { 60,20 }, true, true, { 0, 334, 234, 79 }, "Snow", App->scenes,  TEXTURE::ATLAS);
	snowButton->hover_rect = { 263, 334, 234, 79 };
	snowButton->click_rect = { 525, 334, 234, 79 };

	volcanoButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 485, 450 }, { 20,20 }, true, true, { 0, 334, 234, 79 }, "Volcano", App->scenes, TEXTURE::ATLAS);
	volcanoButton->hover_rect = { 263, 334, 234, 79 };
	volcanoButton->click_rect = { 525, 334, 234, 79 };

	backButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 505, 570 }, { 50,15 }, true, true, { 0, 658, 207, 71 }, "BACK", App->scenes, TEXTURE::ATLAS);
	backButton->hover_rect = { 263, 658, 207, 71 };
	backButton->click_rect = { 525, 658, 207, 71 };
	



	//LOADING

	
	/*if (App->audio->PlayingMenuMusic != true) {
		App->audio->PlayMusic("audio/music/music_scene_mainMenu.ogg");
		App->audio->PlayingMenuMusic = true;
	}*/

	return ret;
}

// Called each loop iteration
bool StartScene::PreUpdate()
{
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	bool ret = true;

	if (ResetPosition == true) {
		continueButton->map_position.x = -300;
		continueButton->label->map_position.x = -275;
		forestButton->map_position.x = 1300;
		forestButton->label->map_position.x = 1335;
		snowButton->map_position.x = -300;
		snowButton->label->map_position.x = -245;
		volcanoButton->map_position.x = 1300;
		volcanoButton->label->map_position.x = 1300;
		backButton->map_position.x = -300;
		backButton->label->map_position.x = -250;
		ResetPosition = false;
	}

	return ret;
}

// Called each loop iteration
bool StartScene::Update(float dt)
{
	bool ret = true;

	CameraDebugMovement(dt);

	/*if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->scenes->SwitchScene(SCENES::GAME_SCENE);
	}*/




	//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//{
	//	App->scenes->SwitchScene(SCENES::START_SCENE);
	//}

	if (continueButton->map_position.x < 475 && App->transition_manager->is_transitioning == false) {
		continueButton->map_position = continueButton->map_position = { continueButton->map_position.x + 7,continueButton->map_position.y };
	}
	if (continueButton->label->map_position.x < 475 && App->transition_manager->is_transitioning == false) {
		continueButton->label->map_position = continueButton->label->map_position = { continueButton->label->map_position.x + 7,continueButton->label->map_position.y };
	}
	//--
	if (forestButton->map_position.x > 490 && App->transition_manager->is_transitioning == false) {
		forestButton->map_position = forestButton->map_position = { forestButton->map_position.x - 7,forestButton->map_position.y };
	}
	if (forestButton->label->map_position.x > 490 && App->transition_manager->is_transitioning == false) {
		forestButton->label->map_position = forestButton->label->map_position = { forestButton->label->map_position.x - 7,forestButton->label->map_position.y };
	}

	if (snowButton->map_position.x < 490 && App->transition_manager->is_transitioning == false) {
		snowButton->map_position = snowButton->map_position = { snowButton->map_position.x + 7,snowButton->map_position.y };
	}
	if (snowButton->label->map_position.x < 490 && App->transition_manager->is_transitioning == false) {
		snowButton->label->map_position = snowButton->label->map_position = { snowButton->label->map_position.x + 7,snowButton->label->map_position.y };
	}
	//--
	if (volcanoButton->map_position.x > 490 && App->transition_manager->is_transitioning == false) {
		volcanoButton->map_position = volcanoButton->map_position = { volcanoButton->map_position.x - 7,volcanoButton->map_position.y };
	}
	if (volcanoButton->label->map_position.x > 490 && App->transition_manager->is_transitioning == false) {
		volcanoButton->label->map_position = volcanoButton->label->map_position = { volcanoButton->label->map_position.x - 7,volcanoButton->label->map_position.y };
	}

	if (backButton->map_position.x < 505 && App->transition_manager->is_transitioning == false) {
		backButton->map_position = backButton->map_position = { backButton->map_position.x + 7,backButton->map_position.y };
	}
	if (backButton->label->map_position.x < 505 && App->transition_manager->is_transitioning == false) {
		backButton->label->map_position = backButton->label->map_position = { backButton->label->map_position.x + 7,backButton->label->map_position.y };
		
	}
	else if (App->transition_manager->is_transitioning == false) {
		FinishedPosition = true; //ONLY ONE CHANGE TO TRUE IS NEEDED BECAUSE ALL BUTTONS GET TO THEIR POSITION AT THE SAME MOMENT
	}


	if (App->canContinue == false)
	{
		continueButton->rect = { 0, 730, 263, 91 };
		continueButton->hover_rect = { 0, 730, 263, 91 };
		continueButton->click_rect = { 0, 730, 263, 91 };
		continueButton->interactable = false;
	}
	else if (App->canContinue == true)
	{
		continueButton->rect = { 0, 0, 263, 91 };
		continueButton->hover_rect = { 263, 0, 263, 91 };
		continueButton->click_rect = { 526, 0, 263, 91 };
		continueButton->interactable = true;
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
	App->gui->CleanUp();
	App->gui->CleanUp(); //WE NEED THIS IN EACH CLEANUP

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

	LOG("START SCENE CleanUP");


	return ret;
}


void StartScene::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{

	if (FinishedPosition==true) {
		if (element == backButton && type == GUI_Event::EVENT_ONCLICK)
		{

			App->transition_manager->CreateSlide(SCENES::MENU_SCENE, 0.5f, true);

		}

		if (element == continueButton && type == GUI_Event::EVENT_ONCLICK)
		{
			App->LoadGame();

			if (App->scenes->WhichMapToLoad == "forest"){
				App->scenes->Load_Map_Forest = true;
				App->scenes->Load_Map_Snow = false;
				App->scenes->Load_Map_Volcano = false;
			}
			else if (App->scenes->WhichMapToLoad == "snow") {
				App->scenes->Load_Map_Snow = true;
				App->scenes->Load_Map_Forest = false;
				App->scenes->Load_Map_Volcano = false;
			}
			else if (App->scenes->WhichMapToLoad == "volcano") {
				App->scenes->Load_Map_Volcano = true;
				App->scenes->Load_Map_Forest = false;
				App->scenes->Load_Map_Snow = false;
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
}





void StartScene::ExecuteTransition()
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
		
	}
}
