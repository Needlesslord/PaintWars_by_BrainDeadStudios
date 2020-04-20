#ifndef __J1FONTS_H__
#define __J1FONTS_H__

#include "j1Module.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_FONTS 50
#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Font_Base
{
	char table[MAX_FONT_CHARS];
	SDL_Texture* graphic = nullptr;
	uint rows, len, char_w, char_h, row_chars;
};

class j1FontsUI : public j1Module
{
public:

	j1FontsUI();
	~j1FontsUI();

	// Load Font
	int Load(const char* texture_path, const char* characters, uint rows = 1);
	void UnLoad(int font_id);

	// Create a surface from text
	void BlitText(int x, int y, int bmp_font_id, const char* text, int layer) const;


private:
	Font_Base	 fonts[MAX_FONTS];

};


#endif // __j1Fonts_H__