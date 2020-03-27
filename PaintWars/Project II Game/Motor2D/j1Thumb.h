#ifndef _UI_THUMB__H
#define _UI_THUMB__H

#include "p2Defs.h"
#include "j1Gui.h"
#include "SDL/include/SDL.h"

class SDL_Rect;

class UiItem_Thumb : public UI_Item
{
public:
	UiItem_Thumb(SDL_Rect s_thumb, UI_Item* parent);
	~UiItem_Thumb() {};

	bool Start();
	bool PostUpdate();

	bool OnHover();

public:
	SDL_Rect thumb_box; 
	iPoint click_position; 
};

#endif  // !_UI_THUMB__H
