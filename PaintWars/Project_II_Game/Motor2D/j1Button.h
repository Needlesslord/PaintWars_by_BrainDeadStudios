#ifndef _UI_BUTTON__H
#define _UI_BUTTON__H

#include "p2Defs.h"
#include "j1ElementUI.h"
#include "SDL/include/SDL.h"

enum Button_Type //Types of buttons
{
	PLAY,
	SETTINGS,
	CONTINUE,
	MUTE,
	UNMUTE,
	BACK,
	SAVE,
	LOAD,
	EXIT,
	CLOSE,
	MENU,
	START_PLAY,
	START_CONTINUE,
	START_SETTINGS,
	CLOSE_SETTINGS,
	LINK,
	CREDITS_CLOSE,
	CREDITS_MENU,
	SLIDER_BOX,

	//CONSOLE BUTTONS
	CONSOLE_MAIN,
	CONSOLE_SECONDARY,
	CONSOLE_KILL,
	CONSOLE_HPLESS,
	CONSOLE_HPMORE,
	CONSOLE_HPFULL,
	CONSOLE_GOD,
	CONSOLE_NOCAP,
	CONSOLE_30CAP,
	CONSOLE_60CAP,
	CONSOLE_NOVSYNC,
	CONSOLE_YESVSYNC,
	CONSOLE_RESETENTITY,
	CONSOLE_MAP1,
	CONSOLE_MAP2,
	CONSOLE_COLLECTLESS,
	CONSOLE_COLLECTMORE,
	BOX_SLIDER1,
	BOX_SLIDER2
};

class  UIitem_Button :public UI_Item
{
public:
	UIitem_Button(const char* text, Button_Type type, SDL_Rect idle_rect, SDL_Rect* rect_hover, SDL_Rect* rect_click, UI_Item* parent);
	~UIitem_Button();

	bool Start();
	bool PostUpdate();
	Button_Type	GetType();

	bool OnHover(); // To know the if the button is OnHoverState


private:
	SDL_Rect	button_rect[MAX_STATE]; //Rect of the button
	p2SString	button_text; // Text for button (Not Visual)
	Button_Type	button_type; // Which type of button
};

#endif  // !_UI_BUTTON__H