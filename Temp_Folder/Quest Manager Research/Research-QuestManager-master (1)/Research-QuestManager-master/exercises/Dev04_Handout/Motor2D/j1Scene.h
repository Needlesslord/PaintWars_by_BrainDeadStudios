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

	void CheckEvent();
	void OrderEvent();

	void DrawQ0();
	void DrawQ1();
	void DrawQ2();
	void DrawQ3();
	void DrawQ4();
	void DrawQ5();

	//Test1
	SDL_Rect test = { 928, 160, 32, 32 };
	SDL_Rect test2 = { 930, 162, 28, 28 };
	SDL_Rect test3 = { 932, 164, 24, 24 };
	SDL_Rect test4 = { 934, 166, 20, 20 };
	SDL_Rect test5 = { 936, 168, 16, 16 };
	SDL_Rect test6 = { 938, 170, 12, 12 };
	SDL_Rect test7 = { 940, 172, 8, 8 };

	//RayTest
	SDL_Rect ray = { 960, 160, 4, 32 };
	SDL_Rect ray2 = { 964, 160, 4, 32 };
	SDL_Rect ray3 = { 968, 160, 4, 32 };
	SDL_Rect ray4 = { 972, 160, 4, 32 };
	SDL_Rect ray5 = { 976, 160, 4, 32 };
	SDL_Rect ray6 = { 980, 160, 4, 32 };
	SDL_Rect ray7 = { 984, 160, 4, 32 };
	SDL_Rect ray8 = { 988, 160, 4, 32 };



	SDL_Texture* graphics = nullptr;

	int r = 0;
	int score = 0;

	bool cherry = false;
	bool banana = false;
	bool orange = false;
	bool watermelon = false;
	bool mango = false;

};

#endif // __j1SCENE_H__