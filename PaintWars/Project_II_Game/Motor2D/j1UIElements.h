#ifndef __j1UIELEMENTS_H__
#define __j1UIELEMENTS_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2Log.h"
#include "SDL/include/SDL_render.h"

#include "SDL\include\SDL_pixels.h"

struct SDL_Texture;

enum class TypeOfUI
{
	GUI_ERROR,
	GUI_BUTTON,
	GUI_INPUTBOX,
	GUI_SCROLLBAR,
	GUI_LABEL,
	GUI_IMAGE,
	GUI_TEXT
};

enum class FONT
{
	FONT_SMALL,
	FONT_MEDIUM,
	FONT_MEDIUM_WHITE,
	FONT_SMALL_WHITE,
	FONT_LOSE_WIN,
	FONT_EXTRA_SMALL,
	FONT_EXTRA_SMALL_WHITE,
	FONT_EXTRA_SMALL_RED,
	FONT_SMALL_RED
};

enum class SCROLL_TYPE
{
	SCROLL_NONE,
	SCROLL_MUSIC
};

enum class TEXTURE
{
	//BUTTONS
	ATLAS,
	MINIMAP_FULL,
	MINIMAP_MINI,
	MINIMAP_CAMERA,
	CONTINUE_LETTERS,
	LOSE_SCREEN,
	WIN_SCREEN,
	LOGO,
	LOGO_LETTERS,
	TEAM_LOGO,

	//SPRITES
	MAIN_IMAGE,
	FOREST_IMAGE,
	VOLCANO_IMAGE,
	SNOW_IMAGE,
	LOGO_SPRITE,
	ATLAS_SPRITE,
	MINIMAP_BACK_SPRITE,
	MINIMAP_CAMERA_SPRITE,
	LOSE_SCREEN_SPRITE,
	WIN_SCREEN_SPRITE,
	MINIMAP_ENTITIES,
	BACKGROUND_FOREST,

	NONE




	/*BUTON_,
	BUTON_HOVER,
	OPTIONS,
	NEXT,
	PREV,
	SCROLL,
	MANAGER_IMAGE,
	IMAGE,
	MAIN_IMAGE,
	BOTON_SCROLL,
	ATLAS,
	MINIMAP_FULL,
	MINIMAP_MINI,
	MINIMAP_BACK,
	MINIMAP_CAMERA,
	LOSE_SCREEN,
	WIN_SCREEN,
	CONTINUE_LETTERS,
	LOGO,
	LOGO_LETTERS,
	NONE*/

	//SPRITES



};

class j1UIElement
{

public:

	j1UIElement() { };
	~j1UIElement();

	virtual bool Start();
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };

	virtual bool CleanUp() { return true; };

	bool MouseOnRect();
	virtual void Mouse_On_Click();
	
public:

	j1UIElement* parent = nullptr;
	j1Module* listener = nullptr;
	TypeOfUI type = TypeOfUI::GUI_ERROR;
	TEXTURE textureType = TEXTURE::NONE;
	FONT fontType = FONT::FONT_MEDIUM;
	fPoint map_position = {0,0};
	fPoint init_map_position = { 1028,575 }; 	//fPoint init_map_position = { 0,0 }; 
	fPoint inside_position = { 0,0 };
	int layer = 3;

	j1UIElement* Button = nullptr;

	SDL_Color color = { 255,255,255 };
	char* text = nullptr;
	bool enabled = false;
	bool interactable = false;

	bool X_drag = false;
	bool Y_drag = false;

	bool above = false;
	bool focus = false;

	

	SDL_Rect rect = { 0,0,0,0 };
	SDL_Rect hover_rect = { 0,0,0,0 };
	SDL_Rect click_rect = { 0,0,0,0 };

	int Value;
	float Float_Value;


	j1UIElement* label = nullptr;
};



#endif // __j1UIELEMENTS_H__
