#ifndef __j1INGAMEUI_H__
#define __j1INGAMEUI_H__

#include "j1Module.h"

struct Game_Menu {

	j1GUIelement* optionsButton = nullptr;
	j1GUIelement* continueButton = nullptr;
	

};

class j1InGameUI : public j1Module
{
public:

	j1InGameUI();
	~j1InGameUI();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();

	void Add_UI();
	void Activate_Menu();
	void GUI_Event_Manager(GUI_Event type, j1GUIelement* element);

private:
	int MiddleScreenW;
	int MiddleScreenH;
	int width;
	Game_Menu menu;
};

#endif // __j1WINDOW_H__