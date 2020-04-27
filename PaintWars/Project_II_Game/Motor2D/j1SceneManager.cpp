#include "j1SceneManager.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "SettingsScene.h"
#include "StartScene.h"
#include "LoseScene.h"
#include "WinScene.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
#include "GameLogoScene.h"
#include "j1Player.h"
#include "TeamLogoScene.h"

j1SceneManager::j1SceneManager() : current_scene(nullptr)
{
	name = "scene_manager";
}

j1SceneManager::~j1SceneManager()
{

}

bool j1SceneManager::Awake(pugi::xml_node& config)
{
	bool ret = true;
	
	ScenePushbacks();
	
	LoadInitialScene();

	current_scene->Awake(config);

	return ret;
}

bool j1SceneManager::Start()
{
	bool ret = true;

	current_scene->Start();

	return ret;
}

bool j1SceneManager::PreUpdate()
{
	bool ret = true;

	current_scene->PreUpdate();

	return ret;
}

bool j1SceneManager::Update(float dt)
{
	bool ret = true;

	current_scene->Update(dt);

	return ret;
}

bool j1SceneManager::PostUpdate()
{
	bool ret = true;

	current_scene->PostUpdate();

	/*if ((App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && current_scene->scene_name != SCENES::GAME_SCENE) || exit)
		ret = false;*/

	return ret;
}

bool j1SceneManager::CleanUp()
{
	bool ret = true;

	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		RELEASE((*item));
	}
	scenes.clear();

	return ret;
}



void j1SceneManager::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{
	current_scene->GUI_Event_Manager(type, element);
}



// -------------- SCENE MANAGEMENT METHODS --------------

void j1SceneManager::SwitchScene(SCENES scene_name)
{	
	current_scene->CleanUp();

	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item)->scene_name == scene_name)
		{
			current_scene = (*item);
		}
	}

	if (current_scene != nullptr)
	{
		current_scene->Start();
	}
}

void j1SceneManager::LoadScene(SCENES scene_name)
{
	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item)->scene_name == scene_name)
		{
			if (next_scene == nullptr)
			{
				next_scene = (*item);
			}
			else
			{
				next_scene->CleanUp();

				next_scene = (*item);
			}
		}
	}

	next_scene->Start();
}

void j1SceneManager::UnloadScene(Scene* scene_to_unload)
{
	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item) == scene_to_unload)
		{
			if ((*item) == current_scene)
			{
				if (next_scene != nullptr)															// Cleaning up current_scene. next_scene is re-assigned to current_scene first.
				{
					Scene* tmp = current_scene;

					current_scene = next_scene;

					next_scene = tmp;

					tmp = nullptr;

					next_scene->CleanUp();

					next_scene = nullptr;
				}
				else
				{
					LOG("UNLOAD SCENE ERROR: Two scenes were not active at the same time.");
				}

				break;
			}
			else
			{
				if (current_scene != nullptr)
				{
					(*item)->CleanUp();

					next_scene = nullptr;
				}
				else
				{
					LOG("UNLOAD SCENE ERROR: Two scenes were not active at the same time.");
				}
				
				break;
			}
		}
	}
}

// ---------------- CREATE SCENE METHODS ----------------

void j1SceneManager::LoadInitialScene()
{
	current_scene = (*scenes.begin());
}

Scene* j1SceneManager::CreateScene(SCENES scene_name)
{
	Scene* item = nullptr;

	switch (scene_name)
	{

	case SCENES::MENU_SCENE:

		item = new MenuScene();

		break;

	case SCENES::GAME_SCENE:

		item = new GameScene();
		
		break;

	case SCENES::SETTINGS_SCENE:

		item = new SettingsScene();

		break;

	case SCENES::START_SCENE:

		item = new StartScene();

		break;

	case SCENES::LOSE_SCENE:
		
		item = new LoseScene();
			
		break;

	case SCENES::WIN_SCENE:
		
		item = new WinScene();
			
		break;

	case SCENES::GAME_LOGO_SCENE:

		item = new GameLogoScene();

		break;

	case SCENES::TEAM_LOGO_SCENE:

		item = new TeamLogoScene();

		break;
	}

	if (item != nullptr)
	{
		scenes.push_back(item);
	}

	return item;
}

void j1SceneManager::ScenePushbacks()
{
	CreateScene(SCENES::TEAM_LOGO_SCENE);
	CreateScene(SCENES::GAME_LOGO_SCENE);
	CreateScene(SCENES::MENU_SCENE);
	CreateScene(SCENES::GAME_SCENE);
	CreateScene(SCENES::SETTINGS_SCENE);
	CreateScene(SCENES::START_SCENE);
	CreateScene(SCENES::LOSE_SCENE);
	CreateScene(SCENES::WIN_SCENE);
}

bool j1SceneManager::Load(pugi::xml_node& save) 
{

	return true;
}

bool j1SceneManager::Save(pugi::xml_node& save) const 
{


	return true;
}