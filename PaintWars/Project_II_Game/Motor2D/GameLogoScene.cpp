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
#include "GameLogoScene.h"
#include "TransitionManager.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "j1Audio.h"

GameLogoScene::GameLogoScene() : Scene(SCENES::GAME_LOGO_SCENE)
{

}

// Destructor
GameLogoScene::~GameLogoScene()
{

}

// Called before render is available
bool GameLogoScene::Awake(pugi::xml_node& config)
{
	LOG("Loading GameLogoScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool GameLogoScene::Start()
{
	bool ret = true;

	gameLogoButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 300, 100 }, { 0,500 }, true, true, { 0, 0, 630, 426 }, "Click on the Logo to Start!", App->scenes, TEXTURE::LOGO, FONT::FONT_MEDIUM_WHITE, 1);
	gameLogoButton->hover_rect = { 0, 0, 630, 426 };
	gameLogoButton->click_rect = { 0, 0, 630, 426 };

	if (App->audio->PlayingLogoMusic != true) {
		App->audio->PlayingLogoMusic = false;
		App->audio->PlayMusic("audio/music/logoScene.ogg");
		App->audio->PlayingLogoMusic = true;
	}



	return ret;
}

// Called each loop iteration
bool GameLogoScene::PreUpdate()
{
	bool ret = true;

	return ret;
}

// Called each loop iteration
bool GameLogoScene::Update(float dt)
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
bool GameLogoScene::PostUpdate()
{
	bool ret = true;

	if ( exit)
		ret = false;

	//ExecuteTransition();

	return ret;
}

// Called before quitting
bool GameLogoScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	gameLogoButton->CleanUp();

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


void GameLogoScene::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{
	if (element == gameLogoButton && type == GUI_Event::EVENT_ONCLICK)
	{
		Mix_PlayChannel(-1, App->audio->Click_Logo_Sound, 0);  /*Mix_VolumeChunk(Click_Logo_Sound, 50);*/

		App->transition_manager->CreateAlternatingBars(SCENES::MENU_SCENE);
		
	}
}

//aaaa
//void GameLogoScene::InitScene()
//{
//	tileset_texture = App->tex->Load("maps/tiles_first_map.png", scene_renderer);	// This texture will be used SceneToTexture(). Needed to get a single whole texture of the map.
//
//	App->map->GetMapSize(map_width, map_height);
//	App->map->GetTileOffset(x_offset, y_offset);
//	
//	App->render->camera.x = map_width * 0.3f;										// This camera position gets the camera close to the center of the map.
//	App->render->camera.y = -40;
//
//	// --- TRANSITIONS WITH TEXTURE
//	/*App->render->camera.x = map_width * 0.5f;										// This camera position is to have the renderer render all the scene_texture.
//	App->render->camera.y = 0;
//
//	SceneToTexture();
//
//	App->render->camera.x = map_width * 0.3f;										// This camera position gets the camera close to the center of the map.
//	App->render->camera.y = -40;*/
//}

//void GameLogoScene::DrawScene()
//{
//	App->map->Draw();
//
//
//	// --- TRANSITIONS WITH TEXTURE
//	/*if (scene_texture != nullptr)
//	{
//		App->render->Blit(scene_texture, -(map_width) * 0.5f, 0, NULL);
//	}*/	
//}


//SDL_Texture* MenuScene::SceneToTexture()
//{
//	App->render->CreateSubRenderer(map_width + x_offset, map_height + y_offset, scene_surface, scene_renderer);		// Both scene_surface and scene renderer are passed by reference.
//
//	tileset_texture = App->tex->Load("maps/tiles_first_map.png", scene_renderer);
//	App->map->DrawToSubRenderer(scene_renderer, tileset_texture);
//
//	scene_texture = SDL_CreateTextureFromSurface(App->render->renderer, scene_surface);
//
//	return scene_texture;
//}


void GameLogoScene::ExecuteTransition()
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
