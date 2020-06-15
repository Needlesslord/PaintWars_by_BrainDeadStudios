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
#include "j1ParticleManager.h"
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
	 + F1/F2/F3 Game Scene - Forest, Snow, Volcano
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

GameScene::GameScene() : Scene(SCENES::GAME_SCENE) {}

// Destructor
GameScene::~GameScene() {}

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

	////camera start
//if (App->scenes->Map_Forest_Active) {
//	App->render->camera.x = 575;
//	App->render->camera.y = -1200;
//}
//if (App->scenes->Map_Snow_Active) {
//	App->render->camera.x = -1200;
//	App->render->camera.y = -2350;
//}
//if (App->scenes->Map_Volcano_Active) {
//	App->render->camera.x = 500;
//	App->render->camera.y = 10;
//}
	
	Map_Manager();

	int w, h;
	uchar* data = NULL;
	//DOESNT ENTER THIS FUNCTION
	if (App->map->CreateWalkabilityMap(w, h, &data))
	{
		App->pathfinding->SetMap(w, h, data);						// Sets a new walkability map with the map passed by CreateWalkabilityMap().

	}


	bool PainterQuestCompleted = false;
	bool PaintExtractorQuestCompleted = false;
	bool ExtractPaintQuestCompleted = false;
	bool UpgradeEntityQuestCompleted = false;

	bool PainterQuestActive = false;
	bool PaintExtractorQuestActive = false;
	bool ExtractPaintQuestActive = false;
	bool UpgradeEntityQuestActive = false;


	Generate_Entities();
	Generate_Tiles();

	App->scenes->IN_GAME_SCENE = true;


	//////////////////
	//      UI      //
	//////////////////

	
	/*BackgroundForest = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 5 }, { 0 , 0 }, false, true, { 0, 1353, 1250, 35 }, nullptr, nullptr, TEXTURE::BACKGROUND_FOREST);
	BackgroundSnow = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 5 }, { 0 , 0 }, false, true, { 0, 1353, 1250, 35 }, nullptr, nullptr, TEXTURE::BACKGROUND_SNOW);
	BackgroundVolcano = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 5 }, { 0 , 0 }, false, true, { 0, 1353, 1250, 35 }, nullptr, nullptr, TEXTURE::BACKGROUND_VOLCANO);*/

	/*if (App->scenes->Map_Forest_Active)
	{
		BackgroundForest = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0, 0 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes, TEXTURE::BACKGROUND_FOREST);
	}

	else if (App->scenes->Map_Snow_Active)
	{
		BackgroundSnow = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0, 0 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes, TEXTURE::BACKGROUND_SNOW);
	}

	else if (App->scenes->Map_Volcano_Active)
	{
		BackgroundVolcano = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0, 0 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes, TEXTURE::BACKGROUND_VOLCANO);
	}*/
	

	
	//HUD - Bar
	//hudBarImage = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 5 }, { 0 , 0 }, false, true, { 0, 1353, 1250, 35 }, nullptr, nullptr, TEXTURE::ATLAS_SPRITE);
	hudBarImage = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15,5 }, { 0,0 }, false, true, { 0,1353,1250,35 }, nullptr, App->scenes, TEXTURE::ATLAS,FONT::FONT_MEDIUM,2);
	paintLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 120 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 },"0", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL);
	woodLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 240 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "0", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL);
	metalLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 360 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "0", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL);
	titaniumLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 480 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "0", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL);
	researchLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 600 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "0", nullptr,  TEXTURE::ATLAS, FONT::FONT_SMALL);
	entitiesLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 720 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "0", nullptr,  TEXTURE::ATLAS, FONT::FONT_SMALL);
	EntityHP = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 1075 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "999", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL);
	timerLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, hudBarImage, { 830 , 5 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "15m 00s", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL_RED);


	//HUD - Quests
	//questsImage = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 50 }, { 0 , 0 }, false, true, { 0, 1388, 263, 40 }, nullptr, nullptr, TEXTURE::ATLAS_SPRITE);
	questsImage = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15 , 50 }, { 0 , 0 }, false, true, { 0, 1388, 263, 40 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL_WHITE, 2);
	questsLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 15 , 52 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "QUESTS", nullptr,  TEXTURE::ATLAS, FONT::FONT_SMALL_WHITE);
	questsOpenButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 120, 65 }, { 200,200 }, true, true, { 317, 1388, 54, 55}, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 2);
	questsOpenButton->hover_rect = { 317, 1443, 54, 54 };
	questsOpenButton->click_rect = { 317, 1497, 54, 54 };
	questsCloseButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 120, 380 }, { 200,200 }, true, false, { 263, 1388, 54, 55 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 2);
	questsCloseButton->hover_rect = { 263, 1443, 54, 54 };
	questsCloseButton->click_rect = { 263, 1497, 54, 54 };

	questsText1 = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 90 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " CREATE 3 PAINTERS", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText1Count = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 120 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " 0/3", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText2 = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 160 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " CREATE 1 BARRACKS", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText2Count = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 190 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, "0/1", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText3 = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 230 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " EXTRACT PAINT", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText3Count = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 260 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " 0/150", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText4 = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 300 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " UPGRADE 1 WARRIOR", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText4Count = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 330 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " 0/1", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText5 = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 370 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " DESTROY 1 SPAWNER", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText5Count = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 330 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " 0/1", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText6 = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 430 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " FIND THE EXPLORER", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	questsText6Count = App->gui->AddElement(TypeOfUI::GUI_LABEL, questsImage, { 15 , 330 }, { 2 , 0 }, false, false, { 0, 0, 0, 0 }, " 0/1", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);


	//HUD - Dialog

	dialogImage = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 300 , 575 }, { 0 , 0 }, false,true, { 0, 1820, 500, 125 }, nullptr, nullptr, TEXTURE::ATLAS);
	//dialogCharacter = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 300 , 575 }, { 0 , 0 }, true, true, { 276, 1972, 30, 28 }, nullptr, nullptr, TEXTURE::ATLAS);
	dialogClose = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 780 , 570 }, { 0 , 0 }, true, true, { 670, 1392, 28, 28 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 2);
	dialogClose->hover_rect = { 636, 1392, 28, 28 };
	dialogClose->click_rect = { 601, 1392, 28, 28 };
	dialogText1 = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 330 , 600 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "DIALOG SYSTEM ", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	dialogText2 = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 330 , 630 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "DIALOG SYSTEM ", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
	dialogText3 = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 330 , 660 }, { 2 , 0 }, false, true, { 0, 0, 0, 0 }, "DIALOG SYSTEM ", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_WHITE);
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
	ExplanationHover = App->gui->AddElement(TypeOfUI::GUI_LABEL, shopImage, { 130 , 680 }, { 0 , 0 }, false, false, { 0, 0, 0, 0 }, "EXPLANATION", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL_WHITE); //Not implemented
	CostLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, shopImage, { 130 , 680 }, { 0 , 0 }, false, false, { 0, 0, 0, 0 }, "COST", nullptr, TEXTURE::ATLAS, FONT::FONT_SMALL_WHITE);
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
	buyMetalGathererButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, shopImage, { 15, 567 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyMetalGathererButton->hover_rect = { 0, 1966, 65, 82 };
	buyMetalGathererButton->click_rect = { 65, 1966, 65, 82 };
	buyTitaniumExtractorButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, shopImage, { 80, 567 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyTitaniumExtractorButton->hover_rect = { 0, 1966, 65, 82 };
	buyTitaniumExtractorButton->click_rect = { 65, 1966, 65, 82 };
	buyLaboratoryButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, shopImage, { 145, 567 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyLaboratoryButton->hover_rect = { 0, 1966, 65, 82 };
	buyLaboratoryButton->click_rect = { 65, 1966, 65, 82 };
	buyTurretButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, shopImage, { 210, 567 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyTurretButton->hover_rect = { 0, 1966, 65, 82 };
	buyTurretButton->click_rect = { 65, 1966, 65, 82 };
	upgradeWoodProducerButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15, 485 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	upgradeWoodProducerButton->hover_rect = { 0, 1966, 65, 82 };
	upgradeWoodProducerButton->click_rect = { 65, 1966, 65, 82 };
	upgradePaintExtractorButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 80, 485 }, { 0,0 }, true, false, { 1985, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	upgradePaintExtractorButton->hover_rect = { 0, 1966, 65, 82 };
	upgradePaintExtractorButton->click_rect = { 65, 1966, 65, 82 };


	////
	fxBar = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 560, 300 }, { 0,0 }, true, false, { 785, 57, 268, 26 }, nullptr, App->scenes, TEXTURE::ATLAS);
	fxBar->hover_rect = { 785, 57, 268, 26 };
	fxBar->click_rect = { 785, 57, 268, 26 };
	musicBar = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 560, 230 }, { 0,0 }, true, false, { 785, 57, 268, 26 }, nullptr, App->scenes, TEXTURE::ATLAS);
	musicBar->click_rect = { 785, 57, 268, 26 };
	musicBar->hover_rect = { 785, 57, 268, 26 };

	musicSlider = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 660, 230 }, { 0,0 }, true, false, { 786, 1, 42, 34 }, nullptr, App->scenes, TEXTURE::ATLAS);
	musicSlider->hover_rect = { 786, 1, 42, 34 };
	musicSlider->click_rect = { 786, 1, 42, 34 };

	fxSlider = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 660, 300 }, { 0,0 }, true, false, { 786, 1, 42, 34 }, nullptr, App->scenes, TEXTURE::ATLAS);
	fxSlider->hover_rect = { 786, 1, 42, 34 };
	fxSlider->click_rect = { 786, 1, 42, 34 };




	//////

	//shopHoverPrice =App->gui->AddElement(TypeOfUI::GUI_BUTTON, shopImage, { 210 , 680 }, { 0,0 }, true, false, { 0, 0, 0, 0 }, "0", App->scenes, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_RED, 6);
	shopHoverPrice = App->gui->AddElement(TypeOfUI::GUI_LABEL, shopImage, { 210 , 680 }, { 0 , 0 }, false, false, { 0, 0, 0, 0 }, "0", nullptr, TEXTURE::ATLAS, FONT::FONT_EXTRA_SMALL_RED);
	

	//HUD - MiniMap

	//miniMapBackground = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 850 , 500 }, { 0 , 0 }, false, true, { 0, 1750, 422, 210 }, nullptr, nullptr, TEXTURE::ATLAS_SPRITE);
	//miniMapBackground = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 850 , 500 }, { 0 , 0 }, false, true, { 0, 1750, 422, 210 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_MEDIUM, 2);
	//minimaps


	miniMapMINI_forest = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 850 , 500 }, { 0,0 }, true,false ,{ 30, 15, 422,210 }, nullptr, App->scenes, TEXTURE::MINIMAP_MINI_FOREST);
	miniMapMINI_forest->click_rect = { 30, 15, 422, 210 };
	miniMapMINI_forest->hover_rect = { 30, 15, 422, 210 };

	miniMapMINI_snow = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 850 , 500 }, { 0,0 }, true, false, { 30, 15, 422,210 }, nullptr, App->scenes, TEXTURE::MINIMAP_MINI_SNOW);
	miniMapMINI_snow->click_rect = { 30, 15, 422, 210 };
	miniMapMINI_snow->hover_rect = { 30, 15, 422, 210 };

	miniMapMINI_volcano = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 850 , 500 }, { 0,0 }, true, false, { 30, 15, 422,210 }, nullptr, App->scenes, TEXTURE::MINIMAP_MINI_VOLCANO);
	miniMapMINI_volcano->click_rect = { 30, 15, 422, 210 };
	miniMapMINI_volcano->hover_rect = { 30, 15, 422, 210 };



	//end minimaps

	miniMapScopeCamera = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 1030, 575 }, { 0 , 0 }, false, true, { 0, 0, 67, 36 }, nullptr, nullptr, TEXTURE::MINIMAP_CAMERA);

	//miniMapBack = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0 , 0 }, { 0 , 0 }, false, false, { 0, 0, 1800, 1300 }, nullptr, nullptr,  TEXTURE::MINIMAP_BACK_SPRITE);

	//minimaps
	if (App->scenes->Map_Forest_Active) {
		miniMapFULL_forest = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 50 , 75 }, { 0 , 0 }, true, false, { 87, 40, 1170,588 }, nullptr, App->scenes, TEXTURE::MINIMAP_FULL_FOREST);
		miniMapFULL_forest->click_rect = { 87, 40, 1170,588 };
		miniMapFULL_forest->hover_rect = { 87, 40, 1170,588 };
	}
	if (App->scenes->Map_Snow_Active) {
		miniMapFULL_snow = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 50 , 75 }, { 0 , 0 }, true, false, { 87, 40, 1170,588 }, nullptr, App->scenes, TEXTURE::MINIMAP_FULL_SNOW);
		miniMapFULL_snow->click_rect = { 87, 40, 1170,588 };
		miniMapFULL_snow->hover_rect = { 87, 40, 1170,588 };
	}
	if (App->scenes->Map_Volcano_Active) {
		miniMapFULL_snow = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 50 , 75 }, { 0 , 0 }, true, false, { 87, 40, 1170,588 }, nullptr, App->scenes, TEXTURE::MINIMAP_FULL_VOLCANO);
		miniMapFULL_snow->click_rect = { 87, 40, 1170,588 };
		miniMapFULL_snow->hover_rect = { 87, 40, 1170,588 };
	}
	//end minimap

	if (App->scenes->Map_Forest_Active) {
		App->render->camera.x = 575;
		App->render->camera.y = -1200;
		App->player->MinimapCameraBufferX = 4;
		App->player->MinimapCameraBufferY = -4;
	}
	if (App->scenes->Map_Snow_Active) {
		App->render->camera.x = -329;
		App->render->camera.y = -608;
		App->player->MinimapCameraBufferX = -24;
		App->player->MinimapCameraBufferY = 15;
	}
	if (App->scenes->Map_Volcano_Active) {
		App->render->camera.x = 700;
		App->render->camera.y = 10;
		App->player->MinimapCameraBufferX = 4.39;
		App->player->MinimapCameraBufferY = 33;
	}

	//Units

	upgradePainterButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 80, 485 }, { 0,0 }, true, false, { 130, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	upgradePainterButton->hover_rect = { 390, 1966, 65, 82 };
	upgradePainterButton->click_rect = { 750, 1966, 65, 82 };
	buyPainterButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15, 485 }, { 0,0 }, true, false, { 260, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyPainterButton->hover_rect = { 520, 1966, 65, 82 };
	buyPainterButton->click_rect = { 780, 1966, 65, 82 };
	buyExplorerButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15, 567 }, { 0,0 }, true, false, { 1105, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyExplorerButton->hover_rect = { 1105, 1885, 65, 82 };
	buyExplorerButton->click_rect = { 1105, 1804, 65, 82 };
	upgradeWarriorButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 80, 485 }, { 0,0 }, true, false, { 195, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	upgradeWarriorButton->hover_rect = { 455, 1966, 65, 82 };
	upgradeWarriorButton->click_rect = { 715, 1966, 65, 82 };
	buyWarriorButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15, 485 }, { 0,0 }, true, false, { 325, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyWarriorButton->hover_rect = { 585, 1966, 65, 82 };
	buyWarriorButton->click_rect = { 845, 1966, 65, 82 };
	buyRangerButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 15, 567 }, { 0,0 }, true, false, { 1170, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyRangerButton->hover_rect = { 1170, 1885, 65, 82 };
	buyRangerButton->click_rect = { 1170, 1804, 65, 82 };
	buyKnightButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 80, 567 }, { 0,0 }, true, false, { 1235, 1966, 65, 82 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	buyKnightButton->hover_rect = { 1235, 1885, 65, 82 };
	buyKnightButton->click_rect = { 1235, 1804, 65, 82 };

	
	//Animation
	//PaintRollerAnimation = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 400, -200 }, { 0 , 0 }, false,false, { 1493, 1292, 552, 753 }, nullptr, nullptr, TEXTURE::ATLAS_SPRITE);
	PaintRollerAnimation = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 400, -600 }, { 0,0 }, false, false, { 1493, 1275, 552, 770 }, nullptr, App->scenes, TEXTURE::ATLAS, FONT::FONT_SMALL, 6);
	//PaintRollerAnimation->enabled = false;

	BackgroundForest = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 5 }, { 0 , 0 }, false, true, { 0, 1353, 1250, 35 }, nullptr, nullptr, TEXTURE::BACKGROUND_FOREST);
	BackgroundSnow = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 5 }, { 0 , 0 }, false, true, { 0, 1353, 1250, 35 }, nullptr, nullptr, TEXTURE::BACKGROUND_SNOW);
	BackgroundVolcano = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 15 , 5 }, { 0 , 0 }, false, true, { 0, 1353, 1250, 35 }, nullptr, nullptr, TEXTURE::BACKGROUND_VOLCANO);
	//////////////////
	//	RESOURCES	//
	//////////////////

	App->player->paintCount.type = RESOURCE_TYPE_PAINT;
	App->player->paintCount.count = 50;

	App->player->woodCount.type = RESOURCE_TYPE_WOOD;
	App->player->woodCount.count = 50;

	App->player->metalScrapCount.type = RESOURCE_TYPE_METAL_SCRAP;
	App->player->metalScrapCount.count = 0;

	App->player->titaniumCount.type = RESOURCE_TYPE_TITANIUM;
	App->player->titaniumCount.count = 0;
	
	App->player->housingSpace.type = RESOURCE_TYPE_HOUSING;
	App->player->housingSpace.count = 2;
	App->player->housingSpace.maxCount = 5;


	if (App->audio->PlayingMenuMusic == true) {
		Mix_HaltMusic();
		App->audio->PlayingMenuMusic = false;
	}

	if (App->audio->PlayingIngameAudio != true) {
		App->audio->PlayMusic("audio/music/music_scene_inGame.ogg");
		App->audio->PlayingIngameAudio = true;
	}

	App->player->gameTimer.Start();

	App->player->cricketsRepeat.Start();

	App->fow->SetVisibilityMap(App->map->data.width, App->map->data.height);


	if (App->scenes->Map_Volcano_Active)
	{
		App->pmanager->meteorActive = true;
	}
	else
	{
		App->pmanager->meteorActive = false;
	}

	return ret;
}

