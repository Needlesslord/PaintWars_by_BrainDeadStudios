#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "GameScene.h"
#include "TransitionManager.h"
#include "j1UIElements.h"
#include "j1UI_manager.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Brofiler/Brofiler.h"
#include "j1Player.h"


/*
DEBUG KEYS
	 + F2/F3 Game Scene
	 + F4 Save
	 + F5 Load (Load function not functional yet)
	 + F6 Full Screen
	 + F7 Direct Win
	 + F8 Direct Lose
	 + F9 Collisions
	 + F10 God Mode (add resources, buildings and units, can't lose, collisions)
		resources
		- 1 add 10 paint
		- 2 add 10 wood
		- 3 add 10 metal scrap -not implemented yet-
		- 4 add 10 titanium -not implemented yet-
		- 5 add 10 food -not implemented yet-
		- 6 add 10 max housing
		- 7 add 1 level of research (units will have the upgrades already)
		units (on mouse position)
		- KP 1 add painter
		- KP 2 add warrior
		- KP 3 add ranged -not implemented yet-
		- KP 4 add tank -not implemented yet-
		- KP 5 add explorer -not implemented yet-
		- KP 0 kill selected units
		buildings (on mouse position)
		- Crtl + KP 1 add paint extractor
		- Crtl + KP 2 add wood producer
		- Crtl + KP 3 add barracks
		- Crtl + KP 4 add house
		- Crtl + KP 0 kill selected buildings
	 + H Go to Town Hall
	 + P Pause
	 + S/L Save/Load (only save implemented)
	 + ESC exit game (not in game scene)
	 + N/M/R Zoom In/Out/Reset
	 + KP MINUS/KP PLUS Control Framerate (+/- 10)
		 + UP/DOWN/LEFT/RIGHT Camera movement
*/

GameScene::GameScene() : Scene(SCENES::GAME_SCENE)
{

}

// Destructor
GameScene::~GameScene()
{

}

