#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1GUI.h"
#include "j1SceneManager.h"
#include "ForestMapScene.h"
#include "TransitionManager.h"

ForestScene::ForestScene() : Scene(SCENES::GAME_SCENE)
{

}

// Destructor
ForestScene::~ForestScene()
{

}

// Called before render is available
bool ForestScene::Awake(pugi::xml_node& config)
{
	LOG("Loading MenuScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool ForestScene::Start()
{
	bool ret = true;

	mainMenuButton = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 350, 70 }, { 0, 0 }, false, true, { 0, 0, 350, 121 }, "Main Menu");

	newGameButton = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 370, 240 }, { 0,0 }, true, true, { 0, 445, 312, 108 }, "New Game", App->scenes);
	newGameButton->hover_tex = { 350, 445, 312, 108 };

	continueButton = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 370, 380 }, { 0,0 }, true, true, { 0, 445, 312, 108 }, "Continue", App->scenes);
	continueButton->hover_tex = { 350, 445, 312, 108 };

	settingsButton = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 370, 520 }, { 0,0 }, true, true, { 0, 445, 312, 108 }, "Settings", App->scenes);
	settingsButton->hover_tex = { 350, 445, 312, 108 };

	exitButton = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 390, 650 }, { 0,0 }, true, true, { 0, 877, 275, 95 }, "EXIT", App->scenes);
	exitButton->hover_tex = { 350, 877, 275, 95 };

	return ret;
}

// Called each loop iteration
bool ForestScene::PreUpdate()
{
	bool ret = true;

	return ret;
}

// Called each loop iteration
bool ForestScene::Update(float dt)
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
bool ForestScene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	//ExecuteTransition();

	return ret;
}

// Called before quitting
bool ForestScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	RELEASE(mainMenuButton);
	RELEASE(newGameButton);
	RELEASE(continueButton);
	RELEASE(settingsButton);
	RELEASE(exitButton);

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


void ForestScene::ExecuteTransition()
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
