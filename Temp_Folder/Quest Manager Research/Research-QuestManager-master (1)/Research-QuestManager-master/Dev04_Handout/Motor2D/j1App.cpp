#include <iostream> 

#include "p2Defs.h"
#include "p2Log.h"

#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Fruit.h"
#include "j1Collision.h"
#include "j1Fonts.h"
#include "j1QuestManager.h"
#include "j1App.h"


// Constructor
j1App::j1App(int argc, char* args[]) : argc(argc), args(args)
{
	PERF_START(perf_timer);

	/*frames = 0;*/
	want_to_save = want_to_load = false;

	input = new j1Input();
	win = new j1Window();
	render = new j1Render();
	tex = new j1Textures();
	audio = new j1Audio();
	scene = new j1Scene();
	map = new j1Map();
	player = new j1Player();
	fruit = new j1Fruit();
	collider = new j1Collision();
	fonts = new j1Fonts();
	quest_manager = new j1QuestManager();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(map);
	AddModule(collider);


	//player and scenes
	AddModule(scene);
	AddModule(player);
	AddModule(fruit);

	AddModule(fonts);

	AddModule(quest_manager);


	// render last to swap buffer
	AddModule(render);


	PERF_PEEK(perf_timer);
}

// Destructor
j1App::~j1App()
{
	// release modules
	p2List_item<j1Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void j1App::AddModule(j1Module* module)
{
	module->Init();
	modules.add(module);
}

// Called before render is available
bool j1App::Awake()
{
	PERF_START(perf_timer);

	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	bool ret = false;
		
	config = LoadConfig(config_file);

	frame_cap = 60;

	if(config.empty() == false)
	{
		// self-config
		ret = true;
		app_config = config.child("app");
		title.create(app_config.child("title").child_value());
		organization.create(app_config.child("organization").child_value());
	}

	if(ret == true)
	{
		p2List_item<j1Module*>* item;
		item = modules.start;

		while(item != NULL && ret == true)
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	PERF_PEEK(perf_timer);
	return ret;
}

// Called before the first frame
bool j1App::Start()
{
	PERF_START(perf_timer);
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}

	PERF_PEEK(perf_timer);
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

//TODO 2: All of our data will be parsed from that XML, therefore we need to create a new function in the App that will read and load that XML for us

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

// ---------------------------------------------
void j1App::PrepareUpdate()
{
	frame_count++;
	frames_last_second++;

	dt = frame_timer.ReadSec();						//Keeps track of the amount of time that has passed since last frame in seconds (processing time of a frame: Frame 1: 0.033secs, ...).
	frame_timer.Start();
}

// ---------------------------------------------
void j1App::FinishUpdate()
{
	if(want_to_save == true)
		SavegameNow();

	if(want_to_load == true)
		LoadGameNow();

	if (last_second_timer.ReadMs() > 1000)
	{
		last_second_timer.Start();
		prev_sec_frames = frames_last_second;
		frames_last_second = 0;
	}

	float frame_cap_ms = 1000 / frame_cap;
	float current_frame_ms = frame_timer.Read();

	if (framesAreCapped)
	{
		if (current_frame_ms < frame_cap_ms)						//If the current frame processing time is lower than the specified frame_cap. Timer instead of PerfTimer was used because SDL_Delay is inaccurate.
		{
			true_delay_timer.Start();

			SDL_Delay(frame_cap_ms - current_frame_ms);				//SDL_Delay delays processing for a specified time. In this case, it delays for the difference in ms between the frame cap (30fps so 33,3ms per frame) and the current frame.

			int intended_delay = frame_cap_ms - current_frame_ms;

			//LOG("We waited for %d milliseconds and got back in %f", intended_delay, true_delay_timer.ReadMs());
		}
	}

	float avg_fps = frame_count / startup_timer.ReadSec();
	seconds_since_startup = startup_timer.ReadSec();
	uint32 last_frame_ms = frame_timer.Read();
	uint32 frames_on_last_update = prev_sec_frames;					//Keeps track of how many frames were processed the last second.

	if (framesAreCapped)
	{
		frameCapOnOff = "On";
	}
	else
	{
		frameCapOnOff = "Off";
	}

	if (vsyncIsActive)
	{
		vsyncOnOff = "On";
	}
	else
	{
		vsyncOnOff = "Off";
	}

	static char title[256];

	sprintf_s(title, 256, "Av.FPS: %.2f / Last Frame Ms: %02u / Last sec frames: %i / Last dt: %.3f / Time since startup: %.3f / Frame Count: %lu / %d / Vsync: %s / Frame cap: %s",
		avg_fps, last_frame_ms, frames_on_last_update, dt, seconds_since_startup, frame_count, vsyncOnOff, frameCapOnOff, frameCapOnOff);

	App->win->SetTitle(title);
}

// Call modules before each loop iteration
bool j1App::PreUpdate()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;
	j1Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool j1App::DoUpdate()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.start;
	j1Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool j1App::PostUpdate()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	j1Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool j1App::CleanUp()
{
	bool ret = true;
	p2List_item<j1Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
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
	return title.GetString();
}

// ---------------------------------------
const char* j1App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
void j1App::LoadGame()
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list
	want_to_load = true;
}

// ---------------------------------------
void j1App::SaveGame() const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?

	want_to_save = true;
}

// ---------------------------------------
void j1App::GetSaveGames(p2List<p2SString>& list_to_fill) const
{
	// need to add functionality to file_system module for this to work
}

bool j1App::LoadGameNow()
{
	bool ret = false;

	pugi::xml_document data;
	pugi::xml_node root;

	pugi::xml_parse_result result = data.load_file(load_game.GetString());

	if(result != NULL)
	{
		LOG("Loading new Game State from %s...", load_game.GetString());

		root = data.child("game_state");

		p2List_item<j1Module*>* item = modules.start;
		ret = true;

		while(item != NULL && ret == true)
		{
			ret = item->data->Load(root.child(item->data->name.GetString()));
			item = item->next;
		}

		data.reset();
		if(ret == true)
			LOG("...finished loading");
		else
			LOG("...loading process interrupted with error on module %s", (item != NULL) ? item->data->name.GetString() : "unknown");
	}
	else
		LOG("Could not parse game state xml file %s. pugi error: %s", load_game.GetString(), result.description());

	want_to_load = false;
	return ret;
}

bool j1App::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", save_game.GetString());

	// xml object were we will store all data
	pugi::xml_document data;
	pugi::xml_node root;
	
	root = data.append_child("game_state");

	p2List_item<j1Module*>* item = modules.start;

	while(item != NULL && ret == true)
	{
		ret = item->data->Save(root.append_child(item->data->name.GetString()));
		item = item->next;
	}

	if(ret == true)
	{
		data.save_file(save_game.GetString());
		LOG("... finished saving", );
	}
	else
		LOG("Save process halted from an error in module %s", (item != NULL) ? item->data->name.GetString() : "unknown");

	data.reset();
	want_to_save = false;
	return ret;
}