// Called before render is available
bool GameScene::Awake(pugi::xml_node& config)
{
	LOG("Loading FirstScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool GameScene::Start()
{
	bool ret = true;
	
	CreateDialogText();
	App->PAUSE_ACTIVE = false;
	DialogOperative = false;
	App->render->camera.x = 575;
	App->render->camera.y = -1200;

	
	Map_Manager();

	int w, h;
	uchar* data = NULL;
	if (App->map->CreateWalkabilityMap(w, h, &data))
	{
		App->pathfinding->SetMap(w, h, data);						// Sets a new walkability map with the map passed by CreateWalkabilityMap().

	}

	Generate_Entities();
	Generate_Tiles();

	App->scenes->IN_GAME_SCENE = true;


	//////////////////
	//      UI      //
	//////////////////
	
	
	//HUD - Bar
	hudBarImage = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 5 }, { 0 , 0 }, false, true, { 0, 1353, 1250, 35 }, nullptr, nullptr, TEXTURE::ATLAS_SPRITE);
	paintLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 120 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 },"0", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL);
	woodLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 240 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "0", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL);
	metalLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 360 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "0", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL);
	titaniumLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 480 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "0", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL);
	researchLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 600 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "0", nullptr,  TEXTURE::ATLAS, FONT::FONT_SMALL);
	entitiesLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 720 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "0", nullptr,  TEXTURE::ATLAS, FONT::FONT_SMALL);
	EntityHP = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 1050 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "999", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL);
	//BackgroundForest = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 5 }, { 0 , 0 }, false, true, { 0, 1353, 1250, 35 }, nullptr, nullptr, TEXTURE::BACKGROUND_FOREST);


	//HUD - Quests
	questsImage = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 50 }, { 0 , 0 }, false, true, { 0, 1388, 263, 40 }, nullptr, nullptr, TEXTURE::ATLAS_SPRITE);
	questsLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 15 , 52 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "QUESTS", nullptr,  TEXTURE::ATLAS, FONT::FONT_SMALL_WHITE);
	questsOpenButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 120, 65 }, { 200,200 }, true, true, { 317, 1388, 54, 55}, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 2);
	questsOpenButton->hover_rect = { 317, 1443, 54, 54 };
	questsOpenButton->click_rect = { 317, 1497, 54, 54 };
	questsCloseButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 120, 380 }, { 200,200 }, true, false, { 263, 1388, 54, 55 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 2);
	questsCloseButton->hover_rect = { 263, 1443, 54, 54 };
	questsCloseButton->click_rect = { 263, 1497, 54, 54 };

	questsText1 = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 90 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " Create 1 Painter", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText1Count = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 120 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " 0/1", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText2 = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 160 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " Create 1 Paint", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText2Count = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 190 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " Extractor 0/1", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText3 = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 230 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " Extract Paint", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText3Count = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 260 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " 0/150", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText4 = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 300 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " Upgrade 1 Building", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText4Count = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 330 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " 0/1", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);


	//HUD - Dialog

	dialogImage = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 300 , 575 }, { 0 , 0 }, false,true, { 0, 1820, 500, 125 }, nullptr, nullptr, TEXTURE::ATLAS);
	//dialogCharacter = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 300 , 575 }, { 0 , 0 }, true, true, { 276, 1972, 30, 28 }, nullptr, nullptr, TEXTURE::ATLAS);
	dialogClose = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 780 , 570 }, { 0 , 0 }, true, true, { 670, 1392, 28, 28 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 2);
	dialogClose->hover_rect = { 636, 1392, 28, 28 };
	dialogClose->click_rect = { 601, 1392, 28, 28 };
	dialogText1 = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 330 , 600 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "DIALOG SYSTEM ", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL_WHITE);
	dialogText2 = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 330 , 630 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "DIALOG SYSTEM ", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL_WHITE);
	dialogText3 = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 330 , 660 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "DIALOG SYSTEM ", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL_WHITE);
	dialogPrev = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 695 , 660 }, { 0 , 0 }, true, true, { 499, 1431, 27, 28 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM,2);
	dialogPrev->hover_rect = {457,1432,27,28};
	dialogPrev->click_rect = {415,1432,27,28};
	dialogNext = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 765 , 660 }, { 0 , 0 }, true, true, { 499, 1398, 27, 28 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM,2);
	dialogNext->hover_rect = { 457,1398,27,28 };
	dialogNext->click_rect = { 415,1398,27,28 };
	//dialogOpen = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 500 , 660 }, { 0 , 0 }, true, true, { 425, 1468, 34, 74 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 2);
	dialogOpen = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 500 , 550 }, { 0 , 0 }, true, true, { 535, 1593, 73, 154 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 2);
	dialogOpen->hover_rect = { 535, 1593, 73, 154 };
	dialogOpen->click_rect = { 535, 1593, 73, 154 };
	//dialogExit = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 40 , 575 }, { 0 , 0 }, false, true, { 0, 1820, 500, 125 }, nullptr, nullptr, TEXTURE::ATLAS_SPRITE);


	//HUD - Buttons
	homeButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 1020, 50 }, { 0,0 }, true, true, { 786, 486, 55, 55 }, nullptr, App->scenes,  TEXTURE::ATLAS);
	homeButton->hover_rect = { 785, 560, 55, 55 };
	homeButton->click_rect = { 785, 634, 55, 55 };
	shopButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 1080, 50 }, { 0,0 }, true, true, { 786, 243, 55, 55 }, nullptr, App->scenes, TEXTURE::ATLAS);
	shopButton->hover_rect = { 785, 316, 55, 55 };
	shopButton->click_rect = { 785, 389, 55, 55 };
	pauseMenuButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 1140, 50 }, { 0,0 }, true, true, { 933, 243, 55, 55 }, nullptr, App->scenes,  TEXTURE::ATLAS);
	pauseMenuButton->hover_rect = { 933, 316, 55, 55 };
	pauseMenuButton->click_rect = { 933, 389, 55, 55 };
	restartButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 1200, 50 }, { 0,0 }, true, true, { 859, 486, 55, 55 }, nullptr, App->scenes, TEXTURE::ATLAS);
	restartButton->hover_rect = { 859, 560, 55, 55 };
	restartButton->click_rect = { 859, 634, 55, 55 };

	
	//Pause Menu
	pauseMenuImage = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 400 , 70 }, { 0 , 0 }, false, false, { 263, 729, 452, 623 }, nullptr, nullptr, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 5);
	pauseMenuLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, pauseMenuImage, { 550 , 100 }, { 2 , 2 }, false, false, { 0, 0, 0, 0 }, "PAUSE", nullptr, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 6);
	resumeButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, pauseMenuImage, { 510, 230 }, { 30,20 }, true, false, { 0, 91, 234, 80 }, "RESUME", App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 6);
	resumeButton->hover_rect = { 263, 91, 234, 80 };
	resumeButton->click_rect = { 525, 91, 234, 80 };
	saveButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, pauseMenuImage, { 525, 320 }, { 50,15 }, true, false, { 0, 415, 207, 71 }, "Save", App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 6);
	saveButton->hover_rect = { 263, 415, 207, 71 };
	saveButton->click_rect = { 525, 415, 207, 71 };
	settingsButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, pauseMenuImage, { 525, 400 }, { 15,20 }, true, false, { 0, 415, 207, 71 }, "Settings", App->scenes,  TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	settingsButton->hover_rect = { 263, 415, 207, 71 };
	settingsButton->click_rect = { 525, 415, 207, 71 };
	mainMenuButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, pauseMenuImage, { 540, 490 }, { 30,15 }, true, false, { 1106, 359, 166, 56 }, "Title", App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	mainMenuButton->hover_rect = { 1272, 359, 165, 56 };
	mainMenuButton->click_rect = { 1437, 359, 166, 56 };
	exitButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, pauseMenuImage, { 540, 560 }, { 40,15 }, true, false, { 1106, 359, 166, 56 }, "EXIT", App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	exitButton->hover_rect = { 1272, 359, 165, 56 };
	exitButton->click_rect = { 1437, 359, 166, 56 };

	//Pause Menu - Settings Menu
	musicLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, pauseMenuImage, { 455, 230 }, { 0, 0 }, false, false, { 0, 0, 0, 0 }, "Mus", App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	vfxLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, pauseMenuImage, { 455, 300 }, { 0, 0 }, false, false, { 0, 0, 0, 0 }, "VFX", App->scenes,  TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	fullscreenLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, pauseMenuImage, { 455, 370 }, { 0, 0 }, false, false, { 0, 0, 0, 0 }, "Fullscr", App->scenes,  TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	gpadLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, pauseMenuImage, { 455, 440 }, { 0, 0 }, false, false, { 0, 0, 0, 0 }, "GamePad", App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);

	fullscreenButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, pauseMenuImage, { 635, 360 }, { 0,0 }, true, false, { 0, 1031, 182, 58 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 6);
	fullscreenButton->hover_rect = { 0, 1031, 182, 58 };
	fullscreenButton->click_rect = { 0, 1031, 182, 58 };
	gpadButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, pauseMenuImage, { 635, 430 }, { 0,0 }, true, false, { 0, 1031, 182, 58 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 6);
	gpadButton->hover_rect = { 0, 1031, 182, 58 };
	gpadButton->click_rect = { 0, 1031, 182, 58 };
	resetButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, pauseMenuImage, { 535, 500 }, { 30,15 }, true, false, { 1106, 359, 166, 56 }, "Reset", App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	resetButton->hover_rect = { 1272, 359, 165, 56 };
	resetButton->click_rect = { 1437, 359, 166, 56 };
	backButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, pauseMenuImage, { 655, 580 }, { 40,15 }, true, false, { 1106, 359, 166, 56 }, "BACK", App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	backButton->hover_rect = { 1272, 359, 165, 56 };
	backButton->click_rect = { 1437, 359, 166, 56 };

	// Exit / Restart / Main Menu Menu
	exitMenuImage = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 380 , 200 }, { 0 , 0 }, false, false, { 787, 729, 490, 336 }, nullptr, nullptr, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 5);
	exitMenuLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, exitMenuImage, { 530 , 215 }, { 2 , 2 }, false, false, { 0, 0, 0, 0 }, "EXIT", nullptr, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 6);
	exitTextLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, exitMenuImage, { 460 , 350}, { 2 , 2 }, false, false, { 0, 0, 0, 0 }, "Are you sure", nullptr, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 6);
	yesButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, exitMenuImage, { 450, 430 }, { 50,15 }, true, false, { 1106, 243, 165, 58 }, "YES", App->scenes,TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	yesButton->hover_rect = { 1272, 243, 165, 58 };
	yesButton->click_rect = { 1437, 243, 166, 58 };
	noButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, exitMenuImage, { 650, 432 }, { 60,15 }, true, false, { 1106, 359, 165, 57 }, "NO", App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	noButton->hover_rect = { 1272, 359, 165, 57 };
	noButton->click_rect = { 1437, 359, 166, 57 };

	// Shop
	shopImage = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15 , 450 }, { 0 , 0 }, false, false, { 263, 1551, 263, 265 }, nullptr, nullptr, TEXTURE::ATLAS);
	shopLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, shopImage, { 15 , 452 }, { 2 , 2 }, false, false, { 0, 0, 0, 0 }, "SHOP", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL_WHITE);
	buyWoodProducerButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, shopImage, { 15, 485 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyWoodProducerButton->hover_rect = { 0, 1966, 65, 82 };
	buyWoodProducerButton->click_rect = { 65, 1966, 65, 82 };
	buyPaintExtractorButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, shopImage, { 80, 485 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyPaintExtractorButton->hover_rect = { 0, 1966, 65, 82 };
	buyPaintExtractorButton->click_rect = { 65, 1966, 65, 82 };
	buyBarrackButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, shopImage, { 145, 485 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyBarrackButton->hover_rect = { 0, 1966, 65, 82 };
	buyBarrackButton->click_rect = { 65, 1966, 65, 82 };
	buyHouseButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, shopImage, { 210, 485 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyHouseButton->hover_rect = { 0, 1966, 65, 82 };
	buyHouseButton->click_rect = { 65, 1966, 65, 82 };
	upgradeWoodProducerButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15, 567 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	upgradeWoodProducerButton->hover_rect = { 0, 1966, 65, 82 };
	upgradeWoodProducerButton->click_rect = { 65, 1966, 65, 82 };
	upgradePaintExtractorButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 80, 567 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	upgradePaintExtractorButton->hover_rect = { 0, 1966, 65, 82 };
	upgradePaintExtractorButton->click_rect = { 65, 1966, 65, 82 };


	//HUD - MiniMap

	miniMapBackground = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 850 , 500 }, { 0 , 0 }, false, true, { 0, 1750, 422, 210 }, nullptr, nullptr, TEXTURE::ATLAS_SPRITE);

	miniMapMINI = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 850 , 500 }, { 0,0 }, true, true, { 30, 15, 422,210 }, nullptr, App->scenes, TEXTURE::MINIMAP_MINI);
	miniMapMINI->click_rect = { 30, 15, 422,210 };
	miniMapMINI->hover_rect = { 30, 15, 422,210 };

	miniMapCamera = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 1025, 500 }, { 0 , 0 }, false, true, { 0, 0, 70, 36 }, nullptr, nullptr, TEXTURE::MINIMAP_CAMERA);

	miniMapBack = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0 , 0 }, { 0 , 0 }, false, false, { 0, 0, 1800, 1300 }, nullptr, nullptr,  TEXTURE::MINIMAP_BACK_SPRITE);

	miniMapFULL = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 50 , 75 }, { 0 , 0 }, true, false, { 87, 40, 1170,588 }, nullptr, App->scenes, TEXTURE::MINIMAP_FULL);
	miniMapFULL->click_rect = { 87, 40, 1170,588 };
	miniMapFULL->hover_rect = { 87, 40, 1170,588 };


	//Buildings

	upgradePainterButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 80, 485 }, { 0,0 }, true, false, { 130, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	upgradePainterButton->hover_rect = { 390, 1966, 65, 82 };
	upgradePainterButton->click_rect = { 750, 1966, 65, 82 };
	buyPainterButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15, 485 }, { 0,0 }, true, false, { 260, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyPainterButton->hover_rect = { 520, 1966, 65, 82 };
	buyPainterButton->click_rect = { 780, 1966, 65, 82 };
	upgradeWarriorButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 80, 485 }, { 0,0 }, true, false, { 195, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	upgradeWarriorButton->hover_rect = { 455, 1966, 65, 82 };
	upgradeWarriorButton->click_rect = { 715, 1966, 65, 82 };
	buyWarriorButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15, 485 }, { 0,0 }, true, false, { 325, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyWarriorButton->hover_rect = { 585, 1966, 65, 82 };
	buyWarriorButton->click_rect = { 845, 1966, 65, 82 };
	

	

	//////////////////
	//	RESOURCES	//
	//////////////////

	App->player->paintCount.type = RESOURCE_TYPE_PAINT;
	App->player->paintCount.count = 50;

	App->player->woodCount.type = RESOURCE_TYPE_WOOD;
	App->player->woodCount.count = 50;
	
	App->player->housingSpace.type = RESOURCE_TYPE_HOUSING;
	App->player->housingSpace.count = 1;
	App->player->housingSpace.maxCount = 5;


	if (App->audio->PlayingMenuMusic == true) {
		Mix_HaltMusic();
		App->audio->PlayingMenuMusic = false;
	}

	if (App->audio->PlayingIngameAudio != true) {
		App->audio->PlayMusic("audio/music/music_sadpiano.ogg");
		App->audio->PlayingIngameAudio = true;
	}

	App->player->gameTimer.Start();

	App->player->cricketsRepeat.Start();

	App->fow->SetVisibilityMap(App->map->data.width, App->map->data.height);


	return ret;
}

