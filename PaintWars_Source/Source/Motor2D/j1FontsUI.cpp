
#include "j1App.h"
#include "j1Textures.h"
#include "j1FontsUI.h"
#include "j1Render.h"

#include <string.h>

// Constructor
j1FontsUI::j1FontsUI() : j1Module()
{}

// Destructor
j1FontsUI::~j1FontsUI()
{}

//The blit sytem for fonts  we are using in the render  with Blit Text and all the code related to creation of text in this game 
//belongs to Dolime Corporation (https://github.com/Sanmopre/DOLIME-CORP-PROJECT-II) All code related to Text bliting using labels belongs to them!
// Load new texture from file path
int j1FontsUI::Load(const char* texture_path, const char* characters, uint rows)
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
	fonts[id].graphic = tex; 
	fonts[id].rows = rows; 
	App->tex->GetSize(tex, texturew, textureh);
	fonts[id].len = strlen(characters); 
	fonts[id].char_w = texturew / (fonts[id].len / rows);
	fonts[id].char_h = (textureh / rows) - rows;
	fonts[id].row_chars = fonts[id].len / rows;
	SDL_strlcpy(fonts[id].table, characters, fonts[id].len + 1);

	return id;
}

void j1FontsUI::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->tex->UnLoad(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;

	}
}
void j1FontsUI::BlitText(int x, int y, int font_id, const char* text, int layer) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
	
		return;
	}
	int charPosX = 0;
	const Font_Base* font = &fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	for (uint i = 0; i < len; i++)
	{
		for (uint j = 0; j < font->len; j++)
		{
			if (text[i] == font->table[j])
			{

				rect.y = rect.h * (j / font->row_chars); 
				rect.x = rect.w * (j % font->row_chars);

				
				App->render->RenderQueueUI(layer, font->graphic, x + (rect.w * charPosX) - App->render->camera.x, y -App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
				charPosX++;
				break;
			}

		}

	}
}
//////////////////////////////////////////                  DISCLAIMER                       /////////////////////////////////////////////////////////