#ifndef __STARTSCENE_H__
#define __STARTSCENE_H__

#include "j1Module.h"
#include "Scene.h"

class StartScene : public Scene
{
public:

	StartScene();									// Constructor
	~StartScene();									// Destructor

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
	j1UIElement* backgroundImage = nullptr;
	j1UIElement* Loading_1 = nullptr;
	j1UIElement* Loading_2 = nullptr;
	j1UIElement* Loading_3 = nullptr;

	j1UIElement* Continue_Text = nullptr;
	j1UIElement* Volcano_Text = nullptr;
	j1UIElement* Forest_Text = nullptr;
	j1UIElement* Snow_Text = nullptr;
	j1UIElement* Back_Text = nullptr;



private:

	bool ResetPosition;
	bool FinishedPosition;
};

#endif // __FIRSTSCENE_H__