// Called each loop iteration
bool GameScene::PreUpdate()
{

	bool ret = true;


	

	// Debug pathfinding ------------------
	static iPoint origin;
	static bool origin_selected = false;

	fPoint mouseWP = App->input->GetMouseWorldPosition();
	iPoint p = App->map->WorldToMap(mouseWP.x, mouseWP.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (origin_selected == true)
		{
			//App->pathfinding->CreatePath(origin, p);                  CRASHES WITH THE NEW PATHFINDING
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	QuestManagerFunction();
	DialogManagerFunction();


	return ret;
}

// Called each loop iteration
bool GameScene::Update(float dt)
{
	BROFILER_CATEGORY("Game Scene Update--Scenes();", Profiler::Color::GhostWhite);
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
		

	}

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {

		App->scenes->exit = true;
	}
	
	bool ret = true;
	
	CameraDebugMovement(dt);

	

	App->map->Draw();

	fPoint xy = App->input->GetMouseWorldPosition();
	iPoint cameraW = App->map->WorldToMap(App->render->camera.x, App->render->camera.y);
	iPoint map_coordinates = App->map->WorldToMap(xy.x - cameraW.x /*+ App->map->data.tile_width / 2*/, xy.y - cameraW.y + App->map->data.tile_height/2);

	static char title[256];
	sprintf_s(title, 256, "WorldPosition:%d,%d", map_coordinates, map_coordinates.y);

	App->win->SetTitle(title);

	fPoint worldCoordinates = App->map->MapToWorld(map_coordinates.x, map_coordinates.y);

	iPoint transformer1, transformer2;
	transformer1.x = worldCoordinates.x; transformer1.y = worldCoordinates.y;
	transformer2.x = xy.x; transformer2.y = xy.y;

	 seconds = App->player->gameTimer.ReadSec();
	 minutes = 0;
	for (int i = 0; i < 17; i++) {
		if (seconds > 59) {
			seconds -= 60;
			if (minutes == i) 
				minutes++;
		}
	}

	static char conversorChar1[256];
	int conversorInt1 = App->player->paintCount.count;
	sprintf_s(conversorChar1, 256, "%d", conversorInt1);
	paintLabel->text = conversorChar1;

	static char conversorChar2[256];
	int conversorInt2 = App->player->woodCount.count;
	sprintf_s(conversorChar2, 256, "%d", conversorInt2);
	woodLabel->text = conversorChar2;

	static char conversorChar3[256];
	int conversorInt3 = App->player->housingSpace.count;
	int conversorInt4 = App->player->housingSpace.maxCount;
	sprintf_s(conversorChar3, 256, "%d/%d", conversorInt3, conversorInt4);
	entitiesLabel->text = conversorChar3;
	
	



	

	if ((App->player->gameTimer.ReadSec() / 60) >= 14.9f) {
		Mix_PlayChannel(-1, App->audio->time_sound, 0);
		if ((App->player->gameTimer.ReadSec() / 60) >= 15.0f) {
			App->transition_manager->CreateSlide(SCENES::LOSE_SCENE, 1.0f, true);

		}
	}

	if ((App->player->gameTimer.ReadSec() / 60) >= 0.05f) {

		Mix_PlayChannel(-1, App->audio->birds_sound, 0);


		if (App->player->cricketsRepeat.Read()/60 > 1) {
			Mix_PlayChannel(-1, App->audio->crickets_sound, 0);
			App->player->cricketsRepeat.Start();
		}
	}
	
	
	
	if (App->entities->entitiesSelected.size() == 1) {

		list<Entity*>::iterator showHp = App->entities->entitiesSelected.begin();
		int hp = (*showHp)->GetCurrLife();
		int maxHp = (*showHp)->GetMaxLife();

		static char conversor[256];
		sprintf_s(conversor, 256, "%d/%d", hp, maxHp);
		EntityHP->text = conversor;
	}
	else {

		static char conversor2[256];
		sprintf_s(conversor2, 256, " ");
		EntityHP->text = conversor2;
	}
	



	// If only the TH is selected enable the button
	list<Entity*>::iterator onlyTownhallSelected = App->entities->buildingsSelected.begin();
	if (App->entities->buildingsSelected.size() == 1 && (*onlyTownhallSelected)->entityType == ENTITY_TYPE_TOWN_HALL) {

		buyPainterButton->enabled = true;
		if (!App->entities->paintersUpgraded)
			upgradePainterButton->enabled = true;

		shopImage->enabled = false;
		shopLabel->enabled = false;
		buyWoodProducerButton->enabled = false;
		buyPaintExtractorButton->enabled = false;
		buyBarrackButton->enabled = false;
		buyHouseButton->enabled = false;
		upgradeWoodProducerButton->enabled = false;
		upgradePaintExtractorButton->enabled = false;
	}
	else {
		buyPainterButton->enabled = false;
		upgradePainterButton->enabled = false;
	}



	// If only the Barracks is selected enable the button
	list<Entity*>::iterator onlyBarracksSelected = App->entities->buildingsSelected.begin();
	if (App->entities->buildingsSelected.size() == 1 && (*onlyTownhallSelected)->entityType == ENTITY_TYPE_BARRACKS) {

		buyWarriorButton->enabled = true;
		if (!App->entities->warriorsUpgraded)
			upgradeWarriorButton->enabled = true;

		shopImage->enabled = false;
		shopLabel->enabled = false;
		buyWoodProducerButton->enabled = false;
		buyPaintExtractorButton->enabled = false;
		buyBarrackButton->enabled = false;
		buyHouseButton->enabled = false;
		upgradeWoodProducerButton->enabled = false;
		upgradePaintExtractorButton->enabled = false;
	}
	else {
		buyWarriorButton->enabled = false;
		upgradeWarriorButton->enabled = false;
	}



	fPoint MousePos = App->input->GetMouseWorldPosition();

	LOG("Mouse x at %f", MousePos.x);

	LOG("Mouse y at %f", MousePos.y);

	
	return ret;
}

// Called each loop iteration
bool GameScene::PostUpdate()
{
	BROFILER_CATEGORY("Game Scene PostUpdate--Scenes();", Profiler::Color::FloralWhite);
	bool ret = true;
	
	
	if (App->input->GetKey(SDL_SCANCODE_M) == true) {

		if (miniMapMINI->enabled == true) {
			miniMapBack->enabled = true;
			miniMapFULL->enabled = true;
			miniMapMINI->enabled = false;
			miniMapCamera->enabled = false;
		}
		else {
			miniMapMINI->enabled = true;
			miniMapBack->enabled = false;
			miniMapFULL->enabled = false;
			miniMapCamera->enabled = true;
		}
	}

	miniMapCamera->map_position.x = 0/*miniMapCamera->init_map_position.x+App->render->camera.x*-0.05*/;
	miniMapCamera->map_position.y = miniMapCamera->init_map_position.y + App->render->camera.y*-0.05;

	
	

	WIN_LOSE_Manager();

	ExecuteTransition();
		


	
	dialogImage->enabled;

	return ret;
}



// Called before quitting
bool GameScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;
	App->scenes->IN_GAME_SCENE = false;
	//App->map->CleanUp();

	App->scenes->Load_Map_Forest = false;
	App->scenes->Load_Map_Snow = false;
	App->scenes->Load_Map_Volcano = false;
	App->scenes->Map_Forest_Active = false;
	App->scenes->Map_Snow_Active = false;
	App->scenes->Map_Volcano_Active = false;

	//UI
	for (int i = 0; i < App->gui->GUI_ELEMENTS.count(); i++)
	{
		App->gui->GUI_ELEMENTS[i]->CleanUp();
		//RELEASE(App->gui->GUI_ELEMENTS[i]);
	}
	
	App->scenes->Timer_Minutes = minutes;
	App->scenes->Timer_Seconds = seconds;

	//hudBarImage									   ->CleanUp();
	// paintLabel 								   ->CleanUp();
	// woodLabel									   ->CleanUp();
	// metalLabel 								   ->CleanUp();
	// titaniumLabel 								   ->CleanUp();
	//// foodLabel 									   ->CleanUp();
	// researchLabel 								   ->CleanUp();
	//// entitiesImage 								   ->CleanUp();
	// entitiesLabel 								   ->CleanUp();
	// //BackgroundForest 							   ->CleanUp();
	// questsImage 								   ->CleanUp();
	// questsLabel 								   ->CleanUp();
	// questsOpenButton 							   ->CleanUp();
	// questsCloseButton 							   ->CleanUp();
	// questsText1           						   ->CleanUp();
	// questsText2          						   ->CleanUp();
	// questsText3           						   ->CleanUp();
	// questsText4          						   ->CleanUp();
	// questsText1Count 							   ->CleanUp();
	// questsText2Count 							   ->CleanUp();
	// questsText3Count 							   ->CleanUp();
	// questsText4Count 							   ->CleanUp();
	// //questsCompleted1 							   ->CleanUp();
	// //questsCompleted2 							   ->CleanUp();
	// //questsCompleted3 							   ->CleanUp();
	// //questsCompleted4 							   ->CleanUp();
	//	 hudBarImage 							   ->CleanUp();
	//	 paintLabel 							   ->CleanUp();
	//	 woodLabel 								   ->CleanUp();
	//	 metalLabel 							   ->CleanUp();
	//	 titaniumLabel							   ->CleanUp();
	//	 researchLabel							   ->CleanUp();
	//	 entitiesLabel							   ->CleanUp();
	//	 EntityHP 								   ->CleanUp();
	//	 questsImage 							   ->CleanUp();
	//	 questsLabel 							   ->CleanUp();
	//	 questsOpenButton						   ->CleanUp();
	//	 questsOpenButton 						   ->CleanUp();
	//	 questsOpenButton 						   ->CleanUp();
	//	 questsCloseButton						   ->CleanUp();
	//	 questsCloseButton						   ->CleanUp();
	//	 questsCloseButton						   ->CleanUp();
	//	 questsText1 							   ->CleanUp();
	//	 questsText1Count						   ->CleanUp();
	//	 questsText2 							   ->CleanUp();
	//	 questsText2Count						   ->CleanUp();
	//	 questsText3 							   ->CleanUp();
	//	 questsText3Count						   ->CleanUp();
	//	 questsText4 							   ->CleanUp();
	//	 questsText4Count						   ->CleanUp();
	//	 dialogImage							   ->CleanUp();
	//	 dialogClose							   ->CleanUp();
	//	 dialogClose							   ->CleanUp();
	//	 dialogClose							   ->CleanUp();
	//	 dialogText1							   ->CleanUp();
	//	 dialogText2							   ->CleanUp();
	//	 dialogText3							   ->CleanUp();
	//	 dialogPrev								   ->CleanUp();
	//	 dialogPrev 							   ->CleanUp();
	//	 dialogPrev 							   ->CleanUp();
	//	 dialogNext								   ->CleanUp();
	//	 dialogNext 							   ->CleanUp();
	//	 dialogNext 							   ->CleanUp();
	//	 dialogOpen								   ->CleanUp();
	//	 dialogOpen 							   ->CleanUp();
	//	 dialogOpen 							   ->CleanUp();
	//	  homeButton 							   ->CleanUp();
	//	 homeButton						           ->CleanUp();
	//	 homeButton								   ->CleanUp();
	//	 shopButton 							   ->CleanUp();
	//	 shopButton								   ->CleanUp();
	//	 shopButton								   ->CleanUp();
	//	 pauseMenuButton 						   ->CleanUp();
	//	 pauseMenuButton						   ->CleanUp();
	//	 pauseMenuButton						   ->CleanUp();
	//	 restartButton 							   ->CleanUp();
	//	 restartButton							   ->CleanUp();
	//	 restartButton							   ->CleanUp();
	//	 pauseMenuImage 						   ->CleanUp();
	//	 pauseMenuLabel 						   ->CleanUp();
	//	 resumeButton 							   ->CleanUp();
	//	 resumeButton							   ->CleanUp();
	//	 resumeButton							   ->CleanUp();
	//	 saveButton 							   ->CleanUp();
	//	 saveButton								   ->CleanUp();
	//	 saveButton								   ->CleanUp();
	//	 settingsButton 						   ->CleanUp();
	//	 settingsButton							   ->CleanUp();
	//	 settingsButton							   ->CleanUp();
	//	 mainMenuButton 						   ->CleanUp();
	//	 mainMenuButton							   ->CleanUp();
	//	 mainMenuButton							   ->CleanUp();
	//	 exitButton 							   ->CleanUp();
	//	 exitButton								   ->CleanUp();
	//	 exitButton								   ->CleanUp();
	//   musicLabel								   ->CleanUp();
	//   vfxLabel 								   ->CleanUp();
	//   fullscreenLabel 							   ->CleanUp();
	//   gpadLabel 								   ->CleanUp();
	//   fullscreenButton 						   ->CleanUp();
	//   fullscreenButton							   ->CleanUp();
	//   fullscreenButton							   ->CleanUp();
	//   gpadButton 								   ->CleanUp();
	//   gpadButton								   ->CleanUp();
	//   gpadButton								   ->CleanUp();
	//   resetButton								   ->CleanUp();
	//   resetButton								   ->CleanUp();
	//   resetButton								   ->CleanUp();
	//   backButton 								   ->CleanUp();
	//   backButton								   ->CleanUp();
	//   backButton								   ->CleanUp();
	//  exitMenuImage 							   ->CleanUp();
	//  exitMenuLabel 							   ->CleanUp();
	//  exitTextLabel 							   ->CleanUp();
	//  yesButton 								   ->CleanUp();
	//  yesButton									   ->CleanUp();
	//  yesButton									   ->CleanUp();
	//  noButton 									   ->CleanUp();
	//  noButton									   ->CleanUp();
	//  noButton									   ->CleanUp();
	// shopImage 									   ->CleanUp();
	// shopLabel 									   ->CleanUp();
	// buyWoodProducerButton 						   ->CleanUp();
	// buyWoodProducerButton						   ->CleanUp();
	// buyWoodProducerButton						   ->CleanUp();
	// buyPaintExtractorButton 					   ->CleanUp();
	// buyPaintExtractorButton					   ->CleanUp();
	// buyPaintExtractorButton					   ->CleanUp();
	// buyBarrackButton 							   ->CleanUp();
	// buyBarrackButton							   ->CleanUp();
	// buyBarrackButton							   ->CleanUp();
	// buyHouseButton 							   ->CleanUp();
	// buyHouseButton								   ->CleanUp();
	// buyHouseButton								   ->CleanUp();
	// upgradeWoodProducerButton					   ->CleanUp();
	// upgradeWoodProducerButton					   ->CleanUp();
	// upgradeWoodProducerButton					   ->CleanUp();
	// upgradePaintExtractorButton 				   ->CleanUp();
	// upgradePaintExtractorButton				   ->CleanUp();
	// upgradePaintExtractorButton				   ->CleanUp();
	// miniMapBackground 							   ->CleanUp();
	// miniMapMINI								   ->CleanUp();
	// miniMapMINI								   ->CleanUp();
	// miniMapMINI								   ->CleanUp();
	// miniMapCamera 								   ->CleanUp();
	// miniMapBack 								   ->CleanUp();
	// miniMapFULL 								   ->CleanUp();
	// miniMapFULL								   ->CleanUp();
	// miniMapFULL								   ->CleanUp();
 //  upgradePainterButton 						   ->CleanUp();
 //  upgradePainterButton							   ->CleanUp();
 //  upgradePainterButton							   ->CleanUp();
 //  buyPainterButton 							   ->CleanUp();
 //  buyPainterButton								   ->CleanUp();
 //  buyPainterButton								   ->CleanUp();
 //  upgradeWarriorButton 						   ->CleanUp();
 //  upgradeWarriorButton							   ->CleanUp();
 //  upgradeWarriorButton							   ->CleanUp();
 //  buyWarriorButton 							   ->CleanUp();
 //  buyWarriorButton								   ->CleanUp();
 //  buyWarriorButton								   ->CleanUp();





		 //////////////////////
	if (scene_texture != nullptr)
	{
		App->tex->UnLoad(scene_texture);
	}

	if (tileset_texture != nullptr)
	{
		App->tex->UnLoad(tileset_texture);
	}

	if (SDL_RenderClear(scene_renderer) == 0)
	{
		scene_renderer = nullptr;
	}

	if (scene_surface != nullptr)
	{
		SDL_FreeSurface(scene_surface);
	}

	LOG("GAME SCENE CleanUP");


	return ret;
}

