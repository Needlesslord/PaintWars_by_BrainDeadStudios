#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;


class j1Scene : public j1Module
{
public:
	
	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//CAMERA



	//MAP & SCENE 
	void Map_Manager();
	void Create_Forest_Map();
	void Create_Snow_Map();
	void Create_Volcano_Map();


private:
	SDL_Texture* debug_tex;

public:

	//MAP MANAGER
	bool LoadingMap;
	bool Forest_Map_Active;
	bool Volcano_Map_Active;
	bool Snow_Map_Active;
	bool Load_Forest_Map;
	bool Load_Volcano_Map;
	bool Load_Snow_Map;
	bool Change_Map;
};

#endif // __j1SCENE_H__