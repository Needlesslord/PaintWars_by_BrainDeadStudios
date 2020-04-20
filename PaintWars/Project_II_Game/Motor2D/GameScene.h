#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "j1Module.h"
#include "Scene.h"

struct SDL_Texture;
struct UI_HUD
{
	j1UIElement* Shop_Button;
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
	void GUI_Event_Manager(GUI_Event type, j1UIElement* element);
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

	//bool EntityInCamera(Entity* entity);

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
	j1UIElement* hudBarImage = nullptr;
	j1UIElement* paintLabel = nullptr;
	j1UIElement* woodLabel = nullptr;
	j1UIElement* metalLabel = nullptr;
	j1UIElement* titaniumLabel = nullptr;
	j1UIElement* foodLabel = nullptr;
	j1UIElement* researchLabel = nullptr;
	j1UIElement* entitiesImage = nullptr;
	j1UIElement* entitiesLabel = nullptr;
	j1UIElement* BackgroundForest = nullptr;

	// HUD - Quests
	j1UIElement* questsImage = nullptr;
	j1UIElement* questsLabel = nullptr;
	j1UIElement* questsOpenButton = nullptr;
	j1UIElement* questsCloseButton = nullptr;

	//HUD - Buttons
	j1UIElement* homeButton = nullptr;
	j1UIElement* pauseMenuButton = nullptr;
	bool pauseMenu = false;
	j1UIElement* shopButton = nullptr;
	j1UIElement* restartButton = nullptr;
	bool restartMenu = false;

	//HUD - Mini-map
	j1UIElement* miniMapBack = nullptr;
	j1UIElement* miniMapMINI = nullptr;
	j1UIElement* miniMapFULL = nullptr;
	j1UIElement* miniMapCamera = nullptr;
	j1UIElement* miniMapBackground = nullptr;

	//Pause Menu
	j1UIElement* pauseMenuImage = nullptr;
	j1UIElement* pauseMenuLabel = nullptr;
	j1UIElement* resumeButton = nullptr;
	j1UIElement* saveButton = nullptr;
	j1UIElement* settingsButton = nullptr;
	bool settingsMenu = false;
	j1UIElement* mainMenuButton = nullptr;
	bool mainMenu = false;
	j1UIElement* exitButton = nullptr;
	bool exitMenu = false;

	//Pause Menu - Settings Menu
	j1UIElement* musicLabel = nullptr;
	j1UIElement* vfxLabel = nullptr;
	j1UIElement* fullscreenLabel = nullptr;
	j1UIElement* gpadLabel = nullptr;

	j1UIElement* vfxScroll = nullptr;
	j1UIElement* fullscreenButton = nullptr;
	j1UIElement* gpadButton = nullptr;
	j1UIElement* resetButton = nullptr;
	j1UIElement* backButton = nullptr;

	// Exit / Restart / Main Menu Menu
	j1UIElement* exitMenuImage = nullptr;
	j1UIElement* exitMenuLabel = nullptr;
	j1UIElement* exitTextLabel = nullptr;
	j1UIElement* yesButton = nullptr;
	j1UIElement* noButton = nullptr;

	// Shop
	j1UIElement* shopImage = nullptr;
	j1UIElement* shopLabel = nullptr;
	j1UIElement* buyPaintExtractorButton = nullptr;
	j1UIElement* buyWoodProducerButton = nullptr;
	j1UIElement* buyBarrackButton = nullptr;
	j1UIElement* buyHouseButton = nullptr;
	j1UIElement* upgradePaintExtractorButton = nullptr;
	j1UIElement* upgradeWoodProducerButton = nullptr;


	// Buildings
	j1UIElement* buyPainterButton = nullptr;
	j1UIElement* buyWarriorButton = nullptr;
	j1UIElement* upgradePainterButton = nullptr;
	j1UIElement* upgradeWarriorButton = nullptr;



	//Resource Values for Blit

	char Wood_Amount_UI;

	char Paint_Amount_UI;

	char Titanium_Amount_UI;

	char Housing_Amount_UI;

	char Max_Housing_Amount_UI;
	
private:



	
	

};

#endif // __FIRSTSCENE_H__