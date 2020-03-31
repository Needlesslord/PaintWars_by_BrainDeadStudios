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
#include "j1Player.h"




j1Scene::j1Scene():j1Module()
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

	//THESE BOOLS HAVE TO BE REMOVED ONCE WE HAVE THE MAIN MENU, BECAUSE WE WANT THE GAME TO LOAD THE MAP AFTER WE USE THE PLAY BUTTON NOT WHILE WE ARE IN THE MENU
	Load_Forest_Map = true;
	Change_Map = true;
	Map_Manager();
	App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL,	{    0,  100 }, { 100, 100 }, App->entities, 10);
	App->entities->AddEntity(ENTITY_TYPE_PAINTER,	{  200,  200 }, {  20,  20 }, App->entities, 5);
	App->entities->AddEntity(ENTITY_TYPE_WARRIOR,	{  400,  200 }, {  62, 118 }, App->entities, 10);
	App->entities->AddEntity(ENTITY_TYPE_SLIME,		{  600,  200 }, {  20,  20 }, App->entities);
	App->entities->AddEntity(ENTITY_TYPE_SPAWNER,	{ 1000, 1000 }, {  20,  20 }, App->entities);
	

	int wCACA, hCACA;
	uchar* dataCACA = NULL;
	if (App->map->CreateWalkabilityMap(wCACA, hCACA, &dataCACA))
	{
		App->pathfinding->SetMap(wCACA, hCACA, dataCACA);						// Sets a new walkability map with the map passed by CreateWalkabilityMap().
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate() {
	
	if (Change_Map == true) {
		if (Load_Forest_Map) {
			Create_Forest_Map();
		}
		else if (Load_Volcano_Map) {
			Create_Volcano_Map();
		}
		else if (Load_Snow_Map) {
			Create_Snow_Map();
		}
		else {}
	}




	// Debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	fPoint mouseWP= App->input->GetMouseWorldPosition();
	iPoint p = App->map->WorldToMap(mouseWP.x, mouseWP.y);

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
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
		float a, b;
		App->input->GetMousePosition(a, b);
		fPoint cd = App->render->ScreenToWorld(a, b);
		float c, d;
		c = cd.x;
		d = cd.y;
		
		App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { c, d }, { 100, 100 }, App->entities);
	}

	/*if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
		iPoint mouse_pos = App->input->GetMousePositionWorld();
		
		App->render->camera.x = App->player->mouse_position.x;
		
	}*/

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		float a, b;
		App->input->GetMousePosition(a, b);
		fPoint cd = App->render->ScreenToWorld(a, b);
		float c, d;
		c = cd.x;
		d = cd.y;

		App->entities->AddEntity(ENTITY_TYPE_PAINTER, { c, d }, { 20, 20 }, App->entities);
	}

	App->map->Draw();

	float x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	fPoint map_coordinates2 = App->input->GetMouseWorldPosition();

	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d, %d, %d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.size(),
					map_coordinates.x, map_coordinates.y, map_coordinates2.x, map_coordinates2.y);

	App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//float x, y;


	//App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		fPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		//App->render->AddBlitEvent(0,debug_tex, pos.x, pos.y);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {
		Change_Map = true;
		Load_Snow_Map = true;
	}

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

void j1Scene::Map_Manager(){ 
	////THESE FUNCTION HAS TO BE REMOVED ONCE WE HAVE THE MAIN MENU, BECAUSE WE WANT THE GAME TO LOAD THE MAP AFTER WE USE THE PLAY BUTTON NOT WHILE WE ARE IN THE MENU
	if (Load_Forest_Map) {
		App->map->Load("map_forest.tmx") == true;
		Create_Forest_Map();
	}
	else if (Load_Volcano_Map) {
		App->map->Load("map_forest.tmx") == true;
		Create_Volcano_Map();
	}
	else if (Load_Snow_Map) {
		App->map->Load("map_snow.tmx") == true;
		Create_Snow_Map();
	}
	else {
		LOG("No map has been loaded in the scene");
	}
}

void j1Scene::Create_Forest_Map()
{
	
	App->map->CleanUp();
	App->map->Load("map_forest.tmx") == true;
	
	Change_Map = false;
	Forest_Map_Active = true;
	Load_Forest_Map = false;
}

void j1Scene::Create_Snow_Map()
{
	App->map->CleanUp();
	App->map->Load("map_snow.tmx") == true;

	App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { -200, 300 }, { 100, 100 }, App->entities, 10); //TESTING ONLY

	Change_Map = false;
	Snow_Map_Active = true;
	Load_Snow_Map = false;
}

void j1Scene::Create_Volcano_Map()
{
	App->map->CleanUp();
	App->map->Load("map_forest.tmx") == true;
	
	
	Change_Map = false;
	Volcano_Map_Active = true;
	Load_Volcano_Map = false;
}