void GameScene::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{

	//Minimap

	if (element == miniMapMINI && type == GUI_Event::EVENT_ONCLICK) {
		
	}

	if (element == miniMapFULL && type == GUI_Event::EVENT_ONCLICK) {
		
	}


	//Quests

	if (element == questsOpenButton && type == GUI_Event::EVENT_ONCLICK)
	{
		questsImage->rect.h = 360;
		questsCloseButton->enabled = true;
		questsOpenButton->enabled = false;

	}

	if (element == questsCloseButton && type == GUI_Event::EVENT_ONCLICK)
	{
		questsImage->rect.h = 40;
		questsOpenButton->enabled = true;
		questsCloseButton->enabled = false;
	}

	//Dialog

	if (element == dialogOpen && type == GUI_Event::EVENT_ONCLICK) {

		

		DialogOperative = true;
		//dialogExit->enabled = true;
		

	}

	if (element == dialogClose && type == GUI_Event::EVENT_ONCLICK) {
 
		DialogOperative = false;
	}

	if (element == dialogNext && type == GUI_Event::EVENT_ONCLICK)
	{
		if (DialogPage1 == true) {
			DialogPage2 = true;
			DialogPage1 = false;
		}
		else if (DialogPage2 == true) {
			DialogPage3 = true;
			DialogPage2 = false;
		}
		else if (DialogPage3 == true) {
			DialogPage4 = true;
			DialogPage3 = false;
		}
		else if (DialogPage4 == true) {
			DialogPage5 = true;
			DialogPage4 = false;
		}
		else if (DialogPage5 == true) {
			DialogPage6 = true;
			DialogPage5 = false;
		}
		else if (DialogPage6 == true) {
			
		}
	 
	}

	if (element == dialogPrev && type == GUI_Event::EVENT_ONCLICK)
	{
		if (DialogPage1 == true) {
			
		}
		else if (DialogPage2 == true) {
			DialogPage1 = true;
			DialogPage2 = false;
		}
		else if (DialogPage3 == true) {
			DialogPage2 = true;
			DialogPage3 = false;
		}
		else if (DialogPage4 == true) {
			DialogPage3 = true;
			DialogPage4 = false;
		}
		else if (DialogPage5 == true) {
			DialogPage4 = true;
			DialogPage5 = false;
		}
		else if (DialogPage6 == true) {
			DialogPage5 = true;
			DialogPage6 = false;
		}
	}
	

	//HomeButton

	if (element == homeButton && type == GUI_Event::EVENT_ONCLICK)
	{
		App->render->camera.x = 575;
		App->render->camera.y = -1200;
	}


	//Shop

	if (element == shopButton && type == GUI_Event::EVENT_ONCLICK)
	{
		shopImage->enabled = !shopImage->enabled;
		shopLabel->enabled = !shopLabel->enabled;
		buyWoodProducerButton->enabled = !buyWoodProducerButton->enabled;
		buyPaintExtractorButton->enabled = !buyPaintExtractorButton->enabled;
		buyBarrackButton->enabled = !buyBarrackButton->enabled;
		buyHouseButton->enabled = !buyHouseButton->enabled;

		if (!App->entities->woodProducersUpgraded && !upgradeWoodProducerButton->enabled)
			upgradeWoodProducerButton->enabled = true;
		else if(!App->entities->woodProducersUpgraded && upgradeWoodProducerButton->enabled)
			upgradeWoodProducerButton->enabled = false;


		if (!App->entities->paintExtractorUpgraded && !upgradePaintExtractorButton->enabled)
			upgradePaintExtractorButton->enabled = true;
		else if (!App->entities->paintExtractorUpgraded && upgradePaintExtractorButton->enabled)
			upgradePaintExtractorButton->enabled = false;

	}

	if (element == buyPaintExtractorButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->entities->isSelectingPlacement != true) {
			App->entities->isSelectingPlacement = true;
			App->entities->hoveringEntityType = ENTITY_TYPE_PAINT_EXTRACTOR;
			Mix_PlayChannel(-1, App->audio->buy1_sound, 0);
			
		}

	}

	if (element == buyBarrackButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->entities->isSelectingPlacement != true) {
			App->entities->isSelectingPlacement = true;
			App->entities->hoveringEntityType = ENTITY_TYPE_BARRACKS;
			Mix_PlayChannel(-1, App->audio->buy2_sound, 0);
		}

	}

	if (element == buyWoodProducerButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->entities->isSelectingPlacement != true) {
			App->entities->isSelectingPlacement = true;

			App->entities->hoveringEntityType = ENTITY_TYPE_WOOD_PRODUCER;
			Mix_PlayChannel(-1, App->audio->buy2_sound, 0);
		}
	}

	if (element == buyHouseButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->entities->isSelectingPlacement != true) {
			App->entities->isSelectingPlacement = true;

			App->entities->hoveringEntityType = ENTITY_TYPE_HOUSE;
			Mix_PlayChannel(-1, App->audio->buy2_sound, 0);
		}
	}

	if (element == buyWoodProducerButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->entities->isSelectingPlacement != true) {
			App->entities->isSelectingPlacement = true;

			App->entities->hoveringEntityType = ENTITY_TYPE_PAINTER;
			Mix_PlayChannel(-1, App->audio->buy1_sound, 0);
		}
	}

	if (element == buyWoodProducerButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->entities->isSelectingPlacement != true) {
			App->entities->isSelectingPlacement = true;

			App->entities->hoveringEntityType = ENTITY_TYPE_WARRIOR;
			Mix_PlayChannel(-1, App->audio->buy1_sound, 0);
		}
	}

	if (element == upgradePaintExtractorButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->player->paintCount.count >= 200) {

			App->player->paintCount.count -= 200;
			list<Entity*>::iterator upgradeAllPaintExtractor = App->entities->activeBuildings.begin();
			while (upgradeAllPaintExtractor != App->entities->activeBuildings.end()) {

				if ((*upgradeAllPaintExtractor)->entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {

					(*upgradeAllPaintExtractor)->extractionRate *= 1.33f;
				}
				upgradeAllPaintExtractor++;
			}
			upgradePaintExtractorButton->enabled = false;
			App->entities->paintExtractorUpgraded = true;
			UpgradeEntityQuestCompleted = true;
		}
	}

	if (element == upgradeWoodProducerButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->player->paintCount.count >= 200) {

			App->player->paintCount.count -= 200;
			list<Entity*>::iterator upgradeAllWoodProducers = App->entities->activeBuildings.begin();
			while (upgradeAllWoodProducers != App->entities->activeBuildings.end()) {

				if ((*upgradeAllWoodProducers)->entityType == ENTITY_TYPE_WOOD_PRODUCER) {
					(*upgradeAllWoodProducers)->SetMaxLife((*upgradeAllWoodProducers)->GetMaxLife()*1.5);
					(*upgradeAllWoodProducers)->SetCurrLife((*upgradeAllWoodProducers)->GetMaxLife());
				}
				upgradeAllWoodProducers++;
			}
			upgradeWoodProducerButton->enabled = false;
			App->entities->woodProducersUpgraded = true;
			UpgradeEntityQuestCompleted = true;
		}
	}

	//Townhall shop

	if (element == buyPainterButton && type == GUI_Event::EVENT_ONCLICK) {
		list<Entity*>::iterator onlyTownhallSelected = App->entities->buildingsSelected.begin();
		(*onlyTownhallSelected)->SpawnEntity();
		PainterQuestCompleted = true;
	}
	else if (element == upgradePainterButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->player->paintCount.count >= 200) {

			App->player->paintCount.count -= 200;
			list<Entity*>::iterator upgradeAllPainters = App->entities->activeUnits.begin();
			while (upgradeAllPainters != App->entities->activeUnits.end()) {

				(*upgradeAllPainters)->extractionRate *= 1.33f;
				upgradeAllPainters++;
			}
			App->entities->paintersUpgraded = true;
		}
	}


	//Barracks shop

	if (element == buyWarriorButton && type == GUI_Event::EVENT_ONCLICK) {
		list<Entity*>::iterator onlyBarracksSelected = App->entities->buildingsSelected.begin();
		(*onlyBarracksSelected)->SpawnEntity();
	}
	else if (element == upgradeWarriorButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->player->paintCount.count >= 200) {

			App->player->paintCount.count -= 200;
			list<Entity*>::iterator upgradeAllWarriors = App->entities->activeUnits.begin();
			while (upgradeAllWarriors != App->entities->activeUnits.end()) {

				(*upgradeAllWarriors)->attackDamage *= 1.5f;
				upgradeAllWarriors++;
			}
			App->entities->warriorsUpgraded = true;
		}
	}


	//Pause Menu

	if (element == pauseMenuButton && type == GUI_Event::EVENT_ONCLICK)
	{
		App->PAUSE_ACTIVE = true;

		App->player->gameTimer.Stop();

		pauseMenu = true;
		pauseMenuImage->enabled = true;
		pauseMenuLabel->enabled = true;
		resumeButton->enabled = true;
		saveButton->enabled = true;
		settingsButton->enabled = true;
		mainMenuButton->enabled = true;
		exitButton->enabled = true;

		homeButton->interactable = false;
		pauseMenuButton->interactable = false;
		shopButton->interactable = false;
		restartButton->interactable = false;
		questsOpenButton->interactable = false;
		questsCloseButton->interactable = false;
	}
	
	if (element == resumeButton && type == GUI_Event::EVENT_ONCLICK)
	{
		App->PAUSE_ACTIVE = false;

		App->player->gameTimer.Resume();

		pauseMenu = false;
		pauseMenuImage->enabled = false;
		pauseMenuLabel->enabled = false;
		saveButton->enabled = false;
		settingsButton->enabled = false;
		mainMenuButton->enabled = false;
		exitButton->enabled = false;
		resumeButton->enabled = false;

		homeButton->interactable = true;
		pauseMenuButton->interactable = true;
		shopButton->interactable = true;
		restartButton->interactable = true;
		questsOpenButton->interactable = true;
		questsCloseButton->interactable = true;
	}


	if (element == settingsButton && type == GUI_Event::EVENT_ONCLICK)
	{
		pauseMenu = false;
		saveButton->enabled = false;
		settingsButton->enabled = false;
		mainMenuButton->enabled = false;
		exitButton->enabled = false;
		resumeButton->enabled = false;

		settingsMenu = true;
		musicLabel->enabled = true;
		vfxLabel->enabled = true;
		fullscreenLabel->enabled = true;
		gpadLabel->enabled = true;
		
	
		fullscreenButton->enabled = true;
		gpadButton->enabled = true;
		resetButton->enabled = true;
		backButton->enabled = true;
	}

	if (element == fullscreenButton && type == GUI_Event::EVENT_ONCLICK)
	{
		if (!App->win->fullscreen)
		{
			fullscreenButton->rect = { 0, 973, 182, 58 };
			fullscreenButton->hover_rect = { 0, 973, 182, 58 };
			fullscreenButton->click_rect = { 0, 973, 182, 58 };
		}

		if (App->win->fullscreen)
		{
			fullscreenButton->rect = { 0, 1031, 182, 58 };
			fullscreenButton->hover_rect = { 0, 1031, 182, 58 };
			fullscreenButton->click_rect = { 0, 1031, 182, 58 };
		}
		

		App->win->Fullscreen_Swap();
	}

	if (element == backButton && type == GUI_Event::EVENT_ONCLICK)
	{

		pauseMenu = true;
		resumeButton->enabled = true;
		saveButton->enabled = true;
		settingsButton->enabled = true;
		mainMenuButton->enabled = true;
		exitButton->enabled = true;

		settingsMenu = false;
		musicLabel->enabled = false;
		vfxLabel->enabled = false;
		fullscreenLabel->enabled = false;
		gpadLabel->enabled = false;
		
		
		fullscreenButton->enabled = false;
		gpadButton->enabled = false;
		resetButton->enabled = false;
		backButton->enabled = false;
	}


	//Disclaimers

	if (element == restartButton && type == GUI_Event::EVENT_ONCLICK)
	{
		restartMenu = true;
		exitMenuImage->enabled = true;
		exitMenuLabel->enabled = true;
		exitMenuLabel->text = "RESTART";
		exitMenuLabel->map_position.x = 530;
		exitTextLabel->enabled = true;
		yesButton->enabled = true;
		noButton->enabled = true;

		pauseMenu = false;
		pauseMenuImage->enabled = false;
		pauseMenuLabel->enabled = false;
		saveButton->enabled = false;
		settingsButton->enabled = false;
		mainMenuButton->enabled = false;
		exitButton->enabled = false;
		resumeButton->enabled = false;
	}

	if (element == exitButton && type == GUI_Event::EVENT_ONCLICK)
	{
		exitMenu = true;
		exitMenuImage->enabled = true;
		exitMenuLabel->enabled = true;
		exitMenuLabel->text = "EXIT";
		exitMenuLabel->map_position.x = 570;
		exitTextLabel->enabled = true;
		yesButton->enabled = true;
		noButton->enabled = true;

		pauseMenu = false;
		pauseMenuImage->enabled = false;
		pauseMenuLabel->enabled = false;
		saveButton->enabled = false;
		settingsButton->enabled = false;
		mainMenuButton->enabled = false;
		exitButton->enabled = false;
		resumeButton->enabled = false;
	}

	if (element == mainMenuButton && type == GUI_Event::EVENT_ONCLICK)
	{
		
		mainMenu = true;
		exitMenuImage->enabled = true;
		exitMenuLabel->enabled = true;
		exitMenuLabel->text = "TITLE";
		exitMenuLabel->map_position.x = 560;
		exitTextLabel->enabled = true;
		yesButton->enabled = true;
		noButton->enabled = true;

		pauseMenu = false;
		pauseMenuImage->enabled = false;
		pauseMenuLabel->enabled = false;
		saveButton->enabled = false;
		settingsButton->enabled = false;
		mainMenuButton->enabled = false;
		exitButton->enabled = false;
		resumeButton->enabled = false;
	}

	if (element == yesButton && type == GUI_Event::EVENT_ONCLICK)
	{
		if (exitMenu)
			App->scenes->exit = true;

		if (restartMenu)
		{

		}

		if (mainMenu) {
			App->entities->CleanUp();
			App->transition_manager->CreateSlide(SCENES::MENU_SCENE, 0.5f, true);
			App->audio->PlayingMenuMusic = false;
			Mix_HaltMusic();
		}
	}

	if (element == noButton && type == GUI_Event::EVENT_ONCLICK)
	{
		if (exitMenu)
		{
			exitMenu = false;

			pauseMenu = true;
			pauseMenuImage->enabled = true;
			pauseMenuLabel->enabled = true;
			resumeButton->enabled = true;
			saveButton->enabled = true;
			settingsButton->enabled = true;
			mainMenuButton->enabled = true;
			exitButton->enabled = true;
		}

		if (restartMenu)
			restartMenu = false;

		if (mainMenu)
		{
			mainMenu = false;

			pauseMenu = true;
			pauseMenuImage->enabled = true;
			pauseMenuLabel->enabled = true;
			resumeButton->enabled = true;
			saveButton->enabled = true;
			settingsButton->enabled = true;
			mainMenuButton->enabled = true;
			exitButton->enabled = true;
			
		}
	
		exitMenuImage->enabled = false;
		exitMenuLabel->enabled = false;
		exitTextLabel->enabled = false;
		yesButton->enabled = false;
		noButton->enabled = false;
	}

	if (element == questsOpenButton && type == GUI_Event::EVENT_ONCLICK) {
		if (PainterQuestActive == true) {
			questsText1Count->enabled = true;
			questsText1->enabled = true;
		}

		if (PaintExtractorQuestActive == true) {
			questsText2Count->enabled = true;
			questsText2->enabled = true;
		}

		if (ExtractPaintQuestActive == true) {
			questsText3Count->enabled = true;
			questsText3->enabled = true;
		}

		if (UpgradeEntityQuestActive == true) {
			questsText4Count->enabled = true;
			questsText4->enabled = true;
		}
	}

	if (element == questsCloseButton && type == GUI_Event::EVENT_ONCLICK) {

		questsText1Count->enabled = false;
		questsText2Count->enabled = false;
		questsText3Count->enabled = false;
		questsText4Count->enabled = false;
		questsText1->enabled = false;
		questsText2->enabled = false;
		questsText3->enabled = false;
		questsText4->enabled = false;
	}

}

