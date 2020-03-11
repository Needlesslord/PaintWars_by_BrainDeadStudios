#ifndef __J1PLAYER_H__
#define __J1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2Log.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();

	//LOADING AND SAVING OPTIONS
	bool Save(pugi::xml_node& data);
	bool Load(pugi::xml_node& data);	
	
private:

	void Drag_Mouse();
	void Camera_Control(float dt);
	void Mouse_Cursor();
	void Select_Entitites(SDL_Rect);
	void Zoom();

	SDL_Rect selector;
	SDL_Rect texture_rect{ 0,0,300,300 };

	SDL_Texture* Tex_Player;

	iPoint mouse_position; 
	iPoint start_mouse_position;

	p2SString	folder;
	pugi::xml_node	node;
	p2SString file;

	uint win_height;
	uint win_width;
	int camera_speed;
	int camera_offset;
};

#endif // __j1PLAYER_H__