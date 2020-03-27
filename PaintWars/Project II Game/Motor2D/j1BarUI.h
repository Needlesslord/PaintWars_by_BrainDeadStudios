#ifndef _UI_BAR__H
#define _UI_BAR__H

#include "p2Defs.h"
#include "j1Gui.h"
#include "SDL/include/SDL.h"

class UiItem_Thumb;

class UiItem_Bar : public UI_Item
{
public:
	UiItem_Bar(SDL_Rect slider_box, UI_Item* parent);

	~UiItem_Bar() {};

	
	bool Start();
	bool PostUpdate();
	bool Awake();
	bool Start2();

	float GetThumbValue();
	float GetThumbValue2();
	UiItem_Thumb*	thumb1 = nullptr;
	UiItem_Thumb*	thumb2 = nullptr;
private:
	
	SDL_Rect	box;
public:
	SDL_Rect s_box; // Slider box

};

#endif  // !_UI_BAR__H