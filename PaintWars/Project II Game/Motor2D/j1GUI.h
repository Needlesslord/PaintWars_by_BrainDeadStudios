#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "j1GUIElements.h"
#include <vector>


class j1Entity;
struct SDL_Texture;


class j1GUI : public j1Module
{

public:

	j1GUI();
	~j1GUI();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	SDL_Texture* Load_Texture(TEXTURE textureType = TEXTURE::NONE);

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	void UpdatePosition(j1Element* element, fPoint position, fPoint local_position);
	j1Element* AddElement(GUItype type, j1Element* parent, fPoint map_Position, fPoint inside_position, bool interactable, bool enabled, SDL_Rect section, char* text = nullptr, j1Module* listener = nullptr, bool X_drag = false, bool Y_drag = false, SCROLL_TYPE scrollType = SCROLL_TYPE::SCROLL_NONE, bool decor = false, TEXTURE textureType = TEXTURE::NONE);
	p2List<j1Element*>	GUI_ELEMENTS;
	//std::vector<j1Element*> gui_elements;

public:
	//TEXTURES FOR UI
	SDL_Texture* texture_load = nullptr;
};

#endif //  __j1GUI_H__

