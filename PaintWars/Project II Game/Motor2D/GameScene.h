#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "j1Module.h"
#include "Scene.h"

struct SDL_Texture;
struct UI_HUD
{
	j1Element* Shop_Button;
};
class GameScene : public Scene
{
public:

	GameScene();									// Constructor
	~GameScene();									// Destructor

	bool Awake(pugi::xml_node& config);				// Called before render is available
	bool Start();									// Called before the first frame
	bool PreUpdate();								// Called before all Updates
	bool Update(float dt);							// Called each loop iteration
	bool PostUpdate();								// Called before all Updates
	bool CleanUp();									// Called before quitting


	//CAMERA

	//UI
	void GUI_Event_Manager(GUI_Event type, j1Element* element);
	void ManageMinimap();

	//MAP & SCENE 
	void Map_Manager();
	void Create_Forest_Map();
	void Create_Snow_Map();
	void Create_Volcano_Map();
	//SCENE TRANSITIONS
	void InitScene();								// Method that will be used to initialize all scene elements.
	void DrawScene();
	void ExecuteTransition();
	void WIN_LOSE_Manager();
	void DebugDrawTile(iPoint tile);

public:
	//void InitScene();								// Method that will be used to initialize all scene elements.
	
	//void DrawScene();								// Method that will draw all scene elements on screen.
	//SDL_Texture* SceneToTexture();				// Method that will be used to get a texture from the current screen.

	//void ExecuteTransition();						// Method that will trigger a new transition depending on the input received.

public:

	//MAP MANAGER
	bool LoadingMap;
	bool Forest_Map_Active;
	bool Volcano_Map_Active;
	bool Snow_Map_Active;
	bool Load_Forest_Map;
	bool Load_Volcano_Map;
	bool Load_Snow_Map;
	bool Change_Map;


	
	//////////////////
	//      UI      //
	//////////////////


	UI_HUD UI_INGAME;

	//HUD - Bar
	j1Element* hudBarImage = nullptr;
	j1Element* paintLabel = nullptr;
	j1Element* woodLabel = nullptr;
	j1Element* metalLabel = nullptr;
	j1Element* titaniumLabel = nullptr;
	j1Element* foodLabel = nullptr;
	j1Element* researchLabel = nullptr;
	j1Element* entitiesImage = nullptr;
	j1Element* entitiesLabel = nullptr;

	// HUD - Quests
	j1Element* questsImage = nullptr;
	j1Element* questsLabel = nullptr;
	j1Element* questsOpenButton = nullptr;
	j1Element* questsCloseButton = nullptr;

	//HUD - Buttons
	j1Element* homeButton = nullptr;
	j1Element* pauseMenuButton = nullptr;
	bool pauseMenu = false;
	j1Element* shopButton = nullptr;
	j1Element* restartButton = nullptr;
	bool restartMenu = false;

	//HUD - Mini-map
	j1Element* miniMapBack = nullptr;
	j1Element* miniMapMINI = nullptr;
	j1Element* miniMapFULL = nullptr;
	j1Element* miniMapCamera = nullptr;
	//Pause Menu
	j1Element* pauseMenuImage = nullptr;
	j1Element* pauseMenuLabel = nullptr;
	j1Element* resumeButton = nullptr;
	j1Element* saveButton = nullptr;
	j1Element* settingsButton = nullptr;
	bool settingsMenu = false;
	j1Element* mainMenuButton = nullptr;
	bool mainMenu = false;
	j1Element* exitButton = nullptr;
	bool exitMenu = false;

	//Pause Menu - Settings Menu
	j1Element* musicLabel = nullptr;
	j1Element* vfxLabel = nullptr;
	j1Element* fullscreenLabel = nullptr;
	j1Element* gpadLabel = nullptr;
	j1Element* musicScroll = nullptr;
	j1Element* vfxScroll = nullptr;
	j1Element* fullscreenButton = nullptr;
	j1Element* gpadButton = nullptr;
	j1Element* resetButton = nullptr;
	j1Element* backButton = nullptr;

	// Exit / Restart / Main Menu Menu
	j1Element* exitMenuImage = nullptr;
	j1Element* exitMenuLabel = nullptr;
	j1Element* exitTextLabel = nullptr;
	j1Element* yesButton = nullptr;
	j1Element* noButton = nullptr;

	// Shop
	j1Element* shopImage = nullptr;
	j1Element* shopLabel = nullptr;
	j1Element* buyPaintExtractorButton = nullptr;
	j1Element* buyWoodProducerButton = nullptr;
	j1Element* buyBarrackButton = nullptr;
	bool debugTile = true;


	//Resource Values for Blit

	char Wood_Amount_UI;

	char Paint_Amount_UI;

	char Titanium_Amount_UI;

	char Housing_Amount_UI;

	char Max_Housing_Amount_UI;
	
private:

	SDL_Texture* debug_tex = nullptr;

	
	

};

#endif // __FIRSTSCENE_H__