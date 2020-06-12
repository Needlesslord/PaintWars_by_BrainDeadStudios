#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1UI_manager.h"
#include "j1SceneManager.h"
#include "j1Audio.h"
#include "SettingsScene.h"
#include "TransitionManager.h"
#include "j1Player.h"
#include "SDL_mixer\include\SDL_mixer.h"

SettingsScene::SettingsScene() : Scene(SCENES::SETTINGS_SCENE)
{

}

// Destructor
SettingsScene::~SettingsScene()
{

}

// Called before render is available
bool SettingsScene::Awake(pugi::xml_node& config)
{
	LOG("Loading MenuScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SettingsScene::Start()
{

	bool ret = true;


	FinishedPosition = false;
	ResetPosition = true;

	App->scenes->IN_GAME_SCENE = false;
	backgroundImage = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0, 0 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes,TEXTURE::MAIN_IMAGE);

	musicLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 150 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "Music", App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM_WHITE, 6);

	vfxLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 250 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "FX", App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM_WHITE, 6);

	fullscreenLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 350 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "Fullscreen", App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM_WHITE, 6);

	mutelabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 450 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "Mute", App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM_WHITE, 6);

	////
	fxBar= App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 620, 255 }, { 0,0 }, true, true, { 785, 57, 268, 26 }, nullptr, App->scenes, TEXTURE::ATLAS);
	fxBar->hover_rect = { 785, 57, 268, 26 };
	fxBar->click_rect = { 785, 57, 268, 26 };
	musicBar= App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 620, 160 }, { 0,0 }, true, true, { 785, 57, 268, 26 }, nullptr, App->scenes, TEXTURE::ATLAS);
	musicBar->click_rect = { 785, 57, 268, 26 };
	musicBar->hover_rect = { 785, 57, 268, 26 };

	musicSlider = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 732, 157 }, { 0,0 }, true, true, { 786, 1, 42, 34 }, nullptr, App->scenes, TEXTURE::ATLAS);
	musicSlider->hover_rect = { 786, 1, 42, 34 };
	musicSlider->click_rect = { 786, 1, 42, 34 };

	fxSlider = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 732, 252 }, { 0,0 }, true, true, { 786, 1, 42, 34 }, nullptr, App->scenes, TEXTURE::ATLAS);
	fxSlider->hover_rect = { 786, 1, 42, 34 };
	fxSlider->click_rect = { 786, 1, 42, 34 };
	/////

	fullscreenButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 700, 350 }, { 0,0 }, true, true, { 0, 1031, 182, 58 }, nullptr, App->scenes, TEXTURE::ATLAS);
	fullscreenButton->hover_rect = { 0, 1031, 182, 58 };
	fullscreenButton->click_rect = { 0, 1031, 182, 58 };

	mutebutton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 620, 450 }, { 0,0 }, true, true, { 0, 1031, 182, 58 }, nullptr, App->scenes, TEXTURE::ATLAS);
	mutebutton->hover_rect = { 0, 1031, 182, 58 };
	mutebutton->click_rect = { 0, 1031, 182, 58 };

	
	resetButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 500, 550 }, { 30,15 }, true, true, { 0, 658, 207, 71 },"Reset", App->scenes, TEXTURE::ATLAS);
	resetButton->hover_rect = { 263, 658, 207, 71 };
	resetButton->click_rect = { 525, 658, 207, 71 };

	backButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 900, 630 }, { 50,15 }, true, true, { 0, 658, 207, 71 }, "BACK", App->scenes, TEXTURE::ATLAS);
	backButton->hover_rect = { 263, 658, 207, 71 };
	backButton->click_rect = { 525, 658, 207, 71 };


	if (App->audio->PlayingSettingsMusic != true) {
		App->audio->PlayMusic("audio/music/music_scene_settings.ogg");
		App->audio->PlayingSettingsMusic = true;
	}


	return ret;
}

// Called each loop iteration
bool SettingsScene::PreUpdate()
{
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	bool ret = true;
	if (ResetPosition == true) {
		musicLabel->map_position.x = -300;
		vfxLabel->map_position.x = -300;
		fullscreenLabel->map_position.x = -300;
		mutelabel->map_position.x = -300;
		resetButton->label->map_position.x = -300;
		fxBar->map_position.x = 1300;
		musicBar->map_position.x = 1300;
		fxSlider->map_position.x = 1300;
		musicSlider->map_position.x = 1300;
		backButton->map_position.x = 1300;
		fullscreenButton->map_position.x = 1300;
		mutebutton->map_position.x = 1300;
		resetButton->map_position.x = 1300;
		backButton->map_position.x = 1300;
		
		ResetPosition = false;
	}
	return ret;
}

