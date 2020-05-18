
#include "j1UIElements.h"

class j1UISprites : public j1UIElement
{
public:

	j1UISprites();
	~j1UISprites();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();


private:

	SDL_Texture* Sprites_UI_Texture_General_ATLAS = nullptr;
	SDL_Texture* Sprites_UI_Texture_General_Sprites = nullptr;
	SDL_Texture* Sprites_UI_Texture_Minimap_FULL_SCALE_BACK = nullptr;
	SDL_Texture* Sprites_UI_Texture_Minimap_MINI_SCALE_forest = nullptr;
	SDL_Texture* Sprites_UI_Texture_Minimap_MINI_SCALE_snow = nullptr;
	SDL_Texture* Sprites_UI_Texture_Minimap_MINI_SCALE_volcano = nullptr;
	SDL_Texture* Sprites_UI_Texture_Minimap_CAMERA_FOLLOW = nullptr;
	SDL_Texture* Sprites_UI_Texture_Letters_WIN_SCENE = nullptr;
	SDL_Texture* Sprites_UI_Texture_Letters_LOSE_SCENE = nullptr;
	SDL_Texture* Sprites_UI_Texture_Letters_LOGO_SCENE = nullptr;
	SDL_Texture* Sprites_UI_Texture_LogoImage_LOGO_SCENE = nullptr;
	SDL_Texture* Sprites_UI_Texture_ContinueLetters_WIN_LOSE_SCENE = nullptr;

	SDL_Texture* Sprites_UI_Texture_Background_Forest = nullptr;
};