// Called each loop iteration
bool GameScene::PreUpdate()
{



	if (App->scenes->Map_Forest_Active) {
		miniMapMINI_forest->enabled = true;
		miniMapMINI_snow->enabled = false;
		miniMapMINI_volcano->enabled = false;
	}
	else if (App->scenes->Map_Snow_Active) {
		miniMapMINI_snow->enabled = true;
		miniMapMINI_volcano->enabled = false;
		miniMapMINI_forest->enabled = false;
	}
	else if (App->scenes->Map_Volcano_Active) {
		miniMapMINI_volcano->enabled = true;
		miniMapMINI_snow->enabled = false;
		miniMapMINI_forest->enabled = false;
	}
	//PaintRollerAnimation->enabled = false;
	
	bool ret = true;
	//--------------------------- PUT AN INT THAT GOES THROUGH IT 15-20 TIMES OR MORE AND WHEN ITS DONE COMPLETE ANIMATION
	
	//LOG("Position Roller Y %f", PaintRollerAnimation->map_position.y);
	if (App->PAUSE_ACTIVE == true && pauseMenu == true){
		
		if (/*PaintRollerAnimation->map_position.y + App->render->camera.y < 0 + App->render->camera.y*/ AnimTime < 90 && App->transition_manager->is_transitioning == false) {
			PaintRollerAnimation->map_position = PaintRollerAnimation->map_position = { PaintRollerAnimation->map_position.x ,PaintRollerAnimation->map_position.y + 25 };
			//LOG("Position Roller Y %f",PaintRollerAnimation->map_position.y);
				//LOG("Camera x at %d", App->render->camera.x);
			++AnimTime;
		}
		else if (App->transition_manager->is_transitioning == true) {

		}
		else {
			PaintRollerAnimation->enabled = false;
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
	}
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
	int conversorInt3 = App->player->metalScrapCount.count;
	sprintf_s(conversorChar3, 256, "%d", conversorInt3);
	metalLabel->text = conversorChar3;

	int housingUsed = 0;
	list<Entity*>::iterator housingCheck = App->entities->activeUnits.begin();
	while (housingCheck != App->entities->activeUnits.end()) {

		if ((*housingCheck)->isEntityFromPlayer)
			housingUsed++;

		housingCheck++;
	}
	App->player->housingSpace.count = housingUsed;

	static char conversorChar4[256];
	int conversorInt4 = App->player->housingSpace.count;
	int conversorInt5 = App->player->housingSpace.maxCount;
	sprintf_s(conversorChar4, 256, "%d/%d", conversorInt4, conversorInt5);
	entitiesLabel->text = conversorChar4;
	
	static char conversorChar6[256];
	int conversorInt6 = App->player->titaniumCount.count;
	sprintf_s(conversorChar6, 256, "%d", conversorInt6);
	titaniumLabel->text = conversorChar6;



	

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


		// Check if there are any explorers alive
		list<Entity*>::iterator noActiveExplorers = App->entities->activeUnits.begin();
		bool noExplorers = true;
		while (noActiveExplorers != App->entities->activeUnits.end()) {
			if ((*noActiveExplorers)->entityType == ENTITY_TYPE_EXPLORER) {
				noExplorers = false;
				break;
			}
			noActiveExplorers++;
		}
		if(noExplorers)
			buyExplorerButton->enabled = true;

		shopImage->enabled = false;
		shopLabel->enabled = false;
		CostLabel->enabled = false;
		buyWoodProducerButton->enabled = false;
		buyPaintExtractorButton->enabled = false;
		buyBarrackButton->enabled = false;
		buyHouseButton->enabled = false;
		upgradeWoodProducerButton->enabled = false;
		upgradePaintExtractorButton->enabled = false;
	}
	else {
		buyPainterButton->enabled = false;
		buyExplorerButton->enabled = false;
		upgradePainterButton->enabled = false;
	}



	// If only the Barracks is selected enable the button
	list<Entity*>::iterator onlyBarracksSelected = App->entities->buildingsSelected.begin();
	if (App->entities->buildingsSelected.size() == 1 && (*onlyTownhallSelected)->entityType == ENTITY_TYPE_BARRACKS) {

		buyWarriorButton->enabled = true;
		if (!App->entities->warriorsUpgraded)
			upgradeWarriorButton->enabled = true;

		buyKnightButton->enabled = true;
		buyRangerButton->enabled = true;

		shopImage->enabled = false;
		shopLabel->enabled = false;
		CostLabel->enabled = false;
		buyWoodProducerButton->enabled = false;
		buyPaintExtractorButton->enabled = false;
		buyBarrackButton->enabled = false;
		buyHouseButton->enabled = false;
		upgradeWoodProducerButton->enabled = false;
		upgradePaintExtractorButton->enabled = false;
	}
	else {
		buyWarriorButton->enabled = false;
		buyKnightButton->enabled = false;
		buyRangerButton->enabled = false;
		upgradeWarriorButton->enabled = false;
	}


	//Timer

	int minutes = 14 - (int)App->player->gameTimer.ReadSec() / 60;
	int seconds = 60 - (int)App->player->gameTimer.ReadSec() % 60;

	static char conversor[256];
	sprintf_s(conversor, 256, "%dm %ds", minutes, seconds);
	timerLabel->text = conversor;




	fPoint MousePos = App->input->GetMouseWorldPosition();

	/*LOG("Mouse x at %f", MousePos.x);

	LOG("Mouse y at %f", MousePos.y);*/

	//comprobaciones
	//if (App->player->gameTimer.ReadSec() == 60) {
	//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 45,  40 }, App->entities, nullptr, 0, true);
	//}

	
	return ret;
}

