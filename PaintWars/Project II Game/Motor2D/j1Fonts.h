#ifndef __j1FONTS_H__
#define __j1FONTS_H__

#include "j1Module.h"
#include "SDL\include\SDL_pixels.h"

//#define DEFAULT_FONT "fonts/OpenSans-BoldItalic.ttf"
#define DEFAULT_FONT "fonts/Chocolate_Drink.ttf"
#define DEFAULT_FONT_SIZE 40

struct SDL_Texture;
struct _TTF_Font;

class j1Fonts : public j1Module
{
public:

	j1Fonts();

	// Destructor
	virtual ~j1Fonts();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Start();

	// Called before quitting
	bool CleanUp();

	// Load Font
	_TTF_Font* const Load(const char* path, int size = 12);

	// Create a surface from text
	SDL_Texture* Print(const char* text, SDL_Color color = { 255, 255, 255, 255 }, _TTF_Font* font = NULL);

	bool CalcSize(const char* text, int& width, int& height, _TTF_Font* font = NULL) const;

public:

	p2List<_TTF_Font*>	fonts;
	_TTF_Font*			default;
	_TTF_Font*			title_buttons;
	_TTF_Font*			title_config;
	_TTF_Font*			title_settings;
	_TTF_Font*			Button_Title;
	_TTF_Font*			credits;
	_TTF_Font*          MainTitle;
	_TTF_Font*          Timer;
	_TTF_Font*          UI_Title;
	_TTF_Font*          Regular_Text;
	_TTF_Font*          Regular_Text_Small;
	_TTF_Font*          Timer_Ingame_Font;
	_TTF_Font*          Console_Font;
	_TTF_Font*          SliderFont;
};


#endif // __j1FONTS_H__
