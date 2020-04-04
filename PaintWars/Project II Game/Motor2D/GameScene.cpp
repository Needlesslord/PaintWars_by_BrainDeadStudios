#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1SceneManager.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "GameScene.h"
#include "TransitionManager.h"
//#include "j1Transition.h"
//#include "j1TransitionManager.h"

GameScene::GameScene() : Scene(SCENES::GAME_SCENE)
{

}

// Destructor
GameScene::~GameScene()
{

}

// Called before render is available
bool GameScene::Awake(pugi::xml_node& config)
{
	LOG("Loading FirstScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool GameScene::Start()
{
	bool ret = true;
	
	debug_tex = App->tex->Load("maps/path2.png");

	//THESE BOOLS HAVE TO BE REMOVED ONCE WE HAVE THE MAIN MENU, BECAUSE WE WANT THE GAME TO LOAD THE MAP AFTER WE USE THE PLAY BUTTON NOT WHILE WE ARE IN THE MENU
	Load_Forest_Map = true;
	Change_Map = true;
	Map_Manager();
	App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL,	{    0,  100 }, { 100, 100 }, App->entities, 10);
	App->entities->AddEntity(ENTITY_TYPE_PAINTER,	{  200,  200 }, {  20,  20 }, App->entities, 5);

	App->entities->AddEntity(ENTITY_TYPE_WARRIOR,	{  400,  400 }, {  62, 118 }, App->entities, 10);
	App->entities->AddEntity(ENTITY_TYPE_WARRIOR,	{  700,  600 }, {  62, 118 }, App->entities);
	App->entities->AddEntity(ENTITY_TYPE_WARRIOR,	{ 1000,  800 }, {  62, 118 }, App->entities);

	App->entities->AddEntity(ENTITY_TYPE_SLIME,		{  600,  200 }, {  20,  20 }, App->entities);
	App->entities->AddEntity(ENTITY_TYPE_SPAWNER,	{ 1000, 1000 }, {  20,  20 }, App->entities);
	

	int w, h;
	uchar* data = NULL;
	if (App->map->CreateWalkabilityMap(w, h, &data))
	{
		App->pathfinding->SetMap(w, h, data);						// Sets a new walkability map with the map passed by CreateWalkabilityMap().
	}

	//App->pathfinding->ChangeWalkability({ 7, 0 }, false);
	//App->pathfinding->ChangeWalkability({ 7, 1 }, false);
	//App->pathfinding->ChangeWalkability({ 7, 2 }, false);
	//App->pathfinding->ChangeWalkability({ 7, 3 }, false);


	return ret;
}

// Called each loop iteration
bool GameScene::PreUpdate()
{
	bool ret = true;



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



	// Debug pathfinding ------------------
	static iPoint origin;
	static bool origin_selected = false;

	fPoint mouseWP = App->input->GetMouseWorldPosition();
	iPoint p = App->map->WorldToMap(mouseWP.x, mouseWP.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (origin_selected == true)
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



	return ret;
}

// Called each loop iteration
bool GameScene::Update(float dt)
{
	bool ret = true;
	
	CameraDebugMovement(dt);

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
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

	fPoint xy = App->input->GetMouseWorldPosition();
	iPoint cameraW = App->map->WorldToMap(App->render->camera.x, App->render->camera.y);
	iPoint map_coordinates = App->map->WorldToMap(xy.x - cameraW.x /*+ App->map->data.tile_width / 2*/, xy.y - cameraW.y + App->map->data.tile_height/2);

	static char title[256];
	sprintf_s(title, 256, "Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d,",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.size(),
		map_coordinates.x, map_coordinates.y);

	App->win->SetTitle(title);


	/*p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d, %d, %d",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.size(),
		map_coordinates.x, map_coordinates.y, map_coordinates2.x, map_coordinates2.y);

	App->win->SetTitle(title.GetString());*/
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		debugTile = !debugTile;
	}
	// Debug pathfinding ------------------------------
	if (debugTile) {
		fPoint c = App->map->MapToWorld(map_coordinates.x, map_coordinates.y);
		App->render->AddBlitEvent(1, debug_tex, c.x, c.y, { 0,0,150,75 });
	}
	return ret;
}

// Called each loop iteration
bool GameScene::PostUpdate()
{
	bool ret = true;
	
	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {
		Change_Map = true;
		Load_Snow_Map = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	ExecuteTransition();

	return ret;
}

// Called before quitting
bool GameScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	App->map->CleanUp();

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

	App->tex->UnLoad(debug_tex);

	return ret;
}

void GameScene::InitScene()
{
	//tileset_texture = App->tex->Load("maps/tiles_first_map.png", scene_renderer);	// This texture will be used SceneToTexture(). Needed to get a single whole texture of the map.

	App->map->Load("map_forest.tmx") == true;
	Create_Forest_Map();
	//App->map->GetMapSize(map_width, map_height);
	//App->map->GetTileOffset(x_offset, y_offset);
	
	//App->render->camera.x = map_width * 0.3f;										// This camera position gets the camera close to the center of the map.
	//App->render->camera.y = -40;

	// --- TRANSITIONS WITH TEXTURE
	/*App->render->camera.x = map_width * 0.5f;										// This camera position is to have the renderer render all the scene_texture.
	App->render->camera.y = 0;

	SceneToTexture();

	App->render->camera.x = map_width * 0.3f;										// This camera position gets the camera close to the center of the map.
	App->render->camera.y = -40;*/
}

void GameScene::DrawScene()
{
	App->map->Draw();


	// --- TRANSITIONS WITH TEXTURE
	/*if (scene_texture != nullptr)
	{
		App->render->Blit(scene_texture, -(map_width) * 0.5f, 0, NULL);
	}*/	
}

void GameScene::Map_Manager() {
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

void GameScene::Create_Forest_Map()
{

	App->map->CleanUp();
	App->map->Load("map_forest.tmx") == true;

	Change_Map = false;
	Forest_Map_Active = true;
	Load_Forest_Map = false;
}

void GameScene::Create_Snow_Map()
{
	App->map->CleanUp();
	App->map->Load("map_snow.tmx") == true;

	App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { -200, 300 }, { 100, 100 }, App->entities, 10); //TESTING ONLY

	Change_Map = false;
	Snow_Map_Active = true;
	Load_Snow_Map = false;
}

void GameScene::Create_Volcano_Map()
{
	App->map->CleanUp();
	App->map->Load("map_forest.tmx") == true;


	Change_Map = false;
	Volcano_Map_Active = true;
	Load_Volcano_Map = false;
}


//SDL_Texture* FirstScene::SceneToTexture()
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

void GameScene::ExecuteTransition()
{
	if (!App->transition_manager->is_transitioning)
	{
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			App->transition_manager->CreateCut(SCENES::MENU_SCENE);
		}

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			App->transition_manager->CreateFadeToColour(SCENES::MENU_SCENE);
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