void GameScene::ManageMinimap()
{
	float CameraSpeed_Minimap = -0.05;
	miniMapCamera->map_position.x = miniMapCamera->init_map_position.x + App->render->camera.x*CameraSpeed_Minimap;
	miniMapCamera->map_position.y = miniMapCamera->init_map_position.y + App->render->camera.y*CameraSpeed_Minimap;
}

void GameScene::InitScene()
{
	
}

void GameScene::DrawScene()
{
	App->map->Draw();



}

void GameScene::Map_Manager() {
	////THESE FUNCTION HAS TO BE REMOVED ONCE WE HAVE THE MAIN MENU, BECAUSE WE WANT THE GAME TO LOAD THE MAP AFTER WE USE THE PLAY BUTTON NOT WHILE WE ARE IN THE MENU
	if (App->scenes->Load_Map_Forest==true) {
		Generate_Forest_Map();
	}
	else if (App->scenes->Load_Map_Snow == true) {
		Generate_Snow_Map();
	}
	else if (App->scenes->Load_Map_Volcano == true) {
		Generate_Volcano_Map();
	}
	else {
		LOG("No map has been loaded in the scene");
	}
}

void GameScene::Generate_Forest_Map()
{
	App->map->CleanUp();
	App->map->Load("map_forest.tmx") == true;
	App->scenes->Load_Map_Forest = false;
	App->scenes->Map_Forest_Active = true;
}

