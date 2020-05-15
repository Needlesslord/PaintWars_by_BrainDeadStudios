#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "j1UIElements.h"
#include <vector>


class j1Entity;
struct SDL_Texture;


class j1UI_Manager : public j1Module
{

public:

	j1UI_Manager();
	~j1UI_Manager();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	SDL_Texture* Get_Texture_From_Image(TEXTURE textureType = TEXTURE::NONE);

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	void UpdatePosition(j1UIElement* element, fPoint position, fPoint local_position);
	j1UIElement* AddElement(TypeOfUI type, j1UIElement* parent, fPoint map_Position, fPoint inside_position, bool interactable, bool enabled, SDL_Rect section, char* text = nullptr, j1Module* listener = nullptr, TEXTURE textureType = TEXTURE::NONE, FONT fontType = FONT::FONT_MEDIUM, int layer = 3);
	p2List<j1UIElement*>	GUI_ELEMENTS;
	//std::vector<j1UIElement*> gui_elements;

public:
	//TEXTURES FOR UI
	SDL_Texture* Atlas_Load = nullptr;
	SDL_Texture* Atlas_Sprite_Load = nullptr;
	SDL_Texture* Minimap_Entities_Load = nullptr;
	SDL_Texture* Minimap_Full_Load = nullptr;
	SDL_Texture* Minimap_Mini_Load = nullptr;
	SDL_Texture* Minimap_Back_Load = nullptr;
	SDL_Texture* Minimap_Camera_Load = nullptr;
	SDL_Texture* Lose_Screen_Sprite_Load = nullptr;
	SDL_Texture* Win_Screen_Sprite_Load = nullptr;
	SDL_Texture* Continue_Letters_Load = nullptr;
	SDL_Texture* Main_Image_Load = nullptr;
	SDL_Texture* Forest_Image_Load = nullptr;
	SDL_Texture* Volcano_Image_Load = nullptr;
	SDL_Texture* Snow_Image_Load = nullptr;
	SDL_Texture* Logo_Sprite_Load = nullptr;
	SDL_Texture* Logo_Load = nullptr;
	SDL_Texture* Logo_Letters = nullptr;
	SDL_Texture* Background_Forest_Sprite_Load = nullptr;

	

};

#endif //  __j1GUI_H__