// Called each loop iteration
bool GameScene::PostUpdate()
{
	BROFILER_CATEGORY("Game Scene PostUpdate--Scenes();", Profiler::Color::FloralWhite);
	bool ret = true;
	
	
	if (App->input->GetKey(SDL_SCANCODE_M) == true) {

		//minimaps
		if (App->scenes->Map_Forest_Active) {
			if (miniMapMINI_forest->enabled == true) {
				miniMapBack->enabled = true;
				miniMapFULL_forest->enabled = true;
				miniMapMINI_forest->enabled = false;
				miniMapScopeCamera->enabled = false;
			}
			else {
				miniMapMINI_forest->enabled = true;
				miniMapBack->enabled = false;
				miniMapFULL_forest->enabled = false;
				miniMapScopeCamera->enabled = true;
			}
		}

		if (App->scenes->Map_Snow_Active) {
			if (miniMapMINI_snow->enabled == true) {
				miniMapBack->enabled = true;
				miniMapFULL_snow->enabled = true;
				miniMapMINI_snow->enabled = false;
				miniMapScopeCamera->enabled = false;
			}
			else {
				miniMapMINI_snow->enabled = true;
				miniMapBack->enabled = false;
				miniMapFULL_snow->enabled = false;
				miniMapScopeCamera->enabled = true;
			}
		}

		if (App->scenes->Map_Volcano_Active) {
			if (miniMapMINI_volcano->enabled == true) {
				miniMapBack->enabled = true;
				miniMapFULL_volcano->enabled = true;
				miniMapMINI_volcano->enabled = false;
				miniMapScopeCamera->enabled = false;
			}
			else {
				miniMapMINI_volcano->enabled = true;
				miniMapBack->enabled = false;
				miniMapFULL_volcano->enabled = false;
				miniMapScopeCamera->enabled = true;
			}
		}
		//end minimaps
	}



	//	//at minute 5 generate 3 slimes, 1 explosive blobs
	//if (App->player->gameTimer.ReadSec() == 300) {
	//		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 52 }, App->entities, nullptr, 0, true);
	//		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 32, 32 }, App->entities, nullptr, 0, true);
	//		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 32 }, App->entities, nullptr, 0, true);
	//		App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { 32, 52 }, App->entities, nullptr, 0, true);
	//}
	//	//at minute 8 generate 4 slimes, 2 explosive blobs, 1 rider
	//if (App->player->gameTimer.ReadSec() == 480) {
	//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 52 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 32, 32 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 32 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 32, 52 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { 37, 57 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { 37, 37 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_RIDER, { 57, 57 }, App->entities, nullptr, 0, true);
	//}
	//	//at minute 11 generate 3 slimes, 2 explosive blobs, 2 riders, 1 chroma king
	//if (App->player->gameTimer.ReadSec() == 660) {
	//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 52 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 32, 32 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 32 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { 57, 57 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { 37, 37 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_RIDER, { 57, 37 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_RIDER, { 37, 57 }, App->entities, nullptr, 0, true);
	//	App->entities->AddEntity(ENTITY_TYPE_CHROMA_KING, { 60, 60 }, App->entities, nullptr, 0, true);
	//}
	

	

	WIN_LOSE_Manager();

	ExecuteTransition();
		


	ManageMinimap();
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

	App->gui->CleanUp();
	for (int i = 0; i < App->gui->GUI_ELEMENTS.count(); i++)
	{
		App->gui->GUI_ELEMENTS[i]->CleanUp();
		//RELEASE(App->gui->GUI_ELEMENTS[i]);
	}
	
	App->scenes->Timer_Minutes = minutes;
	App->scenes->Timer_Seconds = seconds;





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

	//minimaps
	if (element == miniMapMINI_forest && type == GUI_Event::EVENT_ONCLICK) {}
	if (element == miniMapFULL_forest && type == GUI_Event::EVENT_ONCLICK) {}
	if (element == miniMapMINI_snow && type == GUI_Event::EVENT_ONCLICK) {}
	if (element == miniMapFULL_snow && type == GUI_Event::EVENT_ONCLICK) {}
	if (element == miniMapMINI_volcano && type == GUI_Event::EVENT_ONCLICK) {}
	if (element == miniMapFULL_volcano && type == GUI_Event::EVENT_ONCLICK) {}
	//end minimaps

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
		else if (DialogPage5 == true) {
			DialogPage6 = true;
			DialogPage5 = false;
		}
		else if (DialogPage6 == true) {
			DialogPage7 = true;
			DialogPage6 = false;
		}
		else if (DialogPage7 == true) {
			DialogPage8 = true;
			DialogPage7 = false;
		}
		else if (DialogPage8 == true) {
			DialogPage9 = true;
			DialogPage8 = false;
		}
		else if (DialogPage9 == true) {
			DialogPage10 = true;
			DialogPage9 = false;
		}
		else if (DialogPage10 == true) {
			DialogPage11 = true;
			DialogPage10 = false;
		}
		else if (DialogPage11 == true) {
			DialogPage12 = true;
			DialogPage11 = false;
		}
		else if (DialogPage12 == true) {
			DialogPage13 = true;
			DialogPage12 = false;
		}
		else if (DialogPage13 == true) {
			DialogPage14 = true;
			DialogPage13 = false;
		}
		else if (DialogPage14 == true) {
			DialogPage15 = true;
			DialogPage14 = false;
		}
	 
	}

	if (element == dialogPrev && type == GUI_Event::EVENT_ONCLICK)
	{

		if (DialogPage2 == true) {
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
		if (DialogPage7 == true) {
			DialogPage6 = true;
			DialogPage7 = false;
		}
		else if (DialogPage8 == true) {
			DialogPage7 = true;
			DialogPage8 = false;
		}
		else if (DialogPage9 == true) {
			DialogPage8 = true;
			DialogPage9 = false;
		}
		else if (DialogPage10 == true) {
			DialogPage9 = true;
			DialogPage10 = false;
		}
		else if (DialogPage11 == true) {
			DialogPage10 = true;
			DialogPage11 = false;
		}
		if (DialogPage12 == true) {
			DialogPage11 = true;
			DialogPage12 = false;
		}
		else if (DialogPage13 == true) {
			DialogPage12 = true;
			DialogPage13 = false;
		}
		else if (DialogPage14 == true) {
			DialogPage13 = true;
			DialogPage14 = false;
		}
		else if (DialogPage15 == true) {
			DialogPage14 = true;
			DialogPage15 = false;
		}
	}
	

	//HomeButton

	if (element == homeButton && type == GUI_Event::EVENT_ONCLICK)
	{
		if (App->scenes->Map_Forest_Active) {
			App->render->camera.x = 575;
			App->render->camera.y = -1200;
			App->player->MinimapCameraBufferX = 4;
			App->player->MinimapCameraBufferY = -4;
		}
		if (App->scenes->Map_Snow_Active) {
			App->render->camera.x = -329;
			App->render->camera.y = -608;
			App->player->MinimapCameraBufferX = -24;
			App->player->MinimapCameraBufferY = 15;
		}
		if (App->scenes->Map_Volcano_Active) {
			App->render->camera.x = 700;
			App->render->camera.y = 10;
			App->player->MinimapCameraBufferX = 4.39;
			App->player->MinimapCameraBufferY = 33;
		}

	}


	//Shop

	if (element == shopButton && type == GUI_Event::EVENT_ONCLICK)
	{
		shopImage->enabled = !shopImage->enabled;
		shopLabel->enabled = !shopLabel->enabled;
		CostLabel->enabled = !CostLabel->enabled;
		buyWoodProducerButton->enabled = !buyWoodProducerButton->enabled;
		buyPaintExtractorButton->enabled = !buyPaintExtractorButton->enabled;
		buyBarrackButton->enabled = !buyBarrackButton->enabled;
		buyHouseButton->enabled = !buyHouseButton->enabled;
		buyMetalGathererButton->enabled = !buyMetalGathererButton->enabled;
		buyTitaniumExtractorButton->enabled = !buyTitaniumExtractorButton->enabled;
		buyLaboratoryButton->enabled = !buyLaboratoryButton->enabled;
		buyTurretButton->enabled = !buyTurretButton->enabled;
		//upgradePaintExtractorButton->enabled = !upgradePaintExtractorButton->enabled;
		//upgradeWoodProducerButton->enabled = !upgradeWoodProducerButton->enabled;

		/*if (!App->entities->woodProducersUpgraded && !upgradeWoodProducerButton->enabled)
			upgradeWoodProducerButton->enabled = true;
		else if(!App->entities->woodProducersUpgraded && upgradeWoodProducerButton->enabled)
			upgradeWoodProducerButton->enabled = false;*/


		/*if (!App->entities->paintExtractorUpgraded && !upgradePaintExtractorButton->enabled)
			upgradePaintExtractorButton->enabled = true;
		else if (!App->entities->paintExtractorUpgraded && upgradePaintExtractorButton->enabled)
			upgradePaintExtractorButton->enabled = false;*/

	}

	if (element == buyPaintExtractorButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->entities->isSelectingPlacement != true) {
			App->entities->isSelectingPlacement = true;
			App->entities->hoveringEntityType = ENTITY_TYPE_PAINT_EXTRACTOR;
			Mix_PlayChannel(-1, App->audio->buy1_sound, 0);
			
		}

		//  priceTimer = App->player->gameTimer.ReadSec();

	}

	if (element == buyTitaniumExtractorButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->entities->isSelectingPlacement != true) {
			App->entities->isSelectingPlacement = true;
			App->entities->hoveringEntityType = ENTITY_TYPE_TITANIUM_EXTRACTOR;
			Mix_PlayChannel(-1, App->audio->buy1_sound, 0);

		}

		//  priceTimer = App->player->gameTimer.ReadSec();

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

	if (element == buyMetalGathererButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->entities->isSelectingPlacement != true) {
			App->entities->isSelectingPlacement = true;

			App->entities->hoveringEntityType = ENTITY_TYPE_METAL_GATHERER;
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

	if (element == upgradePaintExtractorButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->player->metalScrapCount.count >= 200) {

			App->player->metalScrapCount.count -= 200;
			list<Entity*>::iterator upgradeAllPaintExtractor = App->entities->activeBuildings.begin();
			while (upgradeAllPaintExtractor != App->entities->activeBuildings.end()) {

				if ((*upgradeAllPaintExtractor)->entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {

					(*upgradeAllPaintExtractor)->extractionRate *= 1.33f;
				}
				upgradeAllPaintExtractor++;
			}
			upgradePaintExtractorButton->enabled = false;
			App->entities->paintExtractorUpgraded = true;
		}
	}

	if (element == upgradeWoodProducerButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->player->metalScrapCount.count >= 200) {

			App->player->metalScrapCount.count -= 200;
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
		}
	}

	if (element == buyTurretButton && type == GUI_Event::EVENT_ONCLICK) {

		if (App->entities->isSelectingPlacement != true) {

			App->entities->isSelectingPlacement = true;

			App->entities->hoveringEntityType = ENTITY_TYPE_TURRET;
			Mix_PlayChannel(-1, App->audio->buy2_sound, 0);
		}
	}

	//HoverShop

	if (element == buyPaintExtractorButton && type == GUI_Event::EVENT_HOVER) {

		shopHoverPrice->text = "-20P PAINT EXTRACTOR";
		shopHoverPrice->enabled = true;
	}
	else if (element == buyWoodProducerButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-20P WOOD PRODUCER";
		shopHoverPrice->enabled = true;
	}
	else if (element == buyMetalGathererButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-20M WOOD PRODUCER";
		shopHoverPrice->enabled = true;
	}
	else if (element == buyBarrackButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-50W BARRACKS";
		shopHoverPrice->enabled = true;
	}
	else if (element == buyHouseButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-20W HOUSE";
		shopHoverPrice->enabled = true;
	}
	else if (element == buyPainterButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-25P PAINTER";
		shopHoverPrice->enabled = true;
		//shopHoverPrice->map_position;
	}
	else if (element == buyExplorerButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-25P EXPLORER";
		shopHoverPrice->enabled = true;
		//shopHoverPrice->map_position;
	}
	else if (element == buyWarriorButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-20P WARRIOR";
		shopHoverPrice->enabled = true;
	}
	else if (element == buyKnightButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-100P";
		shopHoverPrice->enabled = true;
	}
	else if (element == buyRangerButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-50P RANGER";
		shopHoverPrice->enabled = true;
	}
	else if (element == upgradeWarriorButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-200P UP-WARRIOR";
		shopHoverPrice->enabled = true;

	}
	else if (element == upgradePainterButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-200P UP-PAINTER";
		shopHoverPrice->enabled = true;
	}
	else if (element == upgradePaintExtractorButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-200M UP-PAINT";
		shopHoverPrice->enabled = true;
	}
	else if (element == upgradeWoodProducerButton && type == GUI_Event::EVENT_HOVER) {
		shopHoverPrice->text = "-200M UP-WOOD";
		shopHoverPrice->enabled = true;
	}
	else {
		shopHoverPrice->enabled = false;
	}



	//Townhall shop

	if (element == buyPainterButton && type == GUI_Event::EVENT_ONCLICK) {
		list<Entity*>::iterator onlyTownhallSelected = App->entities->buildingsSelected.begin();
		(*onlyTownhallSelected)->SpawnEntity(ENTITY_TYPE::ENTITY_TYPE_PAINTER);
		painterscount++;
		if (painterscount >= 3)
		{
			PaintersQuestCompleted = true;
		}
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
	// This is only available if there are no explorers alive
	else if (element == buyExplorerButton && type == GUI_Event::EVENT_ONCLICK) {
		list<Entity*>::iterator onlyTownhallSelected = App->entities->buildingsSelected.begin();
		(*onlyTownhallSelected)->SpawnEntity(ENTITY_TYPE::ENTITY_TYPE_EXPLORER);
	}

	//Barracks shop

	if (element == buyWarriorButton && type == GUI_Event::EVENT_ONCLICK) {
		list<Entity*>::iterator onlyBarracksSelected = App->entities->buildingsSelected.begin();
		(*onlyBarracksSelected)->SpawnEntity(ENTITY_TYPE::ENTITY_TYPE_WARRIOR);
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
			UpgradeWarriorQuestCompleted = true;
		}
	}
	else if (element == buyKnightButton && type == GUI_Event::EVENT_ONCLICK) {
		list<Entity*>::iterator onlyBarracksSelected = App->entities->buildingsSelected.begin();
		(*onlyBarracksSelected)->SpawnEntity(ENTITY_TYPE::ENTITY_TYPE_KNIGHT);
	}
	else if (element == buyRangerButton && type == GUI_Event::EVENT_ONCLICK) {
		list<Entity*>::iterator onlyBarracksSelected = App->entities->buildingsSelected.begin();
		(*onlyBarracksSelected)->SpawnEntity(ENTITY_TYPE::ENTITY_TYPE_RANGER);
	}


	//Pause Menu

	if (element == pauseMenuButton && type == GUI_Event::EVENT_ONCLICK)
	{
		App->PAUSE_ACTIVE = true;
		pauseMenu = true;

		App->player->gameTimer.Stop();
		AnimTime = 0;
		PaintRollerAnimation->enabled = true;

		
	}

	if (element == saveButton && type == GUI_Event::EVENT_ONCLICK)
	{
		if (App->scenes->Map_Forest_Active) {
			App->scenes->savedMapForest = true;
			App->scenes->savedMapSnow = false;
			App->scenes->savedMapVolcano = false;
			App->scenes->saved_map = 1;
		}		
		else if (App->scenes->Map_Snow_Active) {
			App->scenes->savedMapForest = false;
			App->scenes->savedMapSnow = true;
			App->scenes->savedMapVolcano = false;
			App->scenes->saved_map = 2;
		}
		else if (App->scenes->Map_Volcano_Active) {
			App->scenes->savedMapForest = false;
			App->scenes->savedMapSnow = false;
			App->scenes->savedMapVolcano = true;
			App->scenes->saved_map = 3;
		}
		App->SaveGame("save_game.xml");
		App->canContinue = true;
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
		fxBar->enabled = true;
			fxSlider->enabled = true;
			musicBar->enabled = true;
			musicSlider->enabled = true;
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
		fxBar->enabled = false;
		fxSlider->enabled = false;
		musicBar->enabled = false;
		musicSlider->enabled = false;
		
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
	

		//BOTH YES BUTTONS ARE THE SAME, SO YOU CANT RESET AND GO TO TITLE AT THE SAME TIME

		/*App->entities->CleanUp();
		App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { 42, 42 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_PAINTER, { 45,  40 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 40, 20 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 13,  5 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 80,  4 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 10, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 80, 75 }, App->entities, nullptr, 0, true);
		App->transition_manager->CreateSlide(SCENES::GAME_SCENE, 0.5f, true, true);*/

		if (exitMenu) {
			App->scenes->exit = true;
		}
		else if (mainMenu)
		{
			App->entities->CleanUp();
			App->transition_manager->CreateSlide(SCENES::MENU_SCENE, 0.5f, true, true);
		}
		else if (restartMenu)
		{
			if (App->scenes->Map_Forest_Active = true) {
				App->scenes->Load_Map_Forest = true;
			    App->transition_manager->CreateFadeToColour(SCENES::GAME_SCENE);
			}
			else if (App->scenes->Map_Snow_Active = true) {
				App->scenes->Load_Map_Snow = true;
				App->transition_manager->CreateFadeToColour(SCENES::GAME_SCENE);
			}
			else {
				App->scenes->Load_Map_Volcano = true;
				App->transition_manager->CreateFadeToColour(SCENES::GAME_SCENE);
			}
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
		if (PaintersQuestActive == true) {
			questsText1Count->enabled = true;
			questsText1->enabled = true;
		}

		if (BarracksQuestActive == true) {
			questsText2Count->enabled = true;
			questsText2->enabled = true;
		}

		if (ExtractPaintQuestActive == true) {
			questsText3Count->enabled = true;
			questsText3->enabled = true;
		}

		if (UpgradeWarriorQuestActive == true) {
			questsText4Count->enabled = true;
			questsText4->enabled = true;
		}

		if (DestroySpawnerQuestActive == true) {
			questsText5Count->enabled = true;
			questsText5->enabled = true;
		}

		if (ExplorerQuestActive == true) {
			questsText6Count->enabled = true;
			questsText6->enabled = true;
		}
	}

	if (element == questsCloseButton && type == GUI_Event::EVENT_ONCLICK) {

		questsText1Count->enabled = false;
		questsText2Count->enabled = false;
		questsText3Count->enabled = false;
		questsText4Count->enabled = false;
		questsText5Count->enabled = false;
		questsText6Count->enabled = false;
		questsText1->enabled = false;
		questsText2->enabled = false;
		questsText3->enabled = false;
		questsText4->enabled = false;
		questsText5->enabled = false;
		questsText6->enabled = false;
	}


	//SETTINGS SLIDER

	
	
		if (element == fxBar && type == GUI_Event::EVENT_HOVER) {

			//CHUNKS VOLUME SHOULD BE DIFFERENT

			//SLIDER POS
			fPoint MousePos = App->input->GetMouseWorldPosition();

			fxSlider->map_position.x = (MousePos.x / 2) - 10 + fxBar->map_position.x;

			
			if (fxSlider->map_position.x >= 560 && fxSlider->map_position.x <= 590) {
				LOG("VOL FX TO 0");
				App->audio->CurrentFXVolume = 0;
			}

			if (fxSlider->map_position.x >= 591 && fxSlider->map_position.x <= 620) {
				LOG("VOL FX TO 1");
				App->audio->CurrentFXVolume = 4;
			}

			if (fxSlider->map_position.x >= 621 && fxSlider->map_position.x <= 650) {
				LOG("VOL  FX TO 2");

				App->audio->CurrentFXVolume = 8;
			}

			if (fxSlider->map_position.x >= 651 && fxSlider->map_position.x <= 680) {
				LOG("VOL  FXTO 3");
				App->audio->CurrentFXVolume = 12;

			}
			if (fxSlider->map_position.x >= 681 && fxSlider->map_position.x <= 710) {
				LOG("VOL FX TO 4");
				App->audio->CurrentFXVolume = 16;

			}
			if (fxSlider->map_position.x >= 711) {
				LOG("VOL FXTO 5");
				App->audio->CurrentFXVolume = 20;
			}


			App->audio->ChunkAudioManager(App->audio->CurrentFXVolume); //SHOULD WE SET ALL CHUNK VOLUMES TO THE SAME VALUE OR DIFFERENT FOR EACH CHUNK?

		}

		if (element == musicBar && type == GUI_Event::EVENT_HOVER) {

			fPoint MousePos = App->input->GetMouseWorldPosition();

			musicSlider->map_position.x = (MousePos.x / 2) - 10 + musicBar->map_position.x;

			//732 611
			if (musicSlider->map_position.x >= 560 && musicSlider->map_position.x <= 590) {
				LOG("VOL MUS TO 0");
				App->audio->CurrentMusVolume = 0;
			}

			if (musicSlider->map_position.x >= 591 && musicSlider->map_position.x <= 620) {
				LOG("VOL MUS TO 1");
				App->audio->CurrentMusVolume = 2;
			}

			if (musicSlider->map_position.x >= 621 && musicSlider->map_position.x <= 650) {
				LOG("VOL MUS TO 2");
				App->audio->CurrentMusVolume = 4;
			}

			if (musicSlider->map_position.x >= 651 && musicSlider->map_position.x <= 680) {
				LOG("VOL MUS TO 3");
				App->audio->CurrentMusVolume = 6;
			}
			if (musicSlider->map_position.x >= 681 && musicSlider->map_position.x <= 710) {
				LOG("VOL MUS TO 4");
				App->audio->CurrentMusVolume = 8;
			}
			if (musicSlider->map_position.x >= 711) {
				LOG("VOL MUS TO 5");
				App->audio->CurrentMusVolume = 10;
			}

			Mix_VolumeMusic(App->audio->CurrentMusVolume);
		}


	

}

