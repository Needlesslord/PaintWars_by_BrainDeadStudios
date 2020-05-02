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

	Loading_1 = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 500, 300 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes, TEXTURE::MAIN_IMAGE, FONT::FONT_MEDIUM, 1);
	Loading_2 = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 500, 400 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes, TEXTURE::MAIN_IMAGE, FONT::FONT_MEDIUM, 1);
	Loading_3 = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 500, 500 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes, TEXTURE::MAIN_IMAGE, FONT::FONT_MEDIUM, 1);

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
		//App->scenes->SwitchScene(SCENES::MENU_SCENE);
		App->transition_manager->CreateSlide(SCENES::MENU_SCENE, 0.5f, true);

	}

	if (element == continueButton && type == GUI_Event::EVENT_ONCLICK)
	{
		//App->scenes->SwitchScene(SCENES::GAME_SCENE);
		//App->transition_manager->CreateFadeToColour(SCENES::GAME_SCENE);
		App->transition_manager->CreateSlide(SCENES::GAME_SCENE, 0.5f, true);
	}

	if ((element == snowButton || element == forestButton || element == volcanoButton) && type == GUI_Event::EVENT_ONCLICK)
	{
		//App->scenes->SwitchScene(SCENES::GAME_SCENE);
		App->transition_manager->CreateSlide(SCENES::GAME_SCENE, 0.5f, true);
	}
}

//void MenuScene::InitScene()
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

//void MenuScene::DrawScene()
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

		//	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateSlide(SCENES::SECOND_SCENE, 0.5f, true);
		//	}

		//	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateSlide(SCENES::SECOND_SCENE, 0.5f, true, true);
		//	}

		//	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 0.5f, true);
		//	}

		//	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 0.5f, true, true);
		//	}

		//	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateAlternatingBars(SCENES::SECOND_SCENE, 0.5f, true);
		//	}

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
