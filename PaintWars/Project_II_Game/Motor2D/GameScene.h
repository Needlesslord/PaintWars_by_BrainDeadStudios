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
	j1UIElement* questsText1 = nullptr;          //CREATE 1 PAINTER 
	j1UIElement* questsText2 = nullptr;          //CREATE 1 PAINT EXTRACTOR
	j1UIElement* questsText3 = nullptr;          //EXTRACT 150 PAINT
	j1UIElement* questsText4 = nullptr;          //UPGRADE BUILDING
	j1UIElement* questsText1Count = nullptr;
	j1UIElement* questsText2Count = nullptr;
	j1UIElement* questsText3Count = nullptr;
	j1UIElement* questsText4Count = nullptr;
	j1UIElement* questsCompleted1=nullptr;
	j1UIElement* questsCompleted2 = nullptr;
	j1UIElement* questsCompleted3 = nullptr;
	j1UIElement* questsCompleted4 = nullptr;

	

	bool PainterQuestCompleted;
	bool PaintExtractorQuestCompleted;
	bool ExtractPaintQuestCompleted;
	bool UpgradeEntityQuestCompleted;

	bool PainterQuestActive;
	bool PaintExtractorQuestActive;
	bool ExtractPaintQuestActive;
	bool UpgradeEntityQuestActive;


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
	j1UIElement* CostLabel = nullptr;
	j1UIElement* ExplanationHover = nullptr;
	j1UIElement* shopImage = nullptr;
	j1UIElement* shopLabel = nullptr;
	j1UIElement* buyPaintExtractorButton = nullptr;
	j1UIElement* buyWoodProducerButton = nullptr;
	j1UIElement* buyBarrackButton = nullptr;
	j1UIElement* buyHouseButton = nullptr;
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

	j1UIElement* priceLabel = nullptr;
	int priceTimer = 0;


	// Buildings
	j1UIElement* buyPainterButton = nullptr;
	j1UIElement* buyWarriorButton = nullptr;
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

	bool DialogPage1;
	bool DialogPage2;
	bool DialogPage3;
	bool DialogPage4;
	bool DialogPage5;
	bool DialogPage6;

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