// Called each loop iteration
bool SettingsScene::Update(float dt)
{
	bool ret = true;
	
	CameraDebugMovement(dt);

	/*if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->scenes->SwitchScene(SCENES::MENU_SCENE);
	}*/


	if (FinishedPosition != true) {

		if (musicLabel->map_position.x < 300 && App->transition_manager->is_transitioning == false) {
			musicLabel->map_position = musicLabel->map_position = { musicLabel->map_position.x + 7,musicLabel->map_position.y };
		}
		//--
		if (vfxLabel->map_position.x < 300 && App->transition_manager->is_transitioning == false) {
			vfxLabel->map_position = vfxLabel->map_position = { vfxLabel->map_position.x + 7,vfxLabel->map_position.y };
		}
		if (fullscreenLabel->map_position.x < 300 && App->transition_manager->is_transitioning == false) {
			fullscreenLabel->map_position = fullscreenLabel->map_position = { fullscreenLabel->map_position.x + 7,fullscreenLabel->map_position.y };
		}



		if (mutelabel->map_position.x < 300 && App->transition_manager->is_transitioning == false) {
			mutelabel->map_position = mutelabel->map_position = { mutelabel->map_position.x + 7,mutelabel->map_position.y };
		}
		if (fxBar->map_position.x > 620 && App->transition_manager->is_transitioning == false) {
			fxBar->map_position = fxBar->map_position = { fxBar->map_position.x - 7,fxBar->map_position.y };
		}
		//--
		if (musicBar->map_position.x > 620 && App->transition_manager->is_transitioning == false) {
			musicBar->map_position = musicBar->map_position = { musicBar->map_position.x - 7,musicBar->map_position.y };
		}
		if (musicSlider->map_position.x > 732 && App->transition_manager->is_transitioning == false) {
			musicSlider->map_position = musicSlider->map_position = { musicSlider->map_position.x - 7,musicSlider->map_position.y };
		}

		if (fxSlider->map_position.x > 732 && App->transition_manager->is_transitioning == false) {
			fxSlider->map_position = fxSlider->map_position = { fxSlider->map_position.x - 7,fxSlider->map_position.y };
		}
		if (fullscreenButton->map_position.x > 700 && App->transition_manager->is_transitioning == false) {
			fullscreenButton->map_position = fullscreenButton->map_position = { fullscreenButton->map_position.x - 7,fullscreenButton->map_position.y };

		}
		if (mutebutton->map_position.x > 700 && App->transition_manager->is_transitioning == false) {
			mutebutton->map_position = mutebutton->map_position = { mutebutton->map_position.x - 7,mutebutton->map_position.y };

		}

		if (resetButton->map_position.x > 500 && App->transition_manager->is_transitioning == false) {
			resetButton->map_position = resetButton->map_position = { resetButton->map_position.x - 7,resetButton->map_position.y };

		}
		if (backButton->map_position.x > 900 && App->transition_manager->is_transitioning == false) {
			backButton->map_position = backButton->map_position = { backButton->map_position.x - 7,backButton->map_position.y };

		}
		if (resetButton->label->map_position.x < 500 && App->transition_manager->is_transitioning == false) {
			resetButton->label->map_position = resetButton->label->map_position = { resetButton->label->map_position.x + 7,resetButton->label->map_position.y };
		}
		else if (App->transition_manager->is_transitioning == false) {
			FinishedPosition = true; //ONLY ONE CHANGE TO TRUE IS NEEDED BECAUSE ALL BUTTONS GET TO THEIR POSITION AT THE SAME MOMENT
		}
	}





	return ret;
}

// Called each loop iteration
bool SettingsScene::PostUpdate()
{
	App->player->Mouse_Cursor();
	bool ret = true;

	if ( exit)
		ret = false;

	//ExecuteTransition();

	return ret;
}

// Called before quitting
bool SettingsScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	App->gui->CleanUp();
	musicLabel->CleanUp();
	vfxLabel->CleanUp();
	fullscreenLabel->CleanUp();
	mutelabel->CleanUp();
	
	fullscreenButton->CleanUp();
	mutebutton->CleanUp();
	resetButton->CleanUp();
	backButton->CleanUp();
	backgroundImage->CleanUp();

	musicBar->CleanUp();
	fxBar->CleanUp();
	musicSlider->CleanUp();
	fxSlider->CleanUp();



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


