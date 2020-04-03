
#include "j1App.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Render.h"

#include <string.h>

// Constructor
j1Fonts::j1Fonts() : j1Module()
{}

// Destructor
j1Fonts::~j1Fonts()
{}

// Load new texture from file path
int j1Fonts::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
	
		return id;
	}

	SDL_Texture* tex = App->tex->Load(texture_path);
	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
	
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].graphic == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		
		return id;
	}

	uint texturew, textureh;
	fonts[id].graphic = tex; // graphic: pointer to the texture
	fonts[id].rows = rows; // rows: rows of characters in the texture
	App->tex->GetSize(tex, texturew, textureh);
	fonts[id].len = strlen(characters); // len: length of the table
	fonts[id].char_w = texturew / (fonts[id].len / rows);
	fonts[id].char_h = (textureh / rows) - rows;//there's a blank pixel line before every row
	fonts[id].row_chars = fonts[id].len / rows;
	SDL_strlcpy(fonts[id].table, characters, fonts[id].len + 1);

	return id;
}

void j1Fonts::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->tex->UnLoad(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;

	}
}

// Render text using a bitmap font
void j1Fonts::BlitText(int x, int y, int font_id, const char* text) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
	
		return;
	}
	int charPosX = 0;
	const Font* font = &fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	for (uint i = 0; i < len; i++)//itinerating each letter
	{
		for (uint j = 0; j < font->len; j++)//searching for the letter on the table
		{
			if (text[i] == font->table[j])//if there's a match
			{

				rect.y = rect.h * (j / font->row_chars); //x position of the rectangle in the texture
				rect.x = rect.w * (j % font->row_chars);//y position of the rectangle in the texture

				//App->render->Blit(font->graphic, x + (rect.w * charPosX), y, &rect, 0, false);//Blit of the font, each letter goes on a greater x pos
				App->render->AddBlitEvent(4, font->graphic, x + (rect.w * charPosX) - App->render->camera.x, y -App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
				charPosX++;
				break;
			}

		}

	}
}