void GameScene::Generate_Snow_Map()
{
	App->map->CleanUp();
	App->map->Load("map_snow.tmx") == true;
	App->scenes->Load_Map_Snow = false;
	App->scenes->Map_Snow_Active = true;
}

void GameScene::Generate_Volcano_Map()
{
	App->map->CleanUp();
	App->map->Load("map_volcano.tmx") == true;
	App->scenes->Load_Map_Volcano = false;
	App->scenes->Map_Volcano_Active = true;
}

void GameScene::Generate_Entities()
{
	if (App->scenes->Map_Forest_Active==true) {

		App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { 42, 42 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_PAINTER, { 45,  40 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 40, 20 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 13,  5 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 80,  4 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 10, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 80, 75 }, App->entities, nullptr, 0, true);
	}
	else if (App->scenes->Map_Snow_Active == true) {

	}
	else if (App->scenes->Map_Volcano_Active == true) {

	}
}

void GameScene::Generate_Tiles()
{
	if (App->scenes->Map_Forest_Active == true) {
		//LAKE1
		App->pathfinding->ChangeToPaintShore({ 3, 3 });
		App->pathfinding->ChangeToPaintShore({ 4, 3 });
		App->pathfinding->ChangeToPaintShore({ 5, 3 });
		App->pathfinding->ChangeToPaintShore({ 6, 3 });
		App->pathfinding->ChangeToPaintShore({ 3, 4 });
		App->pathfinding->ChangeToPaint({ 4, 4 });
		App->pathfinding->ChangeToPaint({ 5, 4 });
		App->pathfinding->ChangeToPaintShore({ 6, 4 });
		App->pathfinding->ChangeToPaintShore({ 3, 5 });
		App->pathfinding->ChangeToPaint({ 4, 5 });
		App->pathfinding->ChangeToPaint({ 5, 5 });
		App->pathfinding->ChangeToPaintShore({ 6, 5 });
		App->pathfinding->ChangeToPaintShore({ 3, 6 });
		App->pathfinding->ChangeToPaintShore({ 4, 6 });
		App->pathfinding->ChangeToPaintShore({ 5, 6 });
		App->pathfinding->ChangeToPaintShore({ 6, 6 });

		//LAKE2
		App->pathfinding->ChangeToPaint({ 32, 79 });
		App->pathfinding->ChangeToPaint({ 32, 80 });
		App->pathfinding->ChangeToPaint({ 33, 79 });
		App->pathfinding->ChangeToPaint({ 33, 80 });
		App->pathfinding->ChangeToPaintShore({ 31, 78 });
		App->pathfinding->ChangeToPaintShore({ 31, 79 });
		App->pathfinding->ChangeToPaintShore({ 31, 80 });
		App->pathfinding->ChangeToPaintShore({ 31, 81 });
		App->pathfinding->ChangeToPaintShore({ 32, 78 });
		App->pathfinding->ChangeToPaintShore({ 32, 81 });
		App->pathfinding->ChangeToPaintShore({ 33, 78 });
		App->pathfinding->ChangeToPaintShore({ 33, 81 });
		App->pathfinding->ChangeToPaintShore({ 34, 78 });
		App->pathfinding->ChangeToPaintShore({ 34, 79 });
		App->pathfinding->ChangeToPaintShore({ 34, 80 });
		App->pathfinding->ChangeToPaintShore({ 34, 81 });


		//LAKE3
		App->pathfinding->ChangeToPaint({ 49, 32 });
		App->pathfinding->ChangeToPaint({ 49, 33 });
		App->pathfinding->ChangeToPaint({ 50, 32 });
		App->pathfinding->ChangeToPaint({ 50, 33 });
		App->pathfinding->ChangeToPaintShore({ 48, 31 });
		App->pathfinding->ChangeToPaintShore({ 48, 32 });
		App->pathfinding->ChangeToPaintShore({ 48, 33 });
		App->pathfinding->ChangeToPaintShore({ 48, 34 });
		App->pathfinding->ChangeToPaintShore({ 49, 31 });
		App->pathfinding->ChangeToPaintShore({ 49, 34 });
		App->pathfinding->ChangeToPaintShore({ 50, 31 });
		App->pathfinding->ChangeToPaintShore({ 50, 34 });
		App->pathfinding->ChangeToPaintShore({ 51, 31 });
		App->pathfinding->ChangeToPaintShore({ 51, 32 });
		App->pathfinding->ChangeToPaintShore({ 51, 33 });
		App->pathfinding->ChangeToPaintShore({ 51, 34 });


		//LAKE4
		App->pathfinding->ChangeToPaint({ 64, 70 });
		App->pathfinding->ChangeToPaint({ 65, 70 });
		App->pathfinding->ChangeToPaint({ 66, 70 });
		App->pathfinding->ChangeToPaint({ 67, 70 });
		App->pathfinding->ChangeToPaint({ 64, 71 });
		App->pathfinding->ChangeToPaint({ 65, 71 });
		App->pathfinding->ChangeToPaint({ 66, 71 });
		App->pathfinding->ChangeToPaint({ 67, 71 });
		App->pathfinding->ChangeToPaintShore({ 63, 69 });
		App->pathfinding->ChangeToPaintShore({ 64, 69 });
		App->pathfinding->ChangeToPaintShore({ 65, 69 });
		App->pathfinding->ChangeToPaintShore({ 66, 69 });
		App->pathfinding->ChangeToPaintShore({ 67, 69 });
		App->pathfinding->ChangeToPaintShore({ 68, 69 });
		App->pathfinding->ChangeToPaintShore({ 63, 69 });
		App->pathfinding->ChangeToPaintShore({ 68, 74 });
		App->pathfinding->ChangeToPaintShore({ 63, 69 });
		App->pathfinding->ChangeToPaintShore({ 68, 74 });
		App->pathfinding->ChangeToPaintShore({ 63, 72 });
		App->pathfinding->ChangeToPaintShore({ 64, 72 });
		App->pathfinding->ChangeToPaintShore({ 65, 72 });
		App->pathfinding->ChangeToPaintShore({ 66, 72 });
		App->pathfinding->ChangeToPaintShore({ 67, 72 });
		App->pathfinding->ChangeToPaintShore({ 68, 72 });



		//LAKE5
		App->pathfinding->ChangeToPaint({ 92, 37 });
		App->pathfinding->ChangeToPaint({ 93, 37 });
		App->pathfinding->ChangeToPaint({ 94, 37 });
		App->pathfinding->ChangeToPaint({ 95, 37 });
		App->pathfinding->ChangeToPaint({ 92, 38 });
		App->pathfinding->ChangeToPaint({ 93, 38 });
		App->pathfinding->ChangeToPaint({ 94, 38 });
		App->pathfinding->ChangeToPaint({ 95, 38 });
		App->pathfinding->ChangeToPaintShore({ 91, 36 });
		App->pathfinding->ChangeToPaintShore({ 92, 36 });
		App->pathfinding->ChangeToPaintShore({ 93, 36 });
		App->pathfinding->ChangeToPaintShore({ 94, 36 });
		App->pathfinding->ChangeToPaintShore({ 95, 36 });
		App->pathfinding->ChangeToPaintShore({ 96, 36 });
		App->pathfinding->ChangeToPaintShore({ 91, 37 });
		App->pathfinding->ChangeToPaintShore({ 96, 37 });
		App->pathfinding->ChangeToPaintShore({ 91, 38 });
		App->pathfinding->ChangeToPaintShore({ 96, 38 });
		App->pathfinding->ChangeToPaintShore({ 91, 39 });
		App->pathfinding->ChangeToPaintShore({ 92, 39 });
		App->pathfinding->ChangeToPaintShore({ 93, 39 });
		App->pathfinding->ChangeToPaintShore({ 94, 39 });
		App->pathfinding->ChangeToPaintShore({ 95, 39 });
		App->pathfinding->ChangeToPaintShore({ 96, 39 });
	}
	else if (App->scenes->Map_Snow_Active == true) {

	}
	else if (App->scenes->Map_Volcano_Active == true) {

	}
}



