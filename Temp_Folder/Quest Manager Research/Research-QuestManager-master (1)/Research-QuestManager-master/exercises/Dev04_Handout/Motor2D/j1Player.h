
#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"


struct SDL_Texture;
struct Collider;

enum p_states {

	STOP = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DEBUG
};

// ----------------------------------------------------
class j1Player : public j1Module
{
public:

	//Constructor
	j1Player();

	// Destructor
	virtual ~j1Player();

	//Called at first
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before render is available

	bool Awake(pugi::xml_node& conf);

	p2Point<int> getPos() const;

	// Called each loop iteration


	void MoveU();
	void MoveD();
	void MoveL();
	void MoveR();


	// Called before quitting
	bool CleanUp();

	bool is_dead = false;

	int score = 0;

private:

	p_states c_state;

	p2Point<int> pos;

	SDL_Rect hitbox = {};

	
	int snake = 0;
	int speed;

	bool out_of_limits = false;

	
};



#endif // __j1PLAYER_H__