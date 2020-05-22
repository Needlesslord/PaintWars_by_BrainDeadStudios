#ifndef __GAMELOGOSCENE_H__
#define __GAMELOGOSCENE_H__

#include "j1Module.h"
#include "Scene.h"

class GameLogoScene : public Scene
{
public:

	GameLogoScene();									// Constructor
	~GameLogoScene();									// Destructor

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

	j1UIElement* gameLogoButton = nullptr;
	j1UIElement* lettersLogoStart = nullptr;


};

#endif // __FIRSTSCENE_H__