void SettingsScene::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{
	if (element == backButton && type == GUI_Event::EVENT_ONCLICK)
	{
		
		App->transition_manager->CreateSlide(SCENES::MENU_SCENE, 0.5f, true);
	}

	if (element == fullscreenButton && type == GUI_Event::EVENT_ONCLICK)
	{
		if (!App->win->fullscreen)
		{
			fullscreenButton->rect = { 0, 973, 182, 58 };
			fullscreenButton->hover_rect = { 0, 973, 182, 58 };
			fullscreenButton->click_rect = { 0, 973, 182, 58 };
		}

		if (App->win->fullscreen)
		{
			fullscreenButton->rect = { 0, 1031, 182, 58 };
			fullscreenButton->hover_rect = { 0, 1031, 182, 58 };
			fullscreenButton->click_rect = { 0, 1031, 182, 58 };
		}


		App->win->Fullscreen_Swap();
	}

	//SLIDERS

	
		/*if (element == fxBar && type == GUI_Event::EVENT_ONCLICK) {

			fPoint MousePos = App->input->GetMouseWorldPosition();

			fxSlider->map_position.x = (MousePos.x / 2) - 10;
		}*/

		if (FinishedPosition == true) {

			if (element == fxBar && type == GUI_Event::EVENT_HOVER) {

				//CHUNKS VOLUME SHOULD BE DIFFERENT
				fPoint MousePos = App->input->GetMouseWorldPosition();

				fxSlider->map_position.x = (MousePos.x / 2) - 10;

				//732 611
				if (fxSlider->map_position.x >= 620 && fxSlider->map_position.x <= 650) {
					LOG("VOL FX TO 0");
					App->audio->CurrentFXVolume = 0;
				}

				if (fxSlider->map_position.x >= 651 && fxSlider->map_position.x <= 680) {
					LOG("VOL FX TO 1");
					App->audio->CurrentFXVolume = 4;
				}

				if (fxSlider->map_position.x >= 681 && fxSlider->map_position.x <= 710) {
					LOG("VOL  FX TO 2");

					App->audio->CurrentFXVolume = 8;
				}

				if (fxSlider->map_position.x >= 741 && fxSlider->map_position.x <= 770) {
					LOG("VOL  FXTO 3");
					App->audio->CurrentFXVolume = 12;

				}
				if (fxSlider->map_position.x >= 771 && fxSlider->map_position.x <= 800) {
					LOG("VOL FX TO 4");
					App->audio->CurrentFXVolume = 16;

				}
				if (fxSlider->map_position.x >= 801) {
					LOG("VOL FXTO 5");
					App->audio->CurrentFXVolume = 20;
				}


				App->audio->ChunkAudioManager(App->audio->CurrentFXVolume); //SHOULD WE SET ALL CHUNK VOLUMES TO THE SAME VALUE OR DIFFERENT FOR EACH CHUNK?

			}

			if (element == musicBar && type == GUI_Event::EVENT_HOVER) {

				fPoint MousePos = App->input->GetMouseWorldPosition();

				musicSlider->map_position.x = (MousePos.x / 2) - 10;

				//732 611
				if (musicSlider->map_position.x >= 620 && musicSlider->map_position.x <= 650) {
					LOG("VOL MUS TO 0");
					App->audio->CurrentMusVolume = 0;
				}

				if (musicSlider->map_position.x >= 651 && musicSlider->map_position.x <= 680) {
					LOG("VOL MUS TO 1");
					App->audio->CurrentMusVolume = 2;
				}

				if (musicSlider->map_position.x >= 681 && musicSlider->map_position.x <= 710) {
					LOG("VOL MUS TO 2");
					App->audio->CurrentMusVolume = 4;
				}

				if (musicSlider->map_position.x >= 741 && musicSlider->map_position.x <= 770) {
					LOG("VOL MUS TO 3");
					App->audio->CurrentMusVolume = 6;
				}
				if (musicSlider->map_position.x >= 771 && musicSlider->map_position.x <= 800) {
					LOG("VOL MUS TO 4");
					App->audio->CurrentMusVolume = 8;
				}
				if (musicSlider->map_position.x >= 801) {
					LOG("VOL MUS TO 5");
					App->audio->CurrentMusVolume = 10;
				}

				Mix_VolumeMusic(App->audio->CurrentMusVolume);
			}


		}
		
}




void SettingsScene::ExecuteTransition()
{
	if (!App->transition_manager->is_transitioning)
	{
	/*	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
		{
			App->transition_manager->CreateCut(SCENES::GAME_SCENE);
		}*/

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			App->transition_manager->CreateFadeToColour(SCENES::GAME_SCENE);
		}

	
    }
}
