#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1EntityManager.h"
#include "j1Scene.h"
#include "j1GUI.h"
#include "j1Collision.h"


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start() {

	App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, {   0, 100 }, App->entities, 10);
	App->entities->AddEntity(ENTITY_TYPE_PAINTER,	{ 200, 200 }, App->entities,  5);
	App->entities->AddEntity(ENTITY_TYPE_WARRIOR,	{ 400, 200 }, App->entities, 10);
	App->entities->AddEntity(ENTITY_TYPE_SLIME,		{ 600, 200 }, App->entities);

	App->map->Load("map_forest.tmx") == true;

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate() {

	// Debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			//App->pathfinding->CreatePath(origin, p);                  CRASHES WITH THE NEW PATHFINDING
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt) {
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
		int a, b;
		App->input->GetMousePosition(a, b);
		float c, d;
		c = a;
		d = b;
		
		App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { c, d }, App->entities);
	}

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		int a, b;
		App->input->GetMousePosition(a, b);
		float c, d;
		c = a;
		d = b;

		App->entities->AddEntity(ENTITY_TYPE_PAINTER, { c, d }, App->entities);
	}

	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	iPoint trying = App->render->ScreenToWorld(x,y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d, %d, %d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y, trying.x, trying.y);

	App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	//App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		//App->render->AddBlitEvent(0,debug_tex, pos.x, pos.y);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

