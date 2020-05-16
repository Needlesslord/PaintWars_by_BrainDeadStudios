#ifndef _UI_LABEL__H
#define _UI_LABEL__H

#include "p2Defs.h"
#include "j1ElementUI.h"
#include "SDL/include/SDL.h"

enum Label_Type { // Types of labels
	TITLE,
	FONT,
	CONFIG,
	CREDITS,
	BUTTON,
	MAIN_TITLE,
	TEXT,
	UI_FONTS,
	TIME_MENU,
	TEXT_SMALL,
	CONSOLE,
	SLIDERS_FONTS
};

class UI_Label : public UI_Item
{
public:
	UI_Label(const char* text, Label_Type type, SDL_Color color, UI_Item* parent);
	~UI_Label();

	bool Start();
	bool PostUpdate();

	bool OnHover();
	void ChangeTexture(SDL_Color color); // Change the color of the label, when hover or click state
	void ChangeText(const char* text); // Change the text of the label, in this case it is going to have the same but with a different color

private:
	Label_Type label_type;
	p2SString label_text;
	SDL_Color label_color;

public:

	mutable SDL_Texture* tex = nullptr; //?

};


#endif  // !_UI_LABEL__H
