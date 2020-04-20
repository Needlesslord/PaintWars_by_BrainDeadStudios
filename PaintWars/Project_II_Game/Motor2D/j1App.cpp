#include <iostream> 
#include <sstream> 

#include "p2Defs.h"
#include "p2Log.h"

#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1SceneManager.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "j1App.h"
#include "j1Player.h"
#include "j1UI_Manager.h"
#include "j1FontsUI.h"
#include <thread>
#include "TransitionManager.h"
#include "j1SceneManager.h"
#include "j1QuestManager.h"
#include "j1Window.h"

// Constructor
j1App::j1App(int argc, char* args[]) : argc(argc), args(args)
{
	input = new j1Input();
	win = new j1Window();
	render = new j1Render();
	tex = new j1Textures();
	audio = new j1Audio();
	scenes = new j1SceneManager();
	map = new j1Map();
	col = new j1Collision(); 
	entities = new j1EntityManager();
	pathfinding = new j1PathFinding();
	player = new j1Player();
	gui = new j1UI_Manager();
	fonts = new j1FontsUI();
	transition_manager = new TransitionManager();
	quest_manager = new j1QuestManager();
	

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(scenes);
	AddModule(map);
	AddModule(col); 
	AddModule(entities);
	AddModule(pathfinding);
	AddModule(player);
	AddModule(gui);
	AddModule(fonts);
	AddModule(transition_manager);
	AddModule(quest_manager);

	// render last to swap buffer
	AddModule(render);
}

// Destructor
j1App::~j1App()
{
	// release modules
	std::list<j1Module*>::iterator item = modules.end();

	while(item != modules.begin())
	{
		item--;
		RELEASE(*item); 
	
	}

	modules.clear();
}

void j1App::AddModule(j1Module* module)
{
	module->Init();
	modules.push_back(module);
}

// Called before render is available
bool j1App::Awake()
{
	PAUSE_ACTIVE = false;
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	bool ret = false;
		
	config = LoadConfig(config_file);

	if(config.empty() == false)
	{
		// self-config
		ret = true;
		app_config = config.child("app");
		title = (app_config.child("title").child_value());
		organization = (app_config.child("organization").child_value());
	}

	if(ret == true)
	{
		std::list<j1Module*>::iterator item;
		item = modules.begin();

		while(item != modules.end() && ret == true)
		{
			ret = (*item)->Awake(config.child((*item)->name.c_str()));
			item++;
		}
	}

	return ret;
}

// Called before the first frame
bool j1App::Start()
{
	bool ret = true;
	std::list<j1Module*>::iterator item;
	item = modules.begin();

	while(item != modules.end() && ret == true)
	{
		ret = (*item)->Start();
		item++;
	}
	return ret;
}

// Called each loop iteration
bool j1App::Update()
{
	
	

	



	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();


	return ret;
}

// ---------------------------------------------
pugi::xml_node j1App::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = config_file.load_file("config.xml");

	if(result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");

	return ret;
}

// ---------------------------------------------

pugi::xml_node j1App::LoadQuests(pugi::xml_document& file) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = file.load_file("quest_data.xml");

	if (result == NULL)
		LOG("Could not load  xml file <loadxmlfunction> pugi error: %s", result.description());
	else
		ret = file.child("quests");
	LOG("XML LOADED");

	return ret;
}

void j1App::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	
	frame_time.Start();
}

void logsomething(char* something)
{
	LOG(something);
}
// ---------------------------------------------
void j1App::FinishUpdate()
{
	if(want_to_save == true)
		SavegameNow();

	if(want_to_load == true)
		LoadGameNow();

	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	float avg_fps = float(frame_count) / startup_time.ReadSec();
	float seconds_since_startup = startup_time.ReadSec();
	uint32 last_frame_ms = frame_time.Read();
	uint32 frames_on_last_update = prev_last_sec_frame_count;

	static char title[256];
	char* cap = "OFF";
	char* vsync = "OFF";

	if (fpscap)
		cap = "ON";
	else
		cap = "OFF";

	if ((App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN) && framerate_cap > 10)
		framerate_cap -= 10;
	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)
		framerate_cap += 10;
	
	sprintf_s(title, 256, "QR || FPS: %02u / EstFPS: %02u/ Av.FPS: %.2f / Last Frame Ms: %02u / Cap: %s / Vsync: -- / dt: %f",
		frames_on_last_update, framerate_cap, avg_fps, last_frame_ms, cap, dt);

	//App->win->SetTitle(title);

	
	if ((framerate_cap > 0) && fpscap)
	{
		if ((last_frame_ms < (1000 / framerate_cap))) {
			SDL_Delay((1000 / framerate_cap) - last_frame_ms);
		}
	}
}



