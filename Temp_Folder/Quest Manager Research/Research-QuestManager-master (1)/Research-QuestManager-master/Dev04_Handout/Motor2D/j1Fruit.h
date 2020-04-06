#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

#define MAX_FRUITS 25 


struct SDL_Texture;
struct Collider;

enum f_type 
{
	CHERRY = 0,
	BANANA,
	ORANGE,
	WATERMELON,
	MANGO,
	NONE
};

enum difficulty
{
	EASY = 0,
	INTERMEDIATE,
	HARD
};


class j1Fruit : public j1Module 
{
public:

	//Constructor
	j1Fruit();

	// Destructor
	virtual ~j1Fruit();

	//Called at first
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before render is available

	//bool Awake(pugi::xml_node& conf);

	void Spawn();
	void Eaten();
	void UpdateScoreboard();
	void CheckCollision();
	void Restart();

	// Called before quitting
	bool CleanUp();

	int c_points = 0;
	int b_points = 0;
	int o_points = 0;
	int w_points = 0;
	int m_points = 0;

private:

	difficulty difficulty_level;
	

	f_type type;

	p2Point<int> f_pos;
	SDL_Rect f_hitbox = {};

	SDL_Texture* graphics;

	Collider* f_col;


	//Scoreboard

	//cherry
	SDL_Rect c1 = { 864, 448, 32, 32 };
	SDL_Rect c2 = { 928, 448, 32, 32 };
	SDL_Rect c3 = { 992, 448, 32, 32 };
	SDL_Rect c4 = { 1056, 448, 32, 32 };
	SDL_Rect c5 = { 1120, 448, 32, 32 };
	SDL_Rect c_check = { 1170, 454, 20, 20 };

	//banana
	SDL_Rect b1 = { 864, 512, 32, 32 };
	SDL_Rect b2 = { 928, 512, 32, 32 };
	SDL_Rect b3 = { 992, 512, 32, 32 };
	SDL_Rect b4 = { 1056, 512, 32, 32 };
	SDL_Rect b5 = { 1120, 512, 32, 32 };
	SDL_Rect b_check = { 1170, 518, 20, 20 };

	//orange
	SDL_Rect o1 = { 864, 576, 32, 32 };
	SDL_Rect o2 = { 928, 576, 32, 32 };
	SDL_Rect o3 = { 992, 576, 32, 32 };
	SDL_Rect o4 = { 1056, 576, 32, 32 };
	SDL_Rect o5 = { 1120, 576, 32, 32 };
	SDL_Rect o_check = { 1170, 582, 20, 20 };

	//watermelon
	SDL_Rect w1 = { 864, 640, 32, 32 };
	SDL_Rect w2 = { 928, 640, 32, 32 };
	SDL_Rect w3 = { 992, 640, 32, 32 };
	SDL_Rect w4 = { 1056, 640, 32, 32 };
	SDL_Rect w5 = { 1120, 640, 32, 32 };
	SDL_Rect w_check = { 1170, 648, 20, 20 };

	//mango
	SDL_Rect m1 = { 864, 704, 32, 32 };
	SDL_Rect m2 = { 928, 704, 32, 32 };
	SDL_Rect m3 = { 992, 704, 32, 32 };
	SDL_Rect m4 = { 1056, 704, 32, 32 };
	SDL_Rect m5 = { 1120, 704, 32, 32 };
	SDL_Rect m_check = { 1170, 710, 20, 20 };

	
	
};
