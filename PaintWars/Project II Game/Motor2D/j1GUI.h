#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "j1LabelUI.h"
#include "j1Button.h"
#include "j1BarUI.h"
#include "j1SpriteUI.h"
#include "j1Thumb.h"
#include "SDL/include/SDL.h"

#define CURSOR_WIDTH 2

struct UI_Item;


// TODO 1: Create your structure of classes

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate(float dt);

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	UI_Item* CreateSprite(iPoint pos, SDL_Rect rect, bool static_obj = false, UI_Item * parent = nullptr);
	UIitem_Button* CreateButton(iPoint pos, Button_Type type, SDL_Rect idle_rect, SDL_Rect* idle_hover = NULL, SDL_Rect* idle_click = NULL, const char* text = "", bool static_obj = false, UI_Item* parent = nullptr);
	UI_Label* CreateLabel(iPoint pos, const char* text, Label_Type type, SDL_Color color = { 0,0,0,0 }, bool static_obj = false, UI_Item* parent = nullptr);
	UiItem_Thumb* CreateThumb(SDL_Rect s_thumb, UI_Item* parent = nullptr);
	UiItem_Bar* CreateSlider(iPoint pos, SDL_Rect slider_box, bool static_obj = false, UI_Item * parent = nullptr);
	SDL_Texture* GetAtlas() const;

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&)const;

public:
	p2List<UI_Item*> gui_list; // List of items
	uint			fx_buton_pressed; // FX
private:
	SDL_Texture*	atlas;
	p2SString		atlas_file_name;
	p2SString		fx_button_pressed_string; // STring when the button is pressed



};

#endif // __j1GUI_H__
