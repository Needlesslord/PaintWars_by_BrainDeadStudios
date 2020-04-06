#include "Scene.h"
#include "j1Render.h"
#include "j1Input.h"

Scene::Scene(SCENES scene_name) : scene_name(scene_name)
, scene_surface(nullptr)
, scene_renderer(nullptr)
, scene_texture(nullptr)
, tileset_texture(nullptr)
{

}

Scene::~Scene()
{

}

bool Scene::Awake(pugi::xml_node& config)
{
	return true;
}

bool Scene::Start()
{
	return true;
}

bool Scene::PreUpdate()
{
	return true;
}

bool Scene::Update(float dt)
{
	return true;
}

bool Scene::PostUpdate()
{
	return true;
}

bool Scene::CleanUp()
{
	return true;
}

void Scene::InitScene()
{

}

void Scene::DrawScene()
{

}

SDL_Texture* Scene::SceneToTexture()
{
	SDL_Texture* ret = nullptr;

	return ret;
}

void Scene::GUI_Event_Manager(GUI_Event type, j1Element* element)
{

}

void Scene::ExecuteTransition()
{

}

void Scene::CameraDebugMovement(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		App->render->camera.y += floor(500.0f * dt);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		App->render->camera.y -= floor(500.0f * dt);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		App->render->camera.x += floor(500.0f * dt);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		App->render->camera.x -= floor(500.0f * dt);
	}
}