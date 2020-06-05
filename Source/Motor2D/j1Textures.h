#ifndef __j1TEXTURES_H__
#define __j1TEXTURES_H__

#include "j1Module.h"
#include "p2List.h"
#include <list>

struct SDL_Texture;
struct SDL_Surface;

class j1Textures : public j1Module
{
public:

	j1Textures();

	// Destructor
	virtual ~j1Textures();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before quitting
	bool CleanUp();

	// Load Texture
	SDL_Texture* const	Load(const char* path);
	bool				UnLoad(SDL_Texture* texture);
	SDL_Texture* const	LoadSurface(SDL_Surface* surface);
	void				GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:

	std::list<SDL_Texture*>	textures;


	SDL_Texture* Button_UI_Texture_General_ATLAS = nullptr;
	SDL_Texture* Button_UI_Texture_Minimap_FULL_SCALE_forest = nullptr;
	SDL_Texture* Button_UI_Texture_Minimap_MINI_SCALE_forest = nullptr;
	SDL_Texture* Button_UI_Texture_Minimap_FULL_SCALE_snow = nullptr;
	SDL_Texture* Button_UI_Texture_Minimap_MINI_SCALE_snow = nullptr;
	SDL_Texture* Button_UI_Texture_Minimap_FULL_SCALE_volcano = nullptr;
	SDL_Texture* Button_UI_Texture_Minimap_MINI_SCALE_volcano = nullptr;
	SDL_Texture* Button_UI_Texture_Minimap_CAMERA_FOLLOW = nullptr;
	SDL_Texture* Button_UI_Texture_Letters_WIN_SCENE = nullptr;
	SDL_Texture* Button_UI_Texture_Letters_LOSE_SCENE = nullptr;
	SDL_Texture* Button_UI_Texture_Letters_LOGO_SCENE = nullptr;
	SDL_Texture* Button_UI_Texture_LogoImage_LOGO_SCENE = nullptr;
	SDL_Texture* Button_UI_Texture_ContinueLetters_WIN_LOSE_SCENE = nullptr;
	SDL_Texture* Button_UI_Texture_TeamLogoImage_TEAM_LOGO_SCENE = nullptr;
};


#endif // __j1TEXTURES_H__