// Call modules before each loop iteration
bool j1App::PreUpdate()
{
	Debug_Actions();
	bool ret = true;
	std::list<j1Module*>::iterator item;
	item = modules.begin();
	j1Module* pModule = NULL;

	for(item = modules.begin(); item != modules.end() && ret == true; item++)
	{
		pModule = (*item);

		if(pModule->active == false) {
			continue;
		}

		ret = (*item)->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool j1App::DoUpdate()
{
	bool ret = true;
	std::list<j1Module*>::iterator item;
	item = modules.begin();
	j1Module* pModule = NULL;

	for(item = modules.begin(); item != modules.end() && ret == true; item++)
	{
		pModule = (*item);

		if(pModule->active == false) {
			continue;
		}

		ret = (*item)->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool j1App::PostUpdate()
{
	bool ret = true;
	std::list<j1Module*>::iterator item;
	j1Module* pModule = NULL;

	for(item = modules.begin(); item != modules.end() && ret == true; item++)
	{
		pModule = (*item);

		if(pModule->active == false) {
			continue;
		}

		ret = (*item)->PostUpdate();
	}



	return ret;
}

// Called before quitting
bool j1App::CleanUp()
{
	bool ret = true;
	std::list<j1Module*>::iterator item = modules.end();

	while(item != modules.begin() && ret == true)
	{
		item--;
		ret = (*item)->CleanUp();
	}
	return ret;
}

// ---------------------------------------
int j1App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* j1App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* j1App::GetTitle() const
{
	return title.c_str();
}

// ---------------------------------------
float j1App::GetDT() const
{
	return dt;
}

// ---------------------------------------
const char* j1App::GetOrganization() const
{
	return organization.c_str();
}

// Load / Save
void j1App::LoadGame()
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list
	want_to_load = true;
}

// ---------------------------------------
void j1App::SaveGame(const char* file) const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?

	want_to_save = true;
	save_game = (file);
}

// ---------------------------------------
void j1App::GetSaveGames(std::list<std::string>& list_to_fill) const
{
	// need to add functionality to file_system module for this to work
}

bool j1App::LoadGameNow()
{
	bool ret = false;

	load_game = ("save_game.xml");

	pugi::xml_document data;
	pugi::xml_node root;

	pugi::xml_parse_result result = data.load_file(load_game.c_str());

	if (result != NULL)
	{
		LOG("Loading new Game State from %s...", load_game.c_str());

		root = data.child("game_state");

		std::list<j1Module*>::iterator item = modules.begin();
		ret = true;

		while (item != modules.end() && ret == true)
		{
			ret = (*item)->Load(root.child((*item)->name.c_str()));
			item++;
		}

		data.reset();
		if (ret == true)
			LOG("...finished loading");
		else
			LOG("...loading process interrupted with error on module %s", (item != modules.end()) ? (*item)->name.c_str() : "unknown");
	}
	else
		LOG("Could not parse game state xml file %s. pugi error: %s", load_game.c_str(), result.description());

	want_to_load = false;
	return ret;
}

bool j1App::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", save_game.c_str());

	// xml object were we will store all data
	pugi::xml_document data;
	pugi::xml_node root;

	root = data.append_child("game_state");

	std::list<j1Module*>::const_iterator item = modules.begin();

	while (item != modules.end() && ret == true)
	{
		ret = (*item)->Save(root.append_child((*item)->name.c_str()));
		item++;
	}

	if (ret == true)
	{
		data.save_file(save_game.c_str());
		LOG("... finished saving", );
	}
	else
		LOG("Save process halted from an error in module %s", (item != modules.end()) ? (*item)->name.c_str() : "unknown");

	//data.reset();   AQUESTA MERDA D'AQUI FEIA QUE NO GUARDES
	want_to_save = false;
	return ret;
}

void j1App::Debug_Actions()
{
	if (GOD_MODE != true) {

		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
			App->transition_manager->CreateFadeToColour(SCENES::GAME_SCENE);
			//App->scenes->SwitchScene(SCENES::GAME_SCENE);
		}

		if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
			if (!PAUSE_ACTIVE) {
				PAUSE_ACTIVE = true;
			}
			else {
				PAUSE_ACTIVE = false;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) { //has to be changed to snow map when developed
			App->transition_manager->CreateSlide(SCENES::GAME_SCENE, 1.0f, true);

		}
		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) { //has to be changed to volcano map when developed
			App->transition_manager->CreateSlide(SCENES::GAME_SCENE, 1.0f, true);

		}
		
		if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN) {
			App->transition_manager->CreateSlide(SCENES::LOSE_SCENE, 1.0f, true);

		}

		if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) {
			App->transition_manager->CreateSlide(SCENES::WIN_SCENE, 1.0f, true);
		}

	}
	else {

		fPoint mousePosition = App->input->GetMouseWorldPosition();
		iPoint cameraOffset = App->map->WorldToMap(App->render->camera.x, App->render->camera.y);
		iPoint mapCoordinates = App->map->WorldToMap(mousePosition.x - cameraOffset.x, mousePosition.y - cameraOffset.y + App->map->data.tile_height / 2);

		//resources --------------------------------------------------------------------------------
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {  //paint
			App->player->paintCount.count += 10;
		}
		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {  //wood
			App->player->woodCount.count += 10;
		}
		//if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {  //metal scrap
		//}
		//if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {  //titanium
		//}
		//if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {  //food
		//}
		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {  //housing
			App->player->housingSpace.maxCount += 10;
		}
		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {  //research

			//changes for each unit and building

		}
		//units --------------------------------------------------------------------------------
		if (App->input->GetKey(SDL_SCANCODE_KP_1) == KEY_DOWN) {  //painter
			App->entities->AddEntity(ENTITY_TYPE_PAINTER, mapCoordinates, App->entities, nullptr, 0, true);
		}
		if (App->input->GetKey(SDL_SCANCODE_KP_2) == KEY_DOWN) {  //warrior
			App->entities->AddEntity(ENTITY_TYPE_WARRIOR, mapCoordinates, App->entities, nullptr, 0, true);
		}
		//if (App->input->GetKey(SDL_SCANCODE_KP_3) == KEY_DOWN) {  //ranged
		//}
		//if (App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_DOWN) {  //tank
		//}
		//if (App->input->GetKey(SDL_SCANCODE_KP_5) == KEY_DOWN) {  //explorer
		//}
		if (App->input->GetKey(SDL_SCANCODE_KP_0) == KEY_DOWN) {  //kill selected unit

		}
		//buildings --------------------------------------------------------------------------------
		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_KP_1) == KEY_DOWN) {  //paint extractor
			App->entities->AddEntity(ENTITY_TYPE_PAINT_EXTRACTOR, mapCoordinates, App->entities, nullptr, 0, true);
		}
		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_KP_2) == KEY_DOWN) {  //wood producer
			App->entities->AddEntity(ENTITY_TYPE_WOOD_PRODUCER, mapCoordinates, App->entities, nullptr, 0, true);
		}
		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_KP_3) == KEY_DOWN) {  //barracks
			App->entities->AddEntity(ENTITY_TYPE_BARRACKS, mapCoordinates, App->entities, nullptr, 0, true);
		}
		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_DOWN) {  //house
			App->entities->AddEntity(ENTITY_TYPE_HOUSE, mapCoordinates, App->entities, nullptr, 0, true);
		}

	}


	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {

		App->win->Fullscreen_Swap();
	}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->LoadGame();

	
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		App->SaveGame("save_game.xml");
	}


	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {

		if (GOD_MODE == true) {
			GOD_MODE = false;
			App->player->gameTimer.Resume();
		}
		else {
			GOD_MODE = true;
			App->player->gameTimer.Stop();
		}
		
	}


}
