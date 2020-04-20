#ifndef __J1PLAYER_H__
#define __J1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2Log.h"
#include "SDL/include/SDL_rect.h"
#include "GameScene.h"

struct SDL_Texture;

enum RESOURCE_TYPE {

	RESOURCE_TYPE_PAINT,
	RESOURCE_TYPE_FOOD,
	RESOURCE_TYPE_WOOD,
	RESOURCE_TYPE_METAL_SCRAP,
	RESOURCE_TYPE_TITANIUM,
	RESOURCE_TYPE_HOUSING,
	//RESOURCE_TYPE_RESEARCH,

	RESOURCE_NO_TYPE

};

struct Resource
{
	RESOURCE_TYPE type = RESOURCE_NO_TYPE;
	float count;
	float maxCount;
	//uint researchLevel;

};

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

public:

	Resource paintCount;
	Resource woodCount;
	Resource housingSpace;
	int camera_speed;
	int win_height;
	int win_width;

	int camera_offset;

	j1Timer gameTimer;

private:

	SDL_Rect selector;
	SDL_Rect texture_rect{ 0,0,300,300 };

	SDL_Texture* Tex_Player;

	fPoint mouse_position; 
	fPoint start_mouse_position;

	std::string	folder;
	pugi::xml_node	node;
	std::string file;


};

#endif // __j1PLAYER_H__