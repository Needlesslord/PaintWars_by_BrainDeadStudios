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

	void Generate_Forest_Map();
	void Generate_Snow_Map();
	void Generate_Volcano_Map();
	void Generate_Entities();
	void Generate_Tiles();
	//SCENE TRANSITIONS
	void InitScene();								// Method that will be used to initialize all scene elements.
	void DrawScene();
	void ExecuteTransition();
	void WIN_LOSE_Manager();
	void CreateDialogText();
	void DialogManagerFunction();
	void QuestManagerFunction();
	
	//bool EntityInCamera(Entity* entity);

public:
	//void InitScene();								// Method that will be used to initialize all scene elements.

	//void DrawScene();								// Method that will draw all scene elements on screen.
	//SDL_Texture* SceneToTexture();				// Method that will be used to get a texture from the current screen.

	//void ExecuteTransition();						// Method that will trigger a new transition depending on the input received.

public:

	//MAP MANAGER



	const char* Map_Name_To_Load;


	//////////////////
	//      UI      //
	//////////////////

	j1UIElement* EntityHP = nullptr;

	UI_HUD UI_INGAME;

	j1UIElement* BackgroundForest = nullptr;
	j1UIElement* BackgroundVolcano = nullptr;
	j1UIElement* BackgroundSnow = nullptr;

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
	j1UIElement* timerLabel = nullptr;

	// HUD - Quests
	j1UIElement* questsImage = nullptr;
	j1UIElement* questsLabel = nullptr;
	j1UIElement* questsOpenButton = nullptr;
	j1UIElement* questsCloseButton = nullptr;
	j1UIElement* questsText1 = nullptr;          //CREATE 3 PAINTERS
	j1UIElement* questsText2 = nullptr;          //CREATE 1 BARRACKS
	j1UIElement* questsText3 = nullptr;          //EXTRACT 150 PAINT
	j1UIElement* questsText4 = nullptr;          //UPGRADE 1 WARRIOR
	j1UIElement* questsText5 = nullptr;          //FIND 1 EXPLORER
	j1UIElement* questsText6 = nullptr;          //DESTROY 1 SPAWNER
	j1UIElement* questsText1Count = nullptr;
	j1UIElement* questsText2Count = nullptr;
	j1UIElement* questsText3Count = nullptr;
	j1UIElement* questsText4Count = nullptr;
	j1UIElement* questsText5Count = nullptr;
	j1UIElement* questsText6Count = nullptr;
	j1UIElement* questsCompleted1= nullptr;
	j1UIElement* questsCompleted2 = nullptr;
	j1UIElement* questsCompleted3 = nullptr;
	j1UIElement* questsCompleted4 = nullptr;
	j1UIElement* questsCompleted5 = nullptr;
	j1UIElement* questsCompleted6 = nullptr;
	
	
	int painterscount;
	int spawnerscount;
	bool PaintersQuestCompleted;
	bool BarracksQuestCompleted;
	bool ExtractPaintQuestCompleted;
	bool UpgradeWarriorQuestCompleted;
	bool ExplorerQuestCompleted;
	bool DestroySpawnerQuestCompleted;

	bool PaintersQuestActive;
	bool BarracksQuestActive;
	bool ExtractPaintQuestActive;
	bool UpgradeWarriorQuestActive;
	bool ExplorerQuestActive;
	bool DestroySpawnerQuestActive;


	//HUD - Buttons
	j1UIElement* homeButton = nullptr;
	j1UIElement* pauseMenuButton = nullptr;
	bool pauseMenu = false;
	j1UIElement* shopButton = nullptr;
	j1UIElement* restartButton = nullptr;
	bool restartMenu = false;

	//HUD - Mini-map
	j1UIElement* miniMapBack = nullptr;
	j1UIElement* miniMapMINI_forest = nullptr;
	j1UIElement* miniMapFULL_forest = nullptr;
	j1UIElement* miniMapMINI_snow = nullptr;
	j1UIElement* miniMapFULL_snow = nullptr;
	j1UIElement* miniMapMINI_volcano = nullptr;
	j1UIElement* miniMapFULL_volcano = nullptr;
	j1UIElement* miniMapScopeCamera = nullptr;
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

	j1UIElement* fxSlider = nullptr;
	j1UIElement* fxBar = nullptr;
	j1UIElement* musicSlider = nullptr;
	j1UIElement* musicBar = nullptr;


	//Pause Menu - Settings Menu
	j1UIElement* musicLabel = nullptr;
	j1UIElement* vfxLabel = nullptr;
	j1UIElement* fullscreenLabel = nullptr;
	j1UIElement* gpadLabel = nullptr;

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
	j1UIElement* CostLabel = nullptr;
	j1UIElement* ExplanationHover = nullptr;
	j1UIElement* shopImage = nullptr;
	j1UIElement* shopLabel = nullptr;
	j1UIElement* buyPaintExtractorButton = nullptr;
	j1UIElement* buyWoodProducerButton = nullptr;
	j1UIElement* buyBarrackButton = nullptr;
	j1UIElement* buyHouseButton = nullptr;
	j1UIElement* buyMetalGathererButton = nullptr;
	j1UIElement* buyTitaniumExtractorButton = nullptr;
	j1UIElement* buyLaboratoryButton = nullptr;
	j1UIElement* buyTurretButton = nullptr;
	j1UIElement* upgradePaintExtractorButton = nullptr;
	j1UIElement* upgradeWoodProducerButton = nullptr;


	j1UIElement* shopHoverPrice = nullptr;
	/*j1UIElement* shopHoverWoodProducer = nullptr;
	j1UIElement* shopHoverBarracks = nullptr;
	j1UIElement* shopHoverHouse = nullptr;
	j1UIElement* shopHoverPainter = nullptr;
	j1UIElement* shopHoverWarrior = nullptr;
	j1UIElement* shopHoverUpgradeWarrior = nullptr;
	j1UIElement* shopHoverUpgradePainter = nullptr;
	j1UIElement* shopHoverUpgradeExtractor = nullptr;
	j1UIElement* shopHoverUpgradeWoodProducer = nullptr;*/

	// int priceTimer = 0;


	// Buildings
	j1UIElement* buyPainterButton = nullptr;
	j1UIElement* buyExplorerButton = nullptr;
	j1UIElement* buyWarriorButton = nullptr;
	j1UIElement* buyKnightButton = nullptr;
	j1UIElement* buyRangerButton = nullptr;
	j1UIElement* upgradePainterButton = nullptr;
	j1UIElement* upgradeWarriorButton = nullptr;

	// Dialogs

	j1UIElement* dialogOpen = nullptr;
	j1UIElement* dialogImage = nullptr;
	//j1UIElement* dialogCharacter = nullptr;
	j1UIElement* dialogText1 = nullptr;
	j1UIElement* dialogText2 = nullptr;
	j1UIElement* dialogText3 = nullptr;
	j1UIElement* dialogNext = nullptr;
	j1UIElement* dialogPrev = nullptr;
	j1UIElement* dialogClose = nullptr;

	bool movedstuff = false;


	//Animation

	j1UIElement* PaintRollerAnimation = nullptr;


	char* Dialog_Text1_Line_1 = nullptr;
	char* Dialog_Text1_Line_2 = nullptr;
	char* Dialog_Text1_Line_3 = nullptr;
	char* Dialog_Text2_Line_1 = nullptr;
	char* Dialog_Text2_Line_2 = nullptr;
	char* Dialog_Text2_Line_3 = nullptr;
	char* Dialog_Text3_Line_1 = nullptr;
	char* Dialog_Text3_Line_2 = nullptr;
	char* Dialog_Text3_Line_3 = nullptr;
	char* Dialog_Text4_Line_1 = nullptr;
	char* Dialog_Text4_Line_2 = nullptr;
	char* Dialog_Text4_Line_3 = nullptr;
	char* Dialog_Text5_Line_1 = nullptr;
	char* Dialog_Text5_Line_2 = nullptr;
	char* Dialog_Text5_Line_3 = nullptr;
	char* Dialog_Text6_Line_1 = nullptr;
	char* Dialog_Text6_Line_2 = nullptr;
	char* Dialog_Text6_Line_3 = nullptr;
	char* Dialog_Text7_Line_1 = nullptr;
	char* Dialog_Text7_Line_2 = nullptr;
	char* Dialog_Text7_Line_3 = nullptr;
	char* Dialog_Text8_Line_1 = nullptr;
	char* Dialog_Text8_Line_2 = nullptr;
	char* Dialog_Text8_Line_3 = nullptr;
	char* Dialog_Text9_Line_1 = nullptr;
	char* Dialog_Text9_Line_2 = nullptr;
	char* Dialog_Text9_Line_3 = nullptr;
	char* Dialog_Text10_Line_1 = nullptr;
	char* Dialog_Text10_Line_2 = nullptr;
	char* Dialog_Text10_Line_3 = nullptr;
	char* Dialog_Text11_Line_1 = nullptr;
	char* Dialog_Text11_Line_2 = nullptr;
	char* Dialog_Text11_Line_3 = nullptr;
	char* Dialog_Text12_Line_1 = nullptr;
	char* Dialog_Text12_Line_2 = nullptr;
	char* Dialog_Text12_Line_3 = nullptr;
	char* Dialog_Text13_Line_1 = nullptr;
	char* Dialog_Text13_Line_2 = nullptr;
	char* Dialog_Text13_Line_3 = nullptr;
	char* Dialog_Text14_Line_1 = nullptr;
	char* Dialog_Text14_Line_2 = nullptr;
	char* Dialog_Text14_Line_3 = nullptr;
	char* Dialog_Text15_Line_1 = nullptr;
	char* Dialog_Text15_Line_2 = nullptr;
	char* Dialog_Text15_Line_3 = nullptr;

	bool DialogPage1;
	bool DialogPage2;
	bool DialogPage3;
	bool DialogPage4;
	bool DialogPage5;
	bool DialogPage6;
	bool DialogPage7;
	bool DialogPage8;
	bool DialogPage9;
	bool DialogPage10;
	bool DialogPage11;
	bool DialogPage12;
	bool DialogPage13;
	bool DialogPage14;
	bool DialogPage15;

	bool DialogOperative;

	
	




	//Resource Values for Blit

	char Wood_Amount_UI;

	char Paint_Amount_UI;

	char Titanium_Amount_UI;

	char Housing_Amount_UI;

	char Max_Housing_Amount_UI;

private:

	int seconds;
	int minutes;
	int AnimTime;



};

#endif // __GAMESCENE_H__