void GameScene::ExecuteTransition()
{
	if (!App->transition_manager->is_transitioning)
	{
		//if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		//{
		//	App->transition_manager->CreateCut(SCENES::MENU_SCENE);
		//}

		//if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		//{
		//	App->transition_manager->CreateFadeToColour(SCENES::MENU_SCENE);
		//}

		if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
		{
			App->transition_manager->CreateSlide(SCENES::WIN_SCENE, 0.5f, true);
			App->entities->CleanUp();
		}

		if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		{
			App->transition_manager->CreateSlide(SCENES::LOSE_SCENE, 0.5f, true, true);
			App->entities->CleanUp();
		}

	

	}
}

void GameScene::WIN_LOSE_Manager()
{
	// WIN CONDITION
	bool anySpawnerActive = false;
	list<Entity*>::const_iterator checkForSpawners = App->entities->activeBuildings.begin();
	while (checkForSpawners != App->entities->activeBuildings.end()) {

		if ((*checkForSpawners)->entityType == ENTITY_TYPE_SPAWNER) {
			anySpawnerActive = true;
			break;
		}
		checkForSpawners++;
	}
	if (!anySpawnerActive)
		App->entities->TriggerEndGame(true);

	// LOSE CONDITION
	bool anyTownhallActive = false;
	list<Entity*>::const_iterator checkForTownhalls = App->entities->activeBuildings.begin();
	while (checkForTownhalls != App->entities->activeBuildings.end()) {

		if ((*checkForTownhalls)->entityType == ENTITY_TYPE_TOWN_HALL) {
			anyTownhallActive = true;
			break;
		}
		checkForTownhalls++;
	}
	if (!anyTownhallActive)
		App->entities->TriggerEndGame(false);
}

