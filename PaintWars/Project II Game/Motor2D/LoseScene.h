//#ifndef __LOSESCENE_H__
//#define __LOSESCENE_H__
//
//#include "j1Module.h"
//#include "Scene.h"
//
//class LoseScene : public Scene
//{
//public:
//
//	LoseScene();									// Constructor
//	~LoseScene();									// Destructor
//
//	bool Awake(pugi::xml_node& config);				// Called before render is available
//	bool Start();									// Called before the first frame
//	bool PreUpdate();								// Called before all Updates
//	bool Update(float dt);							// Called each loop iteration
//	bool PostUpdate();								// Called before all Updates
//	bool CleanUp();									// Called before quitting
//
//	void GUI_Event_Manager(GUI_Event type, j1Element* element);
//
//public:
//	//void InitScene();								// Method that will be used to initialize all scene elements.
//
//	//void DrawScene();								// Method that will draw all scene elements on screen.
//	//SDL_Texture* SceneToTexture();				// Method that will be used to get a texture from the current screen.
//
//	void ExecuteTransition();						// Method that will trigger a new transition depending on the input received.
//
//public:
//
//	j1Element* Lose_Scene_UI = nullptr;
//	j1Element* Continue = nullptr;
//
//
//};
//
//#endif // __LOSESCENE_H__


#ifndef __LOSESCENE_H__
#define __LOSESCENE_H__

#include "j1Module.h"
#include "Scene.h"

class LoseScene : public Scene
{
public:

	LoseScene();									// Constructor
	~LoseScene();									// Destructor

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

	void GUI_Event_Manager(GUI_Event type, j1Element* element);

	void ExecuteTransition();						// Method that will trigger a new transition depending on the input received.

public:

	j1Element* continueButton = nullptr;
	j1Element* forestButton = nullptr;
	j1Element* snowButton = nullptr;
	j1Element* volcanoButton = nullptr;
	j1Element* backButton = nullptr;
	j1Element* Lose_Scene_UI = nullptr;
	j1Element* TryAgain = nullptr;

};

#endif 
