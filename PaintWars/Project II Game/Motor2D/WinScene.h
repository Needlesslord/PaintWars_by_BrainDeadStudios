#ifndef __WINSCENE_H__
#define __WINSCENE_H__

#include "j1Module.h"
#include "Scene.h"

class WinScene : public Scene
{
public:

	WinScene();									// Constructor
	~WinScene();									// Destructor

	bool Awake(pugi::xml_node& config);				// Called before render is available
	bool Start();									// Called before the first frame
	bool PreUpdate();								// Called before all Updates
	bool Update(float dt);							// Called each loop iteration
	bool PostUpdate();								// Called before all Updates
	bool CleanUp();									// Called before quitting



public:
	//void InitScene();								// Method that will be used to initialize all scene elements.

	//void DrawScene();								// Method that will draw all scene elements on screen.
	//SDL_Texture* SceneToTexture();				// Method that will be used to get a texture from the current screen.

	void GUI_Event_Manager(GUI_Event type, j1UIElement* element);

	void ExecuteTransition();						// Method that will trigger a new transition depending on the input received.

public:

	j1UIElement* continueButton = nullptr;
	j1UIElement* forestButton = nullptr;
	j1UIElement* snowButton = nullptr;
	j1UIElement* volcanoButton = nullptr;
	j1UIElement* backButton = nullptr;
	j1UIElement* Win_Scene_UI = nullptr;
	j1UIElement* ReturnVictorious = nullptr;

};

#endif 