void GameScene::ManageMinimap()
{
	float CameraSpeed_Minimap = -0.0000005;
	/*miniMapScopeCamera->map_position.x = miniMapScopeCamera->init_map_position.x + App->render->camera.x*CameraSpeed_Minimap;
	miniMapScopeCamera->map_position.y = miniMapScopeCamera->init_map_position.y + App->render->camera.y*CameraSpeed_Minimap;*/
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
	//App->entities->AddEntity(ENTITY_TYPE_EXPLORER, { 4, 4 }, App->entities, nullptr, 0, true);

	//scattered enemies (slimes)
	if (App->scenes->Map_Forest_Active == true) {

		//App->entities->AddEntity(ENTITY_TYPE_CHROMA_KING, { 2, 2 }, App->entities, nullptr, 0, true);


		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 19, 86 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 86, 19 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 90, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 98, 95 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 34, 70 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 75, 85 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 93, 83 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 92, 67 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 85, 38 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 74, 17 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 37, 7 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 50, 10 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 10, 50 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 7, 37 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 58, 8 }, App->entities, nullptr, 0, true);

	}
	else if (App->scenes->Map_Snow_Active == true) {
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 90, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 95, 95 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 80, 80 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 75, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 90, 75 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 6, 92 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 9, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 6, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 6, 84 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 50, 50 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 46, 48 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 61, 40 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 40, 61 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 51, 64 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 50, 13 }, App->entities, nullptr, 0, true);

	}
	else if (App->scenes->Map_Volcano_Active == true) {

		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 90, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 95, 95 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 80, 80 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 75, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 90, 75 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 6, 92 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 9, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 6, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 6, 84 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 50, 50 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 46, 48 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 61, 40 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 40, 61 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 51, 64 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SLIME, { 50, 13 }, App->entities, nullptr, 0, true);

	}


	if (App->scenes->Map_Forest_Active == true) {

		//town hall
		App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { 42, 42 }, App->entities, nullptr, 0, true);
		//painter
		App->entities->AddEntity(ENTITY_TYPE_PAINTER, { 45,  40 }, App->entities, nullptr, 0, true);
		//spawners
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 40, 20 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 13,  5 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 80,  4 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 10, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 80, 75 }, App->entities, nullptr, 0, true);
		//trying
		//App->entities->AddEntity(ENTITY_TYPE_RANGER, { 40, 25 }, App->entities, nullptr, 0, true);
		//App->entities->AddEntity(ENTITY_TYPE_SLIME, { 2, 2 }, App->entities, nullptr, 0, true);
		//App->entities->AddEntity(ENTITY_TYPE_EXPLORER, { 20, 20 }, App->entities, nullptr, 0, true);


		//enemy waves
		////at minute 5 generate 3 slimes, 1 explosive blob
		//if (App->player->gameTimer.ReadSec() == 300) {
		//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 52 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 32, 32 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 32 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { 32, 52 }, App->entities, nullptr, 0, true);
		//}
		////at minute 8 generate 4 slimes, 2 explosive blobs, 1 rider
		//if (App->player->gameTimer.ReadSec() == 480) {
		//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 52 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 32, 32 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 32 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 32, 52 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { 37, 57 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { 37, 37 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_RIDER, { 57, 57 }, App->entities, nullptr, 0, true);
		//}
		////at minute 11 generate 3 slimes, 2 explosive blobs, 2 riders, 1 chroma king
		//if (App->player->gameTimer.ReadSec() == 660) {
		//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 52 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 32, 32 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_SLIME, { 52, 32 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { 57, 57 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { 37, 37 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_RIDER, { 57, 37 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_RIDER, { 37, 57 }, App->entities, nullptr, 0, true);
		//	App->entities->AddEntity(ENTITY_TYPE_CHROMA_KING, { 60, 60 }, App->entities, nullptr, 0, true);
		//}
		//when 1 spawner destroyed generate 2 slimes, 2 explosive blobs, 1 rider
	
	
	}
	else if (App->scenes->Map_Snow_Active == true) {


		//town hall
		App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { 37, 11 }, App->entities, nullptr, 0, true);
		//painter
		App->entities->AddEntity(ENTITY_TYPE_PAINTER, { 40,  8 }, App->entities, nullptr, 0, true);
		//spawners
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 94, 94 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 62, 11 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, {  9, 90 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 21, 13 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 30, 70 }, App->entities, nullptr, 0, true);
		//enemies



	}
	else if (App->scenes->Map_Volcano_Active == true) {

		//town hall
		App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { 7, 12 }, App->entities, nullptr, 0, true);
		//painter
		App->entities->AddEntity(ENTITY_TYPE_PAINTER, { 9, 10 }, App->entities, nullptr, 0, true);
		//spawners
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, {  7, 47 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 23, 14 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 19, 96 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 95, 95 }, App->entities, nullptr, 0, true);
		App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { 68, 24 }, App->entities, nullptr, 0, true);
		//enemies


		
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

	//LAKE 1

	   App->pathfinding->ChangeToPaintShore({ 4, 50 });
	   App->pathfinding->ChangeToPaintShore({ 5, 50 });
	   App->pathfinding->ChangeToPaintShore({ 6, 50 });
	   App->pathfinding->ChangeToPaintShore({ 7, 50 });
	   App->pathfinding->ChangeToPaintShore({ 4, 51 });
	   App->pathfinding->ChangeToPaint({ 5, 51 });
	   App->pathfinding->ChangeToPaint({ 6, 51 });
	   App->pathfinding->ChangeToPaintShore({ 7, 51 });
	   App->pathfinding->ChangeToPaintShore({ 4, 52 });
	   App->pathfinding->ChangeToPaint({ 5, 52 });
	   App->pathfinding->ChangeToPaint({ 6, 52 });
	   App->pathfinding->ChangeToPaintShore({ 7, 52 });
	   App->pathfinding->ChangeToPaintShore({ 4, 53 });
	   App->pathfinding->ChangeToPaintShore({ 5, 53 });
	   App->pathfinding->ChangeToPaintShore({ 6, 53 });
	   App->pathfinding->ChangeToPaintShore({ 7, 53 });

	//LAKE 2

	   App->pathfinding->ChangeToPaintShore({ 48, 31 });
	   App->pathfinding->ChangeToPaintShore({ 49, 31 });
	   App->pathfinding->ChangeToPaintShore({ 50, 31 });
	   App->pathfinding->ChangeToPaintShore({ 51, 31 });
	   App->pathfinding->ChangeToPaintShore({ 48, 32 });
	   App->pathfinding->ChangeToPaint({ 49, 32 });
	   App->pathfinding->ChangeToPaint({ 50, 32 });
	   App->pathfinding->ChangeToPaintShore({ 51, 32 });
	   App->pathfinding->ChangeToPaintShore({ 48, 33 });
	   App->pathfinding->ChangeToPaint({ 49, 33 });
	   App->pathfinding->ChangeToPaint({ 50, 33 });
	   App->pathfinding->ChangeToPaintShore({ 51, 33 });
	   App->pathfinding->ChangeToPaintShore({ 48, 34 });
	   App->pathfinding->ChangeToPaintShore({ 49, 34 });
	   App->pathfinding->ChangeToPaintShore({ 50, 34 });
	   App->pathfinding->ChangeToPaintShore({ 51, 34 });


	//LAKE 3

	   App->pathfinding->ChangeToPaintShore({ 38, 91 });
	   App->pathfinding->ChangeToPaintShore({ 49, 91 });
	   App->pathfinding->ChangeToPaintShore({ 40, 91 });
	   App->pathfinding->ChangeToPaintShore({ 41, 91 });
	   App->pathfinding->ChangeToPaintShore({ 38, 92 });
	   App->pathfinding->ChangeToPaint({ 39, 92 });
	   App->pathfinding->ChangeToPaint({ 40, 92 });
	   App->pathfinding->ChangeToPaintShore({ 41, 92 });
	   App->pathfinding->ChangeToPaintShore({ 38, 93 });
	   App->pathfinding->ChangeToPaint({ 39, 93 });
	   App->pathfinding->ChangeToPaint({ 40, 93 });
	   App->pathfinding->ChangeToPaintShore({ 41, 93 });
	   App->pathfinding->ChangeToPaintShore({ 38, 94 });
	   App->pathfinding->ChangeToPaintShore({ 39, 94 });
	   App->pathfinding->ChangeToPaintShore({ 40, 94 });
	   App->pathfinding->ChangeToPaintShore({ 41, 94 });

	//LAKE 4

	   App->pathfinding->ChangeToPaintShore({ 64, 69 });
	   App->pathfinding->ChangeToPaintShore({ 65, 69 });
	   App->pathfinding->ChangeToPaintShore({ 66, 69 });
	   App->pathfinding->ChangeToPaintShore({ 67, 69 });
	   App->pathfinding->ChangeToPaintShore({ 68, 69 });
	   App->pathfinding->ChangeToPaintShore({ 69, 69 });
	   App->pathfinding->ChangeToPaintShore({ 64, 70 });
	   App->pathfinding->ChangeToPaint({ 65, 70 });
	   App->pathfinding->ChangeToPaint({ 66, 70 });
	   App->pathfinding->ChangeToPaint({ 67, 70 });
	   App->pathfinding->ChangeToPaint({ 68, 70 });
	   App->pathfinding->ChangeToPaintShore({ 69, 70 });
	   App->pathfinding->ChangeToPaintShore({ 64, 71 });
	   App->pathfinding->ChangeToPaint({ 65, 71 });
	   App->pathfinding->ChangeToPaint({ 66, 71 });
	   App->pathfinding->ChangeToPaint({ 67, 71 });
	   App->pathfinding->ChangeToPaint({ 68, 71 });
	   App->pathfinding->ChangeToPaintShore({ 69, 71 });
	   App->pathfinding->ChangeToPaintShore({ 64, 72 });
	   App->pathfinding->ChangeToPaintShore({ 65, 72 });
	   App->pathfinding->ChangeToPaintShore({ 66, 72 });
	   App->pathfinding->ChangeToPaintShore({ 67, 72 });
	   App->pathfinding->ChangeToPaintShore({ 68, 72 });
	   App->pathfinding->ChangeToPaintShore({ 69, 72 });
	  
	  
	  
	  //LAKE 5


	  
	   App->pathfinding->ChangeToPaintShore({ 89, 41 });
	   App->pathfinding->ChangeToPaintShore({ 90, 41 });
	   App->pathfinding->ChangeToPaintShore({ 91, 41 });
	   App->pathfinding->ChangeToPaintShore({ 92, 41 });
	   App->pathfinding->ChangeToPaintShore({ 93, 41 });
	   App->pathfinding->ChangeToPaintShore({ 94, 41 });
	   App->pathfinding->ChangeToPaintShore({ 89, 42 });
	   App->pathfinding->ChangeToPaint({ 90, 42 });
	   App->pathfinding->ChangeToPaint({ 91, 42 });
	   App->pathfinding->ChangeToPaint({ 92, 42 });
	   App->pathfinding->ChangeToPaint({ 93, 42 });
	   App->pathfinding->ChangeToPaintShore({ 94, 42 });
	   App->pathfinding->ChangeToPaint({ 89, 43 });
	   App->pathfinding->ChangeToPaint({ 90, 43 });
	   App->pathfinding->ChangeToPaint({ 91, 43 });
	   App->pathfinding->ChangeToPaint({ 92, 43 });
	   App->pathfinding->ChangeToPaint({ 93, 43 });
	   App->pathfinding->ChangeToPaintShore({ 94, 43 });
	   App->pathfinding->ChangeToPaintShore({ 89, 44 });
	   App->pathfinding->ChangeToPaintShore({ 90, 44 });
	   App->pathfinding->ChangeToPaintShore({ 91, 44 });
	   App->pathfinding->ChangeToPaintShore({ 92, 44 });
	   App->pathfinding->ChangeToPaintShore({ 93, 44 });
	   App->pathfinding->ChangeToPaintShore({ 94, 44 });

	}
	else if (App->scenes->Map_Volcano_Active == true) {

	//LAKE 1

	App->pathfinding->ChangeToPaintShore({ 1, 1 });
	App->pathfinding->ChangeToPaintShore({ 2, 1 });
	App->pathfinding->ChangeToPaintShore({ 3, 1 });
	App->pathfinding->ChangeToPaintShore({ 4, 1 });
	App->pathfinding->ChangeToPaintShore({ 1, 2 });
	App->pathfinding->ChangeToPaint({ 2, 2 });
	App->pathfinding->ChangeToPaint({ 3, 2 });
	App->pathfinding->ChangeToPaintShore({ 4, 2 });
	App->pathfinding->ChangeToPaintShore({ 1, 3 });
	App->pathfinding->ChangeToPaint({ 2, 3 });
	App->pathfinding->ChangeToPaint({ 3, 3 });
	App->pathfinding->ChangeToPaintShore({ 4, 3 });
	App->pathfinding->ChangeToPaintShore({ 1, 4 });
	App->pathfinding->ChangeToPaintShore({ 2, 4 });
	App->pathfinding->ChangeToPaintShore({ 3, 4 });
	App->pathfinding->ChangeToPaintShore({ 4, 4 });


	//LAKE 2

	App->pathfinding->ChangeToPaintShore({ 4, 70 });
	App->pathfinding->ChangeToPaintShore({ 5, 70 });
	App->pathfinding->ChangeToPaintShore({ 6, 70 });
	App->pathfinding->ChangeToPaintShore({ 7, 70 });
	App->pathfinding->ChangeToPaintShore({ 8, 70 });
	App->pathfinding->ChangeToPaintShore({ 9, 70 });
	App->pathfinding->ChangeToPaintShore({ 4, 71 });
	App->pathfinding->ChangeToPaint({ 5, 71 });
	App->pathfinding->ChangeToPaint({ 6, 71 });
	App->pathfinding->ChangeToPaint({ 7, 71 });
	App->pathfinding->ChangeToPaint({ 8, 71 });
	App->pathfinding->ChangeToPaintShore({ 9, 71 });
	App->pathfinding->ChangeToPaintShore({ 4, 72 });
	App->pathfinding->ChangeToPaint({ 5, 72 });
	App->pathfinding->ChangeToPaint({ 6, 72 });
	App->pathfinding->ChangeToPaint({ 7, 72 });
	App->pathfinding->ChangeToPaint({ 8, 72 });
	App->pathfinding->ChangeToPaintShore({ 9, 72 });
	App->pathfinding->ChangeToPaintShore({ 4, 73 });
	App->pathfinding->ChangeToPaintShore({ 5, 73 });
	App->pathfinding->ChangeToPaintShore({ 6, 73 });
	App->pathfinding->ChangeToPaintShore({ 7, 73 });
	App->pathfinding->ChangeToPaintShore({ 8, 73 });
	App->pathfinding->ChangeToPaintShore({ 9, 73 });


	//LAKE 3



	App->pathfinding->ChangeToPaintShore({ 47, 30 });
	App->pathfinding->ChangeToPaintShore({ 48, 30 });
	App->pathfinding->ChangeToPaintShore({ 49, 30 });
	App->pathfinding->ChangeToPaintShore({ 50, 30 });
	App->pathfinding->ChangeToPaintShore({ 51, 30 });
	App->pathfinding->ChangeToPaintShore({ 52, 30 });
	App->pathfinding->ChangeToPaintShore({ 47, 33 });
	App->pathfinding->ChangeToPaint({ 48, 33 });
	App->pathfinding->ChangeToPaint({ 49, 33 });
	App->pathfinding->ChangeToPaint({ 50, 33 });
	App->pathfinding->ChangeToPaint({ 51, 33 });
	App->pathfinding->ChangeToPaintShore({ 52, 33 });
	App->pathfinding->ChangeToPaintShore({ 47, 32 });
	App->pathfinding->ChangeToPaint({ 48, 32 });
	App->pathfinding->ChangeToPaint({ 49, 32 });
	App->pathfinding->ChangeToPaint({ 50, 32 });
	App->pathfinding->ChangeToPaint({ 51, 32 });
	App->pathfinding->ChangeToPaintShore({ 52, 32 });
	App->pathfinding->ChangeToPaintShore({ 47, 31 });
	App->pathfinding->ChangeToPaintShore({ 48, 31 });
	App->pathfinding->ChangeToPaintShore({ 49, 31 });
	App->pathfinding->ChangeToPaintShore({ 50, 31 });
	App->pathfinding->ChangeToPaintShore({ 51, 31 });
	App->pathfinding->ChangeToPaintShore({ 52, 31 });


      //LAKE 4




	App->pathfinding->ChangeToPaintShore({ 71,3 });
	App->pathfinding->ChangeToPaintShore({ 72, 3 });
	App->pathfinding->ChangeToPaintShore({ 73, 3 });
	App->pathfinding->ChangeToPaintShore({ 74, 3 });
	App->pathfinding->ChangeToPaintShore({ 71,4 });
	App->pathfinding->ChangeToPaint({ 72, 4 });
	App->pathfinding->ChangeToPaint({ 73, 4 });
	App->pathfinding->ChangeToPaintShore({ 74, 4 });
	App->pathfinding->ChangeToPaintShore({ 71,5 });
	App->pathfinding->ChangeToPaint({ 72, 5 });
	App->pathfinding->ChangeToPaint({ 73, 5 });
	App->pathfinding->ChangeToPaintShore({ 74, 5 });
	App->pathfinding->ChangeToPaintShore({ 71,6 });
	App->pathfinding->ChangeToPaintShore({ 72, 6 });
	App->pathfinding->ChangeToPaintShore({ 73, 6 });
	App->pathfinding->ChangeToPaintShore({ 74, 6 });




	//LAKE 5
	
	App->pathfinding->ChangeToPaintShore({ 91,81 });
	App->pathfinding->ChangeToPaintShore({ 92, 81 });
	App->pathfinding->ChangeToPaintShore({ 93, 81 });
	App->pathfinding->ChangeToPaintShore({ 94, 81 });
	App->pathfinding->ChangeToPaintShore({ 91,82 });
	App->pathfinding->ChangeToPaint({ 92, 82 });
	App->pathfinding->ChangeToPaint({ 93, 82 });
	App->pathfinding->ChangeToPaintShore({ 94, 82 });
	App->pathfinding->ChangeToPaintShore({ 91,83 });
	App->pathfinding->ChangeToPaint({ 92, 83 });
	App->pathfinding->ChangeToPaint({ 93, 83 });
	App->pathfinding->ChangeToPaintShore({ 94, 83 });
	App->pathfinding->ChangeToPaintShore({ 91,84 });
	App->pathfinding->ChangeToPaintShore({ 92, 84 });
	App->pathfinding->ChangeToPaintShore({ 93, 84 });
	App->pathfinding->ChangeToPaintShore({ 94, 84 });
	


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
	while (checkForSpawners != App->entities->activeBuildings.end()) { //active buildings always empty after load?

		if ((*checkForSpawners)->entityType == ENTITY_TYPE_SPAWNER) {
			anySpawnerActive = true;
			spawnerscount++;
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
	DialogPage7 = false;
	DialogPage8 = false;
	DialogPage9 = false;
	DialogPage10 = false;
	DialogPage11 = false;
	DialogPage12 = false;
	DialogPage13 = false;
	DialogPage14 = false;
	DialogPage15 = false;
	/*PaintExtractorQuestCompletedSafe = false;
	PainterQuestCompletedSafe = false;
	ExtractPaintQuestCompletedSafe = false;
    UpgradeEntityQuestCompletedSafe=false;*/

	PaintersQuestCompleted = false;
	BarracksQuestCompleted = false;
	ExtractPaintQuestCompleted = false;
	UpgradeWarriorQuestCompleted = false;
	ExplorerQuestCompleted = false;
	DestroySpawnerQuestCompleted = false;

	PaintersQuestActive = false;
	BarracksQuestActive = false;
	ExtractPaintQuestActive = false;
	UpgradeWarriorQuestActive = false;
	ExplorerQuestActive = false;
	DestroySpawnerQuestActive = false;



	Dialog_Text1_Line_1 = "FINALLY OUR HERO HAS ARRIVED";
	Dialog_Text1_Line_2 = "THE CORRUPTION IS SPREADING";
	Dialog_Text1_Line_3 = "WE NEED TO DO SOMETHING";



	Dialog_Text2_Line_1 = " ";
	Dialog_Text2_Line_2 = "FAST - FIND A LAKE OF PAINT";
	Dialog_Text2_Line_3 = " ";



	Dialog_Text3_Line_1 = "LEFT-CLICK THE PAINTER";
	Dialog_Text3_Line_2 = "RIGHT-CLICK ON THE MAP";
	Dialog_Text3_Line_3 = "CTRL FOR MULTIPLE SELECTION";



	Dialog_Text4_Line_1 = "NOW MOVE THE PAINTER TO";
	Dialog_Text4_Line_2 = "THE EDGE OF THE PAINT LAKE";
	Dialog_Text4_Line_3 = " ";



	Dialog_Text5_Line_1 = "NOW GET SOME PAINT";
	Dialog_Text5_Line_2 = "WE WILL NEED RESOURCES TO";
	Dialog_Text5_Line_3 = "DEFEND OURSELVES";



	Dialog_Text6_Line_1 = "PRODUCE 150 PAINT";
	Dialog_Text6_Line_2 = "/ CHECK QUESTS /";
	Dialog_Text6_Line_3 = " ";



	Dialog_Text7_Line_1 = "WAIT";
	Dialog_Text7_Line_2 = "WE ARE NOT GETTING RESOURCES";
	Dialog_Text7_Line_3 = "FAST ENOUGH";



	Dialog_Text8_Line_1 = "CLICK THE SHOP ICON AND";
	Dialog_Text8_Line_2 = "BUILD A PAINT EXTRACTOR";
	Dialog_Text8_Line_3 = "ON THE LAKE";



	Dialog_Text9_Line_1 = "IT WILL PRODUCE PAINT";
	Dialog_Text9_Line_2 = "AUTOMATICALLY";
	Dialog_Text9_Line_3 = " ";



	Dialog_Text10_Line_1 = "SOME BUILDINGS PRODUCE";
	Dialog_Text10_Line_2 = "AUTOMATICALLY AND SOME";
	Dialog_Text10_Line_3 = "NEED PAINTERS";



	Dialog_Text11_Line_1 = "TIME TO START THE OFFENSE";
	Dialog_Text11_Line_2 = "BUILD A BARRACK";
	Dialog_Text11_Line_3 = "/CHECK QUESTS/";



	Dialog_Text12_Line_1 = "USE THE BARRACKS TO CREATE";
	Dialog_Text12_Line_2 = "A WARRIOR AND SELECT IT";
	Dialog_Text12_Line_3 = " ";



	Dialog_Text13_Line_1 = "FIND AN ENEMY OR SPAWNER";
	Dialog_Text13_Line_2 = "AND RIGHT-CLICK IT TO";
	Dialog_Text13_Line_3 = "ATTACK";



	Dialog_Text14_Line_1 = "NOW YOU KNOW THE BASICS";
	Dialog_Text14_Line_2 = "FIND AND DESTROY THE 5";
	Dialog_Text14_Line_3 = "SPAWNERS IN 15 MINUTES";



	Dialog_Text15_Line_1 = "USE THE QUESTS IN THE";
	Dialog_Text15_Line_2 = "TOP-LEFT CORNER AS A GUIDE";
	Dialog_Text15_Line_3 = "THEY WILL GIVE YOU TITANIUM";
	

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
		dialogText1->fontType = FONT::FONT_EXTRA_SMALL_RED;
		dialogText2->text = Dialog_Text3_Line_2;
		dialogText2->fontType = FONT::FONT_EXTRA_SMALL_RED;
		dialogText3->text = Dialog_Text3_Line_3;
		dialogText3->fontType = FONT::FONT_EXTRA_SMALL_RED;
	}
	else if (DialogPage4) {
		dialogText1->text = Dialog_Text4_Line_1;
		dialogText2->text = Dialog_Text4_Line_2;	
		dialogText3->text = Dialog_Text4_Line_3;	 
	}
	else if (DialogPage5) {
		dialogText1->text = Dialog_Text5_Line_1;
		dialogText1->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
		dialogText2->text = Dialog_Text5_Line_2;	  
		dialogText2->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
		dialogText3->text = Dialog_Text5_Line_3;	   
		dialogText3->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
	}
	else if (DialogPage6) {
		dialogText1->text = Dialog_Text6_Line_1;
		dialogText1->fontType = FONT::FONT_EXTRA_SMALL_RED;
		dialogText2->text = Dialog_Text6_Line_2;
		dialogText2->fontType = FONT::FONT_EXTRA_SMALL_RED;
		dialogText3->text = Dialog_Text6_Line_3;
		dialogText3->fontType = FONT::FONT_EXTRA_SMALL_RED;
	}
	else if (DialogPage7) {
		dialogText1->text = Dialog_Text7_Line_1;
		dialogText1->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
		dialogText2->text = Dialog_Text7_Line_2;
		dialogText2->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
		dialogText3->text = Dialog_Text7_Line_3;
		dialogText3->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
	}
	else if (DialogPage8) {
		dialogText1->text = Dialog_Text8_Line_1;
		dialogText1->fontType = FONT::FONT_EXTRA_SMALL_RED;
		dialogText2->text = Dialog_Text8_Line_2;
		dialogText2->fontType = FONT::FONT_EXTRA_SMALL_RED;
		dialogText3->text = Dialog_Text8_Line_3;
		dialogText3->fontType = FONT::FONT_EXTRA_SMALL_RED;
	}
	else if (DialogPage9) {
		dialogText1->text = Dialog_Text9_Line_1;
		dialogText1->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
		dialogText2->text = Dialog_Text9_Line_2;
		dialogText2->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
		dialogText3->text = Dialog_Text9_Line_3;
		dialogText3->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
	}
	else if (DialogPage10) {
		dialogText1->text = Dialog_Text10_Line_1;
		dialogText2->text = Dialog_Text10_Line_2;
		dialogText3->text = Dialog_Text10_Line_3;
	}
	else if (DialogPage11) {
		dialogText1->text = Dialog_Text11_Line_1;
		dialogText1->fontType = FONT::FONT_EXTRA_SMALL_RED;
		dialogText2->text = Dialog_Text11_Line_2;
		dialogText2->fontType = FONT::FONT_EXTRA_SMALL_RED;
		dialogText3->text = Dialog_Text11_Line_3;
		dialogText3->fontType = FONT::FONT_EXTRA_SMALL_RED;
	}
	else if (DialogPage12) {
		dialogText1->text = Dialog_Text12_Line_1;
		dialogText2->text = Dialog_Text12_Line_2;
		dialogText3->text = Dialog_Text12_Line_3;
	}
	else if (DialogPage13) {
		dialogText1->text = Dialog_Text13_Line_1;
		dialogText2->text = Dialog_Text13_Line_2;
		dialogText3->text = Dialog_Text13_Line_3;
	}
	else if (DialogPage14) {
		dialogText1->text = Dialog_Text14_Line_1;
		dialogText1->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
		dialogText2->text = Dialog_Text14_Line_2;
		dialogText2->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
		dialogText3->text = Dialog_Text14_Line_3;
		dialogText3->fontType = FONT::FONT_EXTRA_SMALL_WHITE;
	}
	else if (DialogPage15) {
		dialogText1->text = Dialog_Text15_Line_1;
		dialogText2->text = Dialog_Text15_Line_2;
		dialogText3->text = Dialog_Text15_Line_3;
	}


}

void GameScene::QuestManagerFunction()
{

	if (PaintersQuestCompleted == true) {
		questsText1Count->text = "3/3";
		//Mix_PlayChannel(-1, App->audio->Quest_Audio, 0);
	}

	if (App->entities->BarracksQuestDone == true) { //REMEMBER TO SET THIS BOOL TO FALSE IN CLEANUP OF GAME SCENE OR THIS QUEST WONT WORK
		BarracksQuestCompleted = true;
		if (BarracksQuestCompleted == true) {
			questsText2Count->text = "1/1";
			//Mix_PlayChannel(-1, App->audio->Quest_Audio, 0);
		}
	}

	if (App->player->paintCount.count>=150) {
		ExtractPaintQuestCompleted = true;
		questsText3Count->text = "150/150";
		//Mix_PlayChannel(-1, App->audio->Quest_Audio, 0);
	}

	if (UpgradeWarriorQuestCompleted == true) {
		questsText4Count->text = " 1/1";
		//Mix_PlayChannel(-1, App->audio->Quest_Audio, 0);
	}

	if (spawnerscount < 4) { //REMEMBER TO SET THIS BOOL TO FALSE IN CLEAN UP OF GAME SCENE OR THIS QUEST WONT WORK
		DestroySpawnerQuestCompleted = true;
		if (DestroySpawnerQuestCompleted == true) {
			questsText5Count->text = "1/1";
			//Mix_PlayChannel(-1, App->audio->Quest_Audio, 0);
		}
	}

	if (App->entities->ExplorerQuestDone == true) { //REMEMBER TO SET THIS BOOL TO FALSE IN CLEAN UP OF GAME SCENE OR THIS QUEST WONT WORK
		ExplorerQuestCompleted = true;
		if (ExplorerQuestCompleted == true) {
			questsText2Count->text = "1/1";
			//Mix_PlayChannel(-1, App->audio->Quest_Audio, 0);
		}
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

			/*questsText1Count->enabled = true;
			questsText1->enabled = true;*/

			dialogNext->enabled = true;
			dialogPrev->enabled = true;

		}
		else if (DialogPage3 == true) {

			PaintersQuestActive = true;
			if (App->entities->destinations.size() > 0 || movedstuff) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
				movedstuff = true;
			}
			else {
				dialogNext->enabled = false;
				dialogPrev->enabled = true;
			}

		}
		else if (DialogPage4 == true) {

			/*questsText3Count->enabled = true;
			questsText3->enabled = true;*/
			ExtractPaintQuestActive = true;

			if (App->player->paintCount.count > 50 ) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
			}
			else {
				dialogNext->enabled = false;
				dialogPrev->enabled = true;
			}

		}
		else if (DialogPage5 == true) {

			dialogNext->enabled = true;
			dialogPrev->enabled = true;

		}
		else if (DialogPage6 == true) {

			if (App->player->paintCount.count > 70) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
			}
			else {
				dialogNext->enabled = false;
				dialogPrev->enabled = true;
			}

		}
		else if (DialogPage7 == true) {

			dialogNext->enabled = true;
			dialogPrev->enabled = true;

		}
		else if (DialogPage8 == true) {

			if (App->entities->ExtractorQuestDone == true) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
			}
			else {
				dialogNext->enabled = false;
				dialogPrev->enabled = true;
			}

		}
		else if (DialogPage9 == true) {

			dialogNext->enabled = true;
			dialogPrev->enabled = true;

		}
		else if (DialogPage10 == true) {

			dialogNext->enabled = true;
			dialogPrev->enabled = true;

		}
		else if (DialogPage11 == true) {

			BarracksQuestActive = true;
			if (App->entities->BarracksQuestDone == true) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
			}
			else {
				dialogNext->enabled = false;
				dialogPrev->enabled = true;
			}

		}
		else if (DialogPage12 == true) {

			if (App->entities->WarriorQuestDone == true) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
			}
			else {
				dialogNext->enabled = false;
				dialogPrev->enabled = true;
			}

		}
		else if (DialogPage13 == true) {

			if (App->entities->AttackQuestDone == true) {
				dialogNext->enabled = true;
				dialogPrev->enabled = true;
			}
			else {
				dialogNext->enabled = false;
				dialogPrev->enabled = true;
			}
		}
		else if (DialogPage14 == true) {

		UpgradeWarriorQuestActive = true;
		dialogNext->enabled = true;
		dialogPrev->enabled = true;

		}
		else if (DialogPage15 == true) {

		DestroySpawnerQuestActive = true;
		ExplorerQuestActive = true;
		dialogNext->enabled = false;
		dialogPrev->enabled = true;

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