void GameScene::CreateDialogText()
{

	DialogPage1 = true;
	DialogPage2 = false;
	DialogPage3 = false;
	DialogPage4 = false;
	DialogPage5 = false;
	DialogPage6 = false;
	/*PaintExtractorQuestCompletedSafe = false;
	PainterQuestCompletedSafe = false;
	ExtractPaintQuestCompletedSafe = false;
    UpgradeEntityQuestCompletedSafe=false;*/

	PainterQuestCompleted = false;
	PaintExtractorQuestCompleted = false;
	ExtractPaintQuestCompleted = false;
	UpgradeEntityQuestCompleted = false;

	PainterQuestActive = false;
	PaintExtractorQuestActive = false;
	ExtractPaintQuestActive = false;
	UpgradeEntityQuestActive = false;




	Dialog_Text1_Line_1 = "GREETINGS KING OF PAINTLAND";
	Dialog_Text1_Line_2 = "I WELCOME YOU TO YOUR KINGDOM";
	Dialog_Text1_Line_3 = "I AM HERE TO GUIDE YOU";



	Dialog_Text2_Line_1 = "NOW LETS GET STARTED!";
	Dialog_Text2_Line_2 = "SELECT THE TOWN HALL";
	Dialog_Text2_Line_3 = "AND BUY A PAINTER";



	Dialog_Text3_Line_1 = "WE WILL ALSO NEED TO ";
	Dialog_Text3_Line_2 = "BUILD A PAINT EXTRACTOR";
	Dialog_Text3_Line_3 = "NOW GO TO THE SHOP!";



	Dialog_Text4_Line_1 = "WE HAVE TO GET STRONGER";
	Dialog_Text4_Line_2 = "WAIT FOR THE EXTRACTORS";
	Dialog_Text4_Line_3 = "TO COLLECT SOME PAINT!";



	Dialog_Text5_Line_1 = "UPGRADE THE EXTRACTOR";
	Dialog_Text5_Line_2 = "TO COLLECT EVEN MORE";
	Dialog_Text5_Line_3 = "PAINT!";

	Dialog_Text6_Line_1 = "THATS ALL THE TUTORIAL FOR NOW";
	Dialog_Text6_Line_2 = "WAIT FOR THE FULL RELEASE TO";
	Dialog_Text6_Line_3 = "KEEP GOING";
	

}

void GameScene::DialogManagerFunction()
{
	if (DialogPage1) {
		dialogText1->text = Dialog_Text1_Line_1;
		dialogText2->text = Dialog_Text1_Line_2;
		dialogText3->text = Dialog_Text1_Line_3;
	}
	else if (DialogPage2) {
		dialogText1->text = Dialog_Text2_Line_1;
		dialogText2->text = Dialog_Text2_Line_2;
		dialogText3->text = Dialog_Text2_Line_3;
	}
	else if (DialogPage3) {
		dialogText1->text = Dialog_Text3_Line_1;
		dialogText2->text = Dialog_Text3_Line_2;
		dialogText3->text = Dialog_Text3_Line_3;
	}
	else if (DialogPage4) {
		dialogText1->text = Dialog_Text4_Line_1;
		dialogText2->text = Dialog_Text4_Line_2;
		dialogText3->text = Dialog_Text4_Line_3;
	}
	else if (DialogPage5) {
		dialogText1->text = Dialog_Text5_Line_1;
		dialogText2->text = Dialog_Text5_Line_2;
		dialogText3->text = Dialog_Text5_Line_3;
	}
	else if (DialogPage6) {
		dialogText1->text = Dialog_Text6_Line_1;
		dialogText2->text = Dialog_Text6_Line_2;
		dialogText3->text = Dialog_Text6_Line_3;
	}


}

void GameScene::QuestManagerFunction()
{

	if (PainterQuestCompleted == true) {
		questsText1Count->text = "1/1";
		//Mix_PlayChannel(-1, App->audio->Quest_Audio, 0);
	}

	if (App->entities->ExtractorQuestDone == true) { //REMEMBER TO SET THIS BOOL TO FALSE IN CLEANUP OF GAME SCENE OR THIS QUEST WONT WORK
		PaintExtractorQuestCompleted = true;
		if (PaintExtractorQuestCompleted == true) {
			questsText2Count->text = "extractor 1/1";
			//Mix_PlayChannel(-1, App->audio->Quest_Audio, 0);
		}
	}

	if (App->player->paintCount.count>=150) {
		ExtractPaintQuestCompleted = true;
		questsText3Count->text = "150/150";
		//Mix_PlayChannel(-1, App->audio->Quest_Audio, 0);
	}

	if (UpgradeEntityQuestCompleted == true) {
		questsText4Count->text = " 1/1";
		//Mix_PlayChannel(-1, App->audio->Quest_Audio, 0);
	}

	if (DialogOperative == true) {
		dialogImage->enabled = true;
		dialogClose->enabled = true;
		dialogText1->enabled = true;
		dialogText2->enabled = true;
		dialogText3->enabled = true;
		dialogPrev->enabled = true;
		dialogNext->enabled = true;
		dialogOpen->enabled = false;

		if (DialogPage1 == true) {
			dialogNext->enabled = true;
			dialogPrev->enabled = false;
		}
		else if (DialogPage2 == true) {
			PainterQuestActive = true;

			/*questsText1Count->enabled = true;
			questsText1->enabled = true;*/

			if (PainterQuestCompleted == true) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
			}
			else {
				dialogNext->enabled = false;
				dialogPrev->enabled = true;
			}

		}
		else if (DialogPage3 == true) {
			PaintExtractorQuestActive = true;

			/*questsText2Count->enabled = true;
			questsText2->enabled = true;*/

			if (PaintExtractorQuestCompleted == true) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
			}
			else {
				dialogNext->enabled = false;
				dialogPrev->enabled = true;
			}

		}
		else if (DialogPage4 == true) {
			ExtractPaintQuestActive = true;

			/*questsText3Count->enabled = true;
			questsText3->enabled = true;*/

			if (ExtractPaintQuestCompleted == true) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
			}
			else {
				dialogNext->enabled = false;
				dialogPrev->enabled = true;
			}

		}
		else if (DialogPage5 == true) {
			UpgradeEntityQuestActive = true;

			/*questsText4Count->enabled = true;
			questsText4->enabled = true;*/

			if (UpgradeEntityQuestCompleted == true) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
			}
			else {
				dialogNext->enabled = false;

			}

		}
	}
	else {

		dialogImage->enabled = false;
		dialogClose->enabled = false;
		dialogText1->enabled = false;
		dialogText2->enabled = false;
		dialogText3->enabled = false;
		dialogPrev->enabled = false;
		dialogNext->enabled = false;
		dialogOpen->enabled = true;
	}

}




