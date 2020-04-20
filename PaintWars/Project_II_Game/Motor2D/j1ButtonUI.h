#include "j1UIElements.h"
class j1ButtonUI : public j1UIElement
{
public:

	j1ButtonUI();
	~j1ButtonUI();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();


	//void Button_Texture_Manager();
	//void Button_Texture_Manager(SDL_Texture* TypeOfTexture,SDL_Rect* RectToBlit);



	



private:

	

	SDL_Texture* Button_UI_Texture_General_ATLAS = nullptr;
	SDL_Texture* Button_UI_Texture_Minimap_FULL_SCALE = nullptr;
	SDL_Texture* Button_UI_Texture_Minimap_MINI_SCALE = nullptr;
	SDL_Texture* Button_UI_Texture_Minimap_CAMERA_FOLLOW = nullptr;
	SDL_Texture* Button_UI_Texture_Letters_WIN_SCENE = nullptr;
	SDL_Texture* Button_UI_Texture_Letters_LOSE_SCENE = nullptr;
	SDL_Texture* Button_UI_Texture_Letters_LOGO_SCENE = nullptr;
	SDL_Texture* Button_UI_Texture_LogoImage_LOGO_SCENE = nullptr;
	SDL_Texture* Button_UI_Texture_ContinueLetters_WIN_LOSE_SCENE = nullptr;

	

	

	
	
};