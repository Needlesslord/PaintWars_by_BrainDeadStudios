#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "j1Module.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1Timer.h"
#include "j1PerfTimer.h"
#include <list>

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Collision;
class j1SceneManager;
class j1Map;
class j1EntityManager;
class j1PathFinding;
class j1ParticleManager;
//class j1Particles;
class j1UI_Manager;
class j1FontsUI;
class j1Player;
class TransitionManager;
class SceneManager;
class j1QuestManager;
class j1Video;
class j1FogOfWar;


class j1App 
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	float GetDT() const;
	
	void LoadGame();
	void SaveGame(const char*) const;
	void GetSaveGames(std::list<std::string>& list_to_fill) const;

	//Load quest file
	pugi::xml_node LoadQuests(pugi::xml_document& quest_file) const;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;
	void Debug_Actions();
public:

	// Modules
	j1Window*			win = NULL;
	j1Input*			input = NULL;
	j1Render*			render = NULL;
	j1Textures*			tex = NULL;
	j1Audio*			audio = NULL;
	j1Collision*		col = NULL;
	j1SceneManager*		scenes = NULL;
	j1Map*				map = NULL;
	j1EntityManager*	entities = NULL;
	j1PathFinding*		pathfinding = NULL;
	j1ParticleManager*	pmanager = NULL;
	//j1Particles*		particles = NULL;
	j1Player*			player = NULL;
	j1UI_Manager*		gui = NULL;
	j1FontsUI*			fonts = NULL;
	TransitionManager*  transition_manager = NULL;
	j1QuestManager*		quest_manager = NULL;
	j1Video*            video = NULL;
	j1FogOfWar*		    fow = NULL;


private:

	std::list<j1Module*> modules;
	int					argc;
	char**				args;

	std::string			title;
	std::string			organization;

	mutable bool		want_to_save = false;
	bool				want_to_load = false;
	bool				has_game_saved = false;
	std::string			load_game;
	mutable std::string	save_game;

	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;

public:

	uint32				framerate_cap = 60;
	bool				fpscap = false;
	uint64				frame_count = 0;
	float dt = 0.1f;
	uint32 getFpsCap() { return framerate_cap; };
	void setFpsCap(uint32 fps);
	bool DEBUG_ACTIVE;
	bool PAUSE_ACTIVE;
	bool GOD_MODE;
	bool canContinue = false;

};

extern j1App* App;

#endif