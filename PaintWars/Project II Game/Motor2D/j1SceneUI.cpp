#include "j1App.h"
#include "j1SceneUI.h"
#include "j1Scene.h"
#include "j1MenuScene.h"
#include "p2Log.h"
#include "j1Input.h"
#include "j1ElementUI.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Player.h"
#include "j1LabelUI.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "j1EntityManager.h"

#include "j1BarUI.h"




#include "SDL/include/SDL.h"

j1Scene_UI::j1Scene_UI() : j1Module()
{
	name.create("scene_UI");
}

// Destructor
j1Scene_UI::~j1Scene_UI()
{}

// Called before render is available
bool j1Scene_UI::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene UI");
	bool ret = true;
	path.create(config.child("path").child_value());
	OnMainMenu = true;
	OnIngameMenu = false;
	OnIngameUI = false;
	ResetEntitiesPositionNewGame = false;
	bMuteSettingsON = false;
	bMuteSettingsOFF = true;
	bMuteIngameON = false;
	bMuteIngameOFF = true;
	LifeAt4 = true;
	HealthChanged = false;
	Menu_Music = true;
	ConsoleSecurity = true;
	OcupyConsoleLOG1 = true;
	OcupyConsoleLOG2 = true;
	OcupyConsoleLOG3 = true;
	OcupyConsoleLOG4 = true;
	OcupyConsoleLOG5 = true;
	VolumeMusicBoxPos.x = 420;
	VolumeMusicBoxPos.y = 372;

	VolumeFXBoxPos.x =650;
	VolumeFXBoxPos.y = 372;
	
	
	return ret;
}

// Called before the first frame
bool j1Scene_UI::Start()
{
	bool ret = true;

	//MAIN MENU----------------------------------------------------------------------------------------------------------------------------------------------------
	MainMenu_UI.add(App->gui->CreateSprite({ -1,-1 }, { 36,866,1037,479 }, true));//BACKGROUND MAIN MENU
	SDL_Rect PlayButtonMenu[3] = { { 1030,479,165,76 }, { 1030,479,165,76 }, { 1030,479,165,76 } };
	SDL_Rect SettingsButtonMenu[3] = { {278,111,100,90},{278,111,100,90},{278,111,100,90} };
	SDL_Rect LinkButtonMenu[3] = { {191,135,64,66}, {191,135,64,66}, {191,135,64,66} };
	SDL_Rect ExitButtonMenu[3] = { {219,213,65,67}, { 219,213,65,67 }, { 219,213,65,67 } };
	SDL_Rect CreditsButtonOpen[3] = { {100,450,65,67},{100,450,65,67},{100,450,65,67} };
	MainMenu_UI.add(App->gui->CreateSprite({ 250,5 }, { 1070,10,530,465 }, true));
	MainMenu_UI.add(App->gui->CreateSprite({ 375,0 }, { 690,480,280,65 }, true));
	MainMenu_Buttons.add(App->gui->CreateButton({ 325,100 }, Button_Type::START_PLAY, PlayButtonMenu[0], &PlayButtonMenu[1], &PlayButtonMenu[1], "Play Button Menu", true));
	MainMenu_Buttons.add(App->gui->CreateButton({ 550,100 }, Button_Type::START_CONTINUE, PlayButtonMenu[0], &PlayButtonMenu[1], &PlayButtonMenu[1], "Continue Button Menu", true));
	MainMenu_Buttons.add(App->gui->CreateButton({ 600,230 }, Button_Type::START_SETTINGS, SettingsButtonMenu[0], &SettingsButtonMenu[1], &SettingsButtonMenu[1], "Settings Button Menu", true));
	MainMenu_Buttons.add(App->gui->CreateButton({ 400,350 }, Button_Type::EXIT, ExitButtonMenu[0], &ExitButtonMenu[1], &ExitButtonMenu[1], "Exit Game Button Menu", true));
	MainMenu_Buttons.add(App->gui->CreateButton({ 300,350 }, Button_Type::LINK, LinkButtonMenu[0], &LinkButtonMenu[1], &LinkButtonMenu[1], "Link Button Menu", true));
	MainMenu_Buttons.add(App->gui->CreateButton({ 500,355 }, Button_Type::CREDITS_MENU, CreditsButtonOpen[0], &CreditsButtonOpen[1], &CreditsButtonOpen[1], "Credits Button Menu", true));
	
	MainMenu_UI.add(App->gui->CreateLabel({ 410, 10}, "PROJECT CETA", Label_Type::MAIN_TITLE, { 255,255,255,255 }, true));
	MainMenu_UI.add(App->gui->CreateLabel({ 380, 115 }, "Play", Label_Type::BUTTON, { 255,255,255,255 }, true));
	MainMenu_UI.add(App->gui->CreateLabel({ 585, 115 }, "Continue", Label_Type::BUTTON, { 255,255,255,255 }, true));
	MainMenu_UI.add(App->gui->CreateSprite({ 360,180 }, { 55,540,97,160 }, true));


	//INGAME--------------------------------------------------------------------------------------------------------------------------------------------------------
	PlayerUI_Ingame.add(App->gui->CreateLabel({ 450, 5 }, "TIME", Label_Type::FONT, { 255,255,255,255 }, true));
	PlayerUI_Ingame.add(timer_label = App->gui->CreateLabel({ 550,5 }, timer_string, Label_Type::FONT, { 255,255,255,255 }, true));
	//BACKPLAYER SQUARE
	PlayerUI_Ingame.add(Map_Icon[0] = (App->gui->CreateSprite({ 900,4 }, { 200,34,52,50 }, true)));
	//HEALTH START
	PlayerUI_Ingame.add(lifes[0] = (App->gui->CreateSprite({ 5,10 }, { 458,45,110,34 }, true)));
	PlayerUI_Ingame.add(player_status[0] = (App->gui->CreateSprite({ 120,10 }, { 413,45,20,35 }, true)));
	//COLLECTABLE
	PlayerUI_Ingame.add(score_label = App->gui->CreateLabel({ 870,4 }, "x0", Label_Type::CONFIG, { 255,255,255,255 }, true));
	//BUTTONS MENU INGAME TESTING
	SDL_Rect ButtonsStates[3] = { {80,30,100,100},{80,245,100,100},{80,140,100,100} };
	SDL_Rect ButtonLoad[2] = { {169,1914,70,66},{169,1914,70,66 } };
	SDL_Rect ButtonSave[2] = { {328,1914,70,70},{328,1914,70,70} };
	SDL_Rect ButtonClose[1] = { 290,210,70,70 };
	SDL_Rect ButtonMuted[1] = { 353,609,64,66 };
	SDL_Rect ButtonNOTMuted[1] = { 246,606,65,65 };
	SDL_Rect ButtonToMenu[1] = {254,1920,54,55};

	//MENU INGAME TEXT AND OTHER THINGS
	Menu_Listed_Ingame.add(App->gui->CreateSprite({ 300,0 }, { 56,1435,464,465 }, true));
	//Menu_Listed_Ingame.add(App->gui->CreateSprite({ 300,0 }, { 590,10,460,465 }, true));
	//Menu_Listed_Ingame.add(App->gui->CreateSprite({ 400,0 }, { 690,480,280,65 }, true));
	Menu_Listed_Ingame.add(App->gui->CreateLabel({ 480,295 }, "PAUSED", Label_Type::FONT, { 255,255,255,255 }, true));
	Buttons_Listed_Ingame.add(App->gui->CreateButton({400,360 }, Button_Type::LOAD, ButtonLoad[0], &ButtonLoad[1], &ButtonLoad[1], "Loading Button", true));
	Buttons_Listed_Ingame.add(App->gui->CreateButton({ 575,360 }, Button_Type::SAVE, ButtonSave[0], &ButtonSave[1], &ButtonSave[1], "Saving Butoon", true));
	MuteIngame_Button.add(App->gui->CreateButton({ 350,225 }, Button_Type::MUTE, ButtonMuted[0], &ButtonMuted[0], &ButtonMuted[0], "Mute ON Button", true));
	UnMuteIngame_Button.add(App->gui->CreateButton({ 352,223 }, Button_Type::UNMUTE, ButtonNOTMuted[0], &ButtonNOTMuted[0], &ButtonNOTMuted[0], "Mute OFF Button", true));
	Buttons_Listed_Ingame.add(App->gui->CreateButton({ 497,365 }, Button_Type::MENU, ButtonToMenu[0], &ButtonToMenu[0], &ButtonToMenu[0], "To Menu", true));
	//Menu_Listed_Ingame.add(App->gui->CreateLabel({ 420, 175 }, "Load", Label_Type::FONT, { 255,255,255,255 }, true));
	//Menu_Listed_Ingame.add(App->gui->CreateLabel({ 600, 175 }, "Save", Label_Type::FONT, { 255,255,255,255 }, true));
	Buttons_Listed_Ingame.add(App->gui->CreateButton({ 680,15 }, Button_Type::CLOSE, ButtonClose[0], &ButtonClose[0], &ButtonClose[0], "Close Menu", true));
	

	
	//SETTINGS MENU
	SettingsMenu_UI.add(App->gui->CreateSprite({ 300,0 }, { 56,1435,464,465 }, true));
	SettingsMenu_UI.add(App->gui->CreateLabel({ 455, 145 }, "Project   Ceta", Label_Type::FONT, { 255,255,255,255 }, true));
	MuteSettings_Button.add(App->gui->CreateButton({ 485,365 }, Button_Type::MUTE, ButtonMuted[0], &ButtonMuted[0], &ButtonMuted[0], "Mute ON Button", true));
	UnMuteSettings_Button.add(App->gui->CreateButton({ 487,363 }, Button_Type::UNMUTE, ButtonNOTMuted[0], &ButtonNOTMuted[0], &ButtonNOTMuted[0], "Mute OFF Button", true));
	SettingsMenu_UI.add(App->gui->CreateLabel({ 450,295 }, "SETTINGS", Label_Type::FONT, { 255,255,255,255 }, true));
	SettingsMenu_UI.add(App->gui->CreateSprite({ 360,375 }, { 494,207,94,28 }, true));
	SettingsMenu_UI.add(App->gui->CreateSprite({ 580,375 }, { 494,207,94,28 }, true));
	SDL_Rect Slider1Rect[1] = { 375,466,38,34 };
	SDL_Rect Slider2Rect[2] = { 375,466,38,34 };

	//SettingsMenu_UI.add(MusicSliderBox=App->gui->CreateSprite({VolumeMusicBoxPos.x,VolumeMusicBoxPos.y}, { 375,466,38,34 }, true));
	//SettingsMenu_UI.add(FXSliderBox=App->gui->CreateSprite({VolumeFXBoxPos.x,VolumeFXBoxPos.y}, { 375,466,38,34 }, true));
	SettingsMenu_Buttons.add(MusicSliderBox = App->gui->CreateButton({ VolumeMusicBoxPos.x,VolumeMusicBoxPos.y }, Button_Type::BOX_SLIDER1,
	Slider1Rect[0],&Slider1Rect[0], Slider1Rect,"SLIDER1",true));

	SettingsMenu_Buttons.add(FXSliderBox = App->gui->CreateButton({ VolumeFXBoxPos.x,VolumeFXBoxPos.y }, Button_Type::BOX_SLIDER2,
	Slider2Rect[0], &Slider2Rect[0], Slider2Rect, "SLIDER2", true));
	SettingsMenu_UI.add(App->gui->CreateLabel({ 585,345 }, "Fx Volume", Label_Type::SLIDERS_FONTS, { 255,255,255,255 }, true));
	SettingsMenu_UI.add(App->gui->CreateLabel({ 350,343 }, "Music Volume", Label_Type::SLIDERS_FONTS, { 255,255,255,255 }, true));
	
	//SettingsMenu_UI.add(App->gui->CreateSprite({ 285,0 }, { 590,10,460,465 }, true));
	//SettingsMenu_UI.add(App->gui->CreateSprite({ 375,0 }, { 690,480,280,65 }, true));
	//SDL_Rect SettingsMenu_MuteON[1] = { 460,275,100,90 };
	//SDL_Rect SettingsMenu_MuteOFF[1] = { 460,388,100,90 };
	SDL_Rect SettingsMenu_Close[1] = { 290,210,70,70 };
	//SDL_Rect SliderBox[1] = { 375,466,38,34 };
	//MuteSettings_Button.add(App->gui->CreateButton({ 575,310 }, Button_Type::MUTE, SettingsMenu_MuteON[0], &SettingsMenu_MuteON[0], &SettingsMenu_MuteON[0], "Settings Mute Button", true));
	//UnMuteSettings_Button.add(App->gui->CreateButton({ 575,310 }, Button_Type::UNMUTE, SettingsMenu_MuteOFF[0], &SettingsMenu_MuteOFF[0], &SettingsMenu_MuteOFF[0], "Settings Unmute Button", true));
	SettingsMenu_Buttons.add(App->gui->CreateButton({ 680,15 }, Button_Type::CLOSE_SETTINGS, SettingsMenu_Close[0], &SettingsMenu_Close[0], &SettingsMenu_Close[0], "Close Settings Menu ", true));
	//SettingsMenu_UI.add(App->gui->CreateSlider({ 435,125 }, { 429,206,158,30 }, true));
	//SettingsMenu_UI.add(App->gui->CreateSlider({ 435,250 }, { 429,206,158,30 }, true));
	//SettingsMenu_UI.add(App->gui->CreateLabel({ 435,10 }, "SETTINGS", Label_Type::FONT, { 255,255,255,255 }, true));
	Menu_Listed_Ingame.add(App->gui->CreateLabel({ 455, 145 }, "Project   Ceta", Label_Type::FONT, { 255,255,255,255 }, true));
	//SettingsMenu_UI.add(App->gui->CreateSprite({ 400,99 }, { 375,466,38,34 }, true));
	//SettingsMenu_Buttons.add(App->gui->CreateButton({ 400,99 }, Button_Type::SLIDER_BOX, SliderBox[0], &SliderBox[0], &SliderBox[0], "Slider Box", true));
	//SettingsMenu_UI.add(App->gui->CreateLabel({435, 150 }, "Music Volume", Label_Type::FONT, { 255,255,255,255 }, true));

	//CREDITS MENU
	SDL_Rect CreditsClose_Button[3] = { {290,210,70,70},{290,210,70,70},{290,210,70,70} };
	CreditsMenu_UI.add(App->gui->CreateSprite({ 285,0 }, { 590,10,460,465 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 450,40 }, "MADE BY:", Label_Type::CONFIG, { 255,255,255,255 }, true));
	CreditsMenu_Buttons.add(App->gui->CreateButton({ 690,0 }, Button_Type::CREDITS_CLOSE, SettingsMenu_Close[0], &SettingsMenu_Close[0], &SettingsMenu_Close[0], "Close Menu", true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 350, 90 }, "Marc Ariza Alborni", Label_Type::TEXT, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 500, 90 }, "&", Label_Type::TEXT, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 520, 90 }, "Adrian Mirabel Martinez", Label_Type::TEXT, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 350, 120 }, "Copyright (c) [2019] [Marc Ariza, Adrian Mirabel]", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 140 }, "Permission is hereby granted, free of charge, to any person ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 155 }, "obtaining a copyof this software and associated  ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 170 }, "documentation files (the Software), to deal in the Software  ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 185 }, "without restriction, including without limitation the rights ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 200 }, "to use, copy, modify, merge, publish,distribute, sublicense,  ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 215 }, "and/or sell copies of the Software, and to permit persons to", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 230 }, "whom the Software is furnished to do so,subject to ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 245 }, "the following conditions: ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 335, 260 }, "The above copyright notice and this permission notice shall be", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 275 }, "included in all copies or substantial portions of the Software.", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 290 }, "THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 305 }, "OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 320}, "NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 335 }, "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 350 }, "IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 365 }, "BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 380 }, "WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 395 }, "ARISING FROM, OUT OF OR IN CONNECTION WITH THE ", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));
	CreditsMenu_UI.add(App->gui->CreateLabel({ 340, 410 }, "SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.", Label_Type::TEXT_SMALL, { 255,255,255,255 }, true));

	//CONSOLE
	SDL_Rect MainConsoleButton[1] = { {656,1354,95,35} };
	SDL_Rect SecondaryConsoleButton[1] = {{656,1394,100,40 }};
	Console_UI.add(App->gui->CreateSprite({ 0,0 }, { 657,1463,1036,285 }, true));
	//Console_Button.add(App->gui->CreateButton({ 500,10 }, Button_Type::CONSOLE_SECONDARY, SecondaryConsoleButton[0], &SecondaryConsoleButton[0], &SecondaryConsoleButton[0],
	//"Console Secondary Button", true));
	//1 COLUMN
	Console_Button.add(App->gui->CreateButton({ 5,10 }, Button_Type::CONSOLE_KILL, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
	"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 30, 13 }, "KILL", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 5,55 }, Button_Type::CONSOLE_HPLESS, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
	"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 30, 58 }, "-1 HP", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 5,100 }, Button_Type::CONSOLE_HPMORE, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
	"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 30, 103 }, "+1 HP", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 5,145 }, Button_Type::CONSOLE_HPFULL, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
	"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 16, 148 }, "FULL HP", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 5,190 }, Button_Type::CONSOLE_GOD, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
	"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 10, 193 }, "GodMode", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));

	//2 COLUMN
	Console_Button.add(App->gui->CreateButton({ 105,10 }, Button_Type::CONSOLE_NOCAP, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
	"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 108, 13 }, "FPS noCap", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 105,55 }, Button_Type::CONSOLE_30CAP, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
	"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 125, 61 }, "30 FPS", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 105,100 }, Button_Type::CONSOLE_60CAP, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
	"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 125, 106 }, "60 FPS", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 105,145 }, Button_Type::CONSOLE_YESVSYNC, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
	"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 110, 148 }, "Vsync ON", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 105,190 }, Button_Type::CONSOLE_NOVSYNC, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
	"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 109, 193 }, "Vsync OFF", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));

	//3 COLUMN
	Console_Button.add(App->gui->CreateButton({ 210,10 }, Button_Type::CONSOLE_RESETENTITY, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
		"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 213, 13 }, "ResetEntit", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 210, 55 }, Button_Type::CONSOLE_MAP1, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
		"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 230, 59 }, "MAP 1", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 210, 101 }, Button_Type::CONSOLE_MAP2, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
		"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 230, 105 },"MAP 2", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 210,145 }, Button_Type::CONSOLE_COLLECTMORE, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
		"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 217, 148 }, "Collect +1", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_Button.add(App->gui->CreateButton({ 210,190 }, Button_Type::CONSOLE_COLLECTLESS, MainConsoleButton[0], &MainConsoleButton[0], &MainConsoleButton[0],
		"Console Primary Button", true));
	Console_UI.add(App->gui->CreateLabel({ 217, 193 }, "Collect -1", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));

	Console_UI.add(ConsoleWarning = App->gui->CreateLabel({ 10,250 }, "----------------------", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));

	Console_UI.add(ConsoleLOG1 = App->gui->CreateLabel({630,10 },"LOG1----------------------", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_UI.add(ConsoleLOG2 = App->gui->CreateLabel({630,40 },"LOG2----------------------", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_UI.add(ConsoleLOG3 = App->gui->CreateLabel({630,70 },"LOG3----------------------", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_UI.add(ConsoleLOG4 = App->gui->CreateLabel({630,100 },"LOG4----------------------", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));
	Console_UI.add(ConsoleLOG5 = App->gui->CreateLabel({630,130 },"LOG5----------------------", Label_Type::CONSOLE, { {150},{100},{255},{255} }, true));

	//MusicSliderBox->pos.x = 100;
	//SETTINGS MENU LISTS
	p2List_item<UIitem_Button*>*SettingsMenuButton_item = SettingsMenu_Buttons.start;
	while (SettingsMenuButton_item != NULL)
	{
		SettingsMenuButton_item->data->visible = false;
		SettingsMenuButton_item = SettingsMenuButton_item->next;
	}
	p2List_item<UI_Item*>*SettingsMenu_item = SettingsMenu_UI.start;
	while (SettingsMenu_item != NULL)
	{
		SettingsMenu_item->data->visible = false;
		SettingsMenu_item = SettingsMenu_item->next;
	}
	//LISTS INGAME MENUS & INTERFACE
	p2List_item<UIitem_Button*>* button_item = Buttons_Listed_Ingame.start;
	while (button_item != NULL)
	{
		button_item->data->visible = false;
		button_item = button_item->next;
	}
	p2List_item<UI_Item*>* ui_item = Menu_Listed_Ingame.start;
	while (ui_item != NULL)
	{
		ui_item->data->visible = false;
		ui_item = ui_item->next;
	}
	p2List_item<UI_Item*>* PlayerUI_item = PlayerUI_Ingame.start;
	while (PlayerUI_item != NULL)
	{
		PlayerUI_item->data->visible = false;
		PlayerUI_item = PlayerUI_item->next;
	}
	//MAIN MENU LISTS
	p2List_item<UI_Item*>* MenuUI_item = MainMenu_UI.start;
	while (MenuUI_item != NULL)
	{
		MenuUI_item->data->visible = false;
		MenuUI_item = MenuUI_item->next;
	}
	p2List_item<UIitem_Button*>* MenuButtons_item = MainMenu_Buttons.start;
	while (MenuButtons_item != NULL)
	{
		MenuButtons_item->data->visible = false;
		MenuButtons_item = MenuButtons_item->next;
	}
	//CREDITS MENU
	p2List_item<UI_Item*>* CreditsUI_item = CreditsMenu_UI.start;
	while (CreditsUI_item != NULL)
	{
		CreditsUI_item->data->visible = false;
		CreditsUI_item = CreditsUI_item->next;
	}
	p2List_item<UIitem_Button*>* CreditsButtons_item = CreditsMenu_Buttons.start;
	while (CreditsButtons_item != NULL)
	{
		CreditsButtons_item->data->visible = false;
		CreditsButtons_item = CreditsButtons_item->next;
	}

	//MUTE & UNMUTE SETTINGS
	p2List_item<UIitem_Button*>* MuteButtons_item = MuteSettings_Button.start;
	while (MuteButtons_item != NULL)
	{
		MuteButtons_item->data->visible = false;
		MuteButtons_item = MuteButtons_item->next;
	}

	p2List_item<UIitem_Button*>* UnMuteButtons_item = UnMuteSettings_Button.start;
	while (UnMuteButtons_item != NULL)
	{
		UnMuteButtons_item->data->visible = false;
		UnMuteButtons_item = UnMuteButtons_item->next;
	}

	//MUTE & UNMUTE INGAME
	p2List_item<UIitem_Button*>* MuteButtons_item2 = MuteIngame_Button.start;
	while (MuteButtons_item2 != NULL)
	{
		MuteButtons_item2->data->visible = false;
		MuteButtons_item2 = MuteButtons_item2->next;
	}

	p2List_item<UIitem_Button*>* UnMuteButtons_item2 = UnMuteIngame_Button.start;
	while (UnMuteButtons_item2 != NULL)
	{
		UnMuteButtons_item2->data->visible = false;
		UnMuteButtons_item2 = UnMuteButtons_item2->next;
	}
	//CONSOLE 
	//BUTTONS CONSOLE
	p2List_item<UIitem_Button*>*  Listed_ConsoleButton2 = Console_Button.start;
	while (Listed_ConsoleButton2 != NULL)
	{
		Listed_ConsoleButton2->data->visible = false;
		Listed_ConsoleButton2 = Listed_ConsoleButton2->next;
	}
	//UI CONSOLE
	p2List_item<UI_Item*>* Listed_ConsoleUI2 = Console_UI.start;
	while (Listed_ConsoleUI2 != NULL)
	{
		Listed_ConsoleUI2->data->visible = false;

		Listed_ConsoleUI2 = Listed_ConsoleUI2->next;
	}

	if (OnMainMenu == true) {
		MainMenuON();
	}

	return ret;
}

// Called each loop iteration
bool j1Scene_UI::PreUpdate(float dt)
{
	return true;
}

// Called each loop iteration
bool j1Scene_UI::Update(float dt)
{

	if ((OnMainMenu == true || OnSettingsMenu == true || OnCreditsMenu == true) && (Menu_Music == true)) {

		App->audio->PlayMusic("audio/Music/MenuMusicAudio.ogg");
		Menu_Music = false;
	}

	


	

	

	

	

	ResetEntitiesPositionNewGame = false;
	PlayerInvencibility = true;

	//SETTINGS BUTTONS MAIN MENU
	if (OnSettingsMenu == true) {

		p2List_item<UIitem_Button*>* SettingsMenuButton_item = SettingsMenu_Buttons.start;
		while (SettingsMenuButton_item != NULL) {
			if (SettingsMenuButton_item->data->OnClick()) {

				switch (SettingsMenuButton_item->data->GetType())
				{

				

				case CLOSE_SETTINGS:
					LOG("CLOSE SETTINGS MENU");
					
						SettingsMenuOFF();
						OnSettingsMenu = false;
						OnMainMenu = true;
						OnIngameMenu = false;
						MuteSettingsOFF();
						UnMuteSettingsOFF();
						MuteSettingsOFF();
					    UnMuteSettingsOFF();
						break;


				}
			}
			SettingsMenuButton_item = SettingsMenuButton_item->next;
		}

		p2List_item<UIitem_Button*>* SliderSettings_item3 = SettingsMenu_Buttons.start;
		while (SliderSettings_item3 != NULL) {
			if (SliderSettings_item3->data->SliderClick()) {

				switch (SliderSettings_item3->data->GetType())
				{

				
				case BOX_SLIDER1:
					//VolumeMusicBoxPos.x = App->gui->
					LOG("SLIDER MUSIC");
					if((VolumeMusicBoxPos.x < 447)&&(VolumeMusicBoxPos.x>367)){
					MusicSliderBox->pos.x = VolumeMusicBoxPos.x - 20;
					
					
					   if ((VolumeMusicBoxPos.x < 447) && (VolumeMusicBoxPos.x >= 410)) {
						  
						  
					   }
					   
					   if ((VolumeMusicBoxPos.x < 409) && (VolumeMusicBoxPos.x >= 380)) {
						  
						 
					   }

					   if ((VolumeMusicBoxPos.x < 379) && (VolumeMusicBoxPos.x >= 367)) {
						  
						 
					   }
					}

					break;


				case BOX_SLIDER2:
					if ((VolumeFXBoxPos.x < 670) && (VolumeFXBoxPos.x > 590)) {
						FXSliderBox->pos.x = VolumeFXBoxPos.x - 20;

						if ((VolumeFXBoxPos.x < 447) && (VolumeFXBoxPos.x >= 410)) {
							
							
						}

						if ((VolumeFXBoxPos.x < 409) && (VolumeFXBoxPos.x >= 380)) {
							
							
						}

						if ((VolumeFXBoxPos.x < 379) && (VolumeFXBoxPos.x >= 367)) {
							
							
						}
					}
					LOG("SLIDER FX");
					break;

				}
			}
			SliderSettings_item3 = SliderSettings_item3->next;
		}
	}
	
	
	
	//CREDITS MENU
	if (OnCreditsMenu == true) {

		p2List_item<UIitem_Button*>*CreditsMenuButton_item = CreditsMenu_Buttons.start;
		while (CreditsMenuButton_item != NULL) {
			if (CreditsMenuButton_item->data->OnClick()) {

				switch (CreditsMenuButton_item->data->GetType())
				{

				case CREDITS_CLOSE:
					LOG("CREDITS MENU CLOSED");
					CreditsMenuOFF();
					OnCreditsMenu = false;
					OnMainMenu = true;

					break;

				}
			}
			CreditsMenuButton_item = CreditsMenuButton_item->next;
		}
	}

	//MAIN MENU 
	if (OnMainMenu == true) {
		p2List_item<UIitem_Button*>* MainMenuButtons = MainMenu_Buttons.start;
		while (MainMenuButtons != NULL) {
			if (MainMenuButtons->data->OnClick()) {

				switch (MainMenuButtons->data->GetType())
				{

				case START_PLAY:
					
					LOG("MAIN MENU PLAY BUTTON");
					App->SaveGame("save_game.xml");
						
					MainMenuOFF();
					IngamePlayerUION();
					OnMainMenu = false;
					OnIngameMenu = false;
					

					ResetEntitiesPositionNewGame = true;
					

					

					

					
					Menu_Music = true;


				    break;

				case START_CONTINUE:
					LOG("MAIN MENU CONTINUE BUTTON");
					MainMenuOFF();
					IngamePlayerUION();
					OnMainMenu = false;
					OnIngameMenu =false;

					
					Menu_Music = true;
				
					break;

				case START_SETTINGS:
					LOG("MAIN MENU SETTINGS BUTTON");
					SettingsMenuON();
					OnSettingsMenu = true;
					OnMainMenu = false;
					OnIngameMenu = false;
					if (bMuteSettingsOFF == true) {
						MuteSettingsOFF();
						UnMuteSettingsON();
					}
					else {
						MuteSettingsON();
						UnMuteSettingsOFF();
					}
					
					break;
				
				case LINK:
					ShellExecuteA(NULL, "open", "https://arizamarc1999.wixsite.com/projectceta", NULL, NULL, SW_SHOWNORMAL);
					break;

				case EXIT:
					return false;
					break;

				case CREDITS_MENU:
					LOG("CREDITS MENU OPEN");
					CreditsMenuON();
					OnCreditsMenu = true;
					OnMainMenu = false;

					break;

				}
			}
			MainMenuButtons = MainMenuButtons->next;
		}
	}

	
	//INGAME MENU
	if (OnIngameMenu == true) {
		p2List_item<UIitem_Button*>* ActionButtons = Buttons_Listed_Ingame.start;
		while (ActionButtons != NULL)
		{
			if (ActionButtons->data->OnClick())
			{
				switch (ActionButtons->data->GetType())
				{
				case SAVE:
					//App->SaveGame("save_game.xml");
					LOG("SAVE BUTTON");


					break;

				case LOAD:
					//App->LoadGame();
					LOG("LOAD BUTTON");

					break;

				case MENU:
					LOG("TO MENU BUTTON");
					OnMainMenu = true;
					OnIngameMenu = false;
					IngameMenuOFF();
					/*MainMenu();
					MainMenu();*/
					MainMenuON();
					App->scene_ui->MuteIngameOFF();
					App->scene_ui->UnMuteIngameOFF();
					IngamePlayerUIOFF();
					
					App->audio->PlayMusic("audio/Music/MenuMusicAudio.ogg");

					

					break;

			

				case CLOSE:
					App->scene_ui->IngameMenuOFF();
					App->scene_ui->OnIngameMenu = false;

					App->scene_ui->MuteIngameOFF();
					App->scene_ui->UnMuteIngameOFF();
				}
			}
			ActionButtons = ActionButtons->next;
		}
	}

	//MUTE & UNMUTE SETTINGS
	if (OnSettingsMenu == true) {
		if (bMuteSettingsON == true) {
			p2List_item<UIitem_Button*>*Mute2MenuButton_item = MuteSettings_Button.start;
			while (Mute2MenuButton_item != NULL) {
				if (Mute2MenuButton_item->data->OnClick()) {

					switch (Mute2MenuButton_item->data->GetType())
					{

					case MUTE:
						LOG("MUTE INGAME");
						MuteSettingsOFF();
						UnMuteSettingsON();
						bMuteSettingsOFF = true;
						bMuteSettingsON = false;

						
						

						break;

					}
				}
				Mute2MenuButton_item = Mute2MenuButton_item->next;
			}
		}
		else {
			p2List_item<UIitem_Button*>*UnMute2MenuButton_item = UnMuteSettings_Button.start;
			while (UnMute2MenuButton_item != NULL) {
				if (UnMute2MenuButton_item->data->OnClick()) {

					switch (UnMute2MenuButton_item->data->GetType())
					{

					case UNMUTE:
						LOG("UNMUTE INGAME");
						MuteSettingsON();
						UnMuteSettingsOFF();
						bMuteSettingsOFF = false;
						bMuteSettingsON = true;
						
						
						break;

					}
				}
				UnMute2MenuButton_item = UnMute2MenuButton_item->next;
			}
		}
	}

	//MUTE & UNMUTE INGAME
	if (OnIngameMenu == true) {
		if (bMuteIngameON == true) {
			p2List_item<UIitem_Button*>*MuteIngame2_item = MuteIngame_Button.start;
			while (MuteIngame2_item != NULL) {
				if (MuteIngame2_item->data->OnClick()) {

					switch (MuteIngame2_item->data->GetType())
					{

					case MUTE:
						LOG("MUTE INGAME");
						MuteIngameOFF();
						UnMuteIngameON();
						bMuteIngameOFF = true;
						bMuteIngameON = false;
						
						break;

					}
				}
				MuteIngame2_item = MuteIngame2_item->next;
			}
		}
		else {
			p2List_item<UIitem_Button*>*UnMuteIngame2_item = UnMuteIngame_Button.start;
			while (UnMuteIngame2_item != NULL) {
				if (UnMuteIngame2_item->data->OnClick()) {

					switch (UnMuteIngame2_item->data->GetType())
					{

					case UNMUTE:
						LOG("UNMUTE INGAME");
						MuteIngameON();
						UnMuteIngameOFF();
						bMuteIngameOFF = false;
						bMuteIngameON = true;
						
						
						break;

					}
				}
				UnMuteIngame2_item = UnMuteIngame2_item->next;
			}
		}
		
	}

	



	if (OnConsole == true) {
		p2List_item<UIitem_Button*>*Console_Buttons3 = Console_Button.start;
		while (Console_Buttons3 != NULL) {
			if (Console_Buttons3->data->OnClick()) {

				switch (Console_Buttons3->data->GetType())
				{

				case CONSOLE_NOCAP:
					LOG("CONSOLE FRAMES NOT CAPED");
					
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("FRAMES NOT CAPED");
					break;

				case CONSOLE_30CAP:
					LOG("CONSOLE FRAMES AT 30");
					
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("FRAMES CAPED AT 30");
					break;

				case CONSOLE_60CAP:
					LOG("CONSOLE FRAMES AT 60");
					
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("FRAMES CAPED AT 60");
					break;

				case CONSOLE_GOD:
					if (ConsoleSecurity == true) {
						ConsoleWarning->ChangeText("WARNING: This Will Break The Game,Restart Will Be Required, CONTINUE?");
						ConsoleSecurity = false;
					}
					else {
						LOG("CONSOLE 4"); //WILL BREAK THE GAME
						
						ConsoleSecurity = true;
						ConsoleLOGS("GOD MODE ACTIVE");
					}
					break;

				case CONSOLE_HPFULL:
					LOG("CONSOLE 5");
					HealthChanged = true;
					HealthBoosted = true;
					HealthFill = true;
					
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("HEALTH AT FULL");
					
					break;

				case CONSOLE_HPLESS:
					LOG("CONSOLE 6");
					HealthChanged = true;
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("HEALTH -1");
					break;

				case CONSOLE_HPMORE:
					LOG("CONSOLE 7");
					
					HealthBoosted = true;
					HealthChanged = true;
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("HEALTH +1");

					break;

				case CONSOLE_COLLECTLESS:
					LOG("CONSOLE 8");
					
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("COLLECT -1");
					break;

				case CONSOLE_COLLECTMORE:
					LOG("CONSOLE 9");
					
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("COLLECT`+1");
					break;

				case CONSOLE_KILL:
					LOG("CONSOLE 10");
					HealthChanged = true;
					Revive();
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("PLYER KILLED");
					break;

				case CONSOLE_MAP1://WILL BREAK THE GAME
					if (ConsoleSecurity == true) {
						ConsoleWarning->ChangeText("WARNING: This Will Break The Game,Restart Will Be Required, CONTINUE?");
						ConsoleSecurity = false;
					}
					else {

					
						LOG("CONSOLE 11");
						ConsoleSecurity = true;
						ConsoleLOGS("MAP 1 LOADED");
					}
					break;

				case CONSOLE_MAP2://WILL BREAK THE GAME
					if (ConsoleSecurity == true) {
						ConsoleWarning->ChangeText("WARNING: This Will Break The Game,Restart Will Be Required, CONTINUE?");
						ConsoleSecurity = false;
					}
					else {
						LOG("CONSOLE 12");
						
						ConsoleSecurity = true;
						ConsoleLOGS("MAP 2 LOADED");
					}
					break;

				case CONSOLE_NOVSYNC:
					
					LOG("CONSOLE 13");
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("VSYNC OFF");

					break;

				case CONSOLE_YESVSYNC:
					LOG("CONSOLE 14");
					
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("VSYNC ON");
					break;

				case CONSOLE_RESETENTITY:
					LOG("CONSOLE 15");
					ResetEntitiesPositionNewGame = true;
					ConsoleWarning->ChangeText("----------------------");
					ConsoleLOGS("ALL ENEMY ENTITIES RESET");

					break;

				}
			}
			Console_Buttons3 = Console_Buttons3->next;
		}
	}
	return true;
}

// Called each loop iteration
bool j1Scene_UI::PostUpdate()
{
	

	bool ret = true;

	

	return ret;
}

// Called before quitting
bool j1Scene_UI::CleanUp()
{
	

	LOG("Freeing Scene Menu");
	Buttons_Listed_Ingame.clear();
	App->gui->Disable();
	
	return true;
}

//void j1Scene_UI::IngameMenu()
//{
//	p2List_item<UIitem_Button*>* button_item = Buttons_Listed_Ingame.start;
//	while (button_item != NULL)
//	{
//		button_item->data->visible = !button_item->data->visible;
//		button_item = button_item->next;
//	}
//	p2List_item<UI_Item*>* ui_item = Menu_Listed_Ingame.start;
//	while (ui_item != NULL)
//	{
//		ui_item->data->visible = !ui_item->data->visible;
//		ui_item = ui_item->next;
//	}
//	
//}

//VISIBLE LISTS----------------------------------------------------------------------------------------------------------------------------------------------------------------
void j1Scene_UI::IngameMenuON()
{
	p2List_item<UIitem_Button*>* button_item = Buttons_Listed_Ingame.start;
	while (button_item != NULL)
	{
		button_item->data->visible = true;
		button_item = button_item->next;
	}
	p2List_item<UI_Item*>* ui_item = Menu_Listed_Ingame.start;
	while (ui_item != NULL)
	{
		ui_item->data->visible = true;
		ui_item = ui_item->next;
	}
}

void j1Scene_UI::IngameMenuOFF()
{
	p2List_item<UIitem_Button*>* button_item = Buttons_Listed_Ingame.start;
	while (button_item != NULL)
	{
		button_item->data->visible = false;
		button_item = button_item->next;
	}
	p2List_item<UI_Item*>* ui_item = Menu_Listed_Ingame.start;
	while (ui_item != NULL)
	{
		ui_item->data->visible = false;
		ui_item = ui_item->next;
	}
}

void j1Scene_UI::SettingsMenuOFF()
{
	
	p2List_item<UI_Item*>* SettingsUI_item1 = SettingsMenu_UI.start;
	while (SettingsUI_item1 != NULL)
	{
		SettingsUI_item1->data->visible = false;
		SettingsUI_item1 = SettingsUI_item1->next;
	}

	p2List_item<UIitem_Button*>* SettingsButton_item1 = SettingsMenu_Buttons.start;
	while (SettingsButton_item1 != NULL)
	{
		SettingsButton_item1->data->visible = false;
		SettingsButton_item1 = SettingsButton_item1->next;
	}
}

void j1Scene_UI::CreditsMenuON()
{
	p2List_item<UI_Item*>* Credits_UI2 = CreditsMenu_UI.start;
	while (Credits_UI2 != NULL)
	{
		Credits_UI2->data->visible = true;
		Credits_UI2 = Credits_UI2->next;
	}

	p2List_item<UIitem_Button*>* Credits_Button2 = CreditsMenu_Buttons.start;
	while (Credits_Button2 != NULL)
	{
		Credits_Button2->data->visible = true;
		Credits_Button2 = Credits_Button2->next;
	}
}


void j1Scene_UI::CreditsMenuOFF()
{
	p2List_item<UI_Item*>* Credits_UI = CreditsMenu_UI.start;
	while (Credits_UI != NULL)
	{
		Credits_UI->data->visible = false;
		Credits_UI = Credits_UI->next;
	}

	p2List_item<UIitem_Button*>* Credits_Button = CreditsMenu_Buttons.start;
	while (Credits_Button != NULL)
	{
		Credits_Button->data->visible = false;
		Credits_Button = Credits_Button->next;
	}
}

void j1Scene_UI::SettingsMenuON()
{
	
	p2List_item<UI_Item*>* SettingsUI_item1 = SettingsMenu_UI.start;
	while (SettingsUI_item1 != NULL)
	{
		SettingsUI_item1->data->visible = true;
		SettingsUI_item1 = SettingsUI_item1->next;
	}

	p2List_item<UIitem_Button*>* SettingsButton_item1 = SettingsMenu_Buttons.start;
	while (SettingsButton_item1 != NULL)
	{
		SettingsButton_item1->data->visible = true;
		SettingsButton_item1 = SettingsButton_item1->next;
	}
}

//void j1Scene_UI::IngamePlayerUI()
//{
//	p2List_item<UI_Item*>* PlayerUI_item = PlayerUI_Ingame.start;
//	while (PlayerUI_item != NULL)
//	{
//		PlayerUI_item->data->visible = !PlayerUI_item->data->visible;
//		PlayerUI_item = PlayerUI_item->next;
//	}
//}

//void j1Scene_UI::MainMenu()
//{
//
//	p2List_item<UIitem_Button*>* button_Menu = MainMenu_Buttons.start;
//	while (button_Menu != NULL)
//	{
//		button_Menu->data->visible = !button_Menu->data->visible;
//		button_Menu = button_Menu->next;
//	}
//	p2List_item<UI_Item*>* ui_Menu = MainMenu_UI.start;
//	while (ui_Menu != NULL)
//	{
//		ui_Menu->data->visible = !ui_Menu->data->visible;
//		ui_Menu = ui_Menu->next;
//	}
//
//}

void j1Scene_UI::IngamePlayerUIOFF()
{
	p2List_item<UI_Item*>* PlayerUI_item = PlayerUI_Ingame.start;
	while (PlayerUI_item != NULL)
	{
		PlayerUI_item->data->visible = false;
		PlayerUI_item = PlayerUI_item->next;
	}
}

void j1Scene_UI::IngamePlayerUION()
{
	p2List_item<UI_Item*>* PlayerUI_item = PlayerUI_Ingame.start;
	while (PlayerUI_item != NULL)
	{
		PlayerUI_item->data->visible = true;
		PlayerUI_item = PlayerUI_item->next;
	}
}

void j1Scene_UI::MainMenuOFF()
{
	p2List_item<UIitem_Button*>* button_Menu = MainMenu_Buttons.start;
	while (button_Menu != NULL)
	{
		button_Menu->data->visible = false;
		button_Menu = button_Menu->next;
	}
	p2List_item<UI_Item*>* ui_Menu = MainMenu_UI.start;
	while (ui_Menu != NULL)
	{
		ui_Menu->data->visible = false;
		ui_Menu = ui_Menu->next;
	}
}

void j1Scene_UI::MainMenuON()
{
	p2List_item<UIitem_Button*>* button_Menu2 = MainMenu_Buttons.start;
	while (button_Menu2 != NULL)
	{
		button_Menu2->data->visible = true;
		button_Menu2 = button_Menu2->next;
	}
	p2List_item<UI_Item*>* ui_Menu2 = MainMenu_UI.start;
	while (ui_Menu2 != NULL)
	{
		ui_Menu2->data->visible = true;
		ui_Menu2 = ui_Menu2->next;
	}
}

// MUTE & UNMUTE CHECKBOX
void j1Scene_UI::MuteSettingsON(){
	p2List_item<UIitem_Button*>* button_Menu2 = MuteSettings_Button.start;
	while (button_Menu2 != NULL)
	{
		button_Menu2->data->visible = true;
		button_Menu2 = button_Menu2->next;
	}
}
void j1Scene_UI::MuteSettingsOFF(){
	p2List_item<UIitem_Button*>* button_Menu2 = MuteSettings_Button.start;
	while (button_Menu2 != NULL)
	{
		button_Menu2->data->visible = false;
		button_Menu2 = button_Menu2->next;
	}
}
void j1Scene_UI::MuteIngameON(){
	p2List_item<UIitem_Button*>* button_Menu2 = MuteIngame_Button.start;
	while (button_Menu2 != NULL)
	{
		button_Menu2->data->visible = true;
		button_Menu2 = button_Menu2->next;
	}
}
void j1Scene_UI::MuteIngameOFF(){
	p2List_item<UIitem_Button*>* button_Menu2 = MuteIngame_Button.start;
	while (button_Menu2 != NULL)
	{
		button_Menu2->data->visible = false;
		button_Menu2 = button_Menu2->next;
	}
}
void j1Scene_UI::UnMuteSettingsON(){
	p2List_item<UIitem_Button*>* button_Menu2 = UnMuteSettings_Button.start;
	while (button_Menu2 != NULL)
	{
		button_Menu2->data->visible = true;
		button_Menu2 = button_Menu2->next;
	}
}
void j1Scene_UI::UnMuteSettingsOFF(){
	p2List_item<UIitem_Button*>* button_Menu2 = UnMuteSettings_Button.start;
	while (button_Menu2 != NULL)
	{
		button_Menu2->data->visible = false;
		button_Menu2 = button_Menu2->next;
	}
}
void j1Scene_UI::UnMuteIngameON(){
	p2List_item<UIitem_Button*>* button_Menu2 = UnMuteIngame_Button.start;
	while (button_Menu2 != NULL)
	{
		button_Menu2->data->visible = true;
		button_Menu2 = button_Menu2->next;
	}
}
void j1Scene_UI::UnMuteIngameOFF(){
	p2List_item<UIitem_Button*>* button_Menu2 = UnMuteIngame_Button.start;
	while (button_Menu2 != NULL)
	{
		button_Menu2->data->visible = false;
		button_Menu2 = button_Menu2->next;
	}
}

void j1Scene_UI::ConsoleON()
{
	p2List_item<UIitem_Button*>*  Listed_ConsoleButton =Console_Button.start;
	while (Listed_ConsoleButton != NULL)
	{
		Listed_ConsoleButton->data->visible = true;
		Listed_ConsoleButton = Listed_ConsoleButton->next;
	}
	p2List_item<UI_Item*>* Listed_ConsoleUI = Console_UI.start;
	while (Listed_ConsoleUI != NULL)
	{
		Listed_ConsoleUI->data->visible = true;

		Listed_ConsoleUI = Listed_ConsoleUI->next;
	}
}

void j1Scene_UI::ConsoleOFF()
{
	p2List_item<UIitem_Button*>*  Listed_ConsoleButton2 = Console_Button.start;
	while (Listed_ConsoleButton2 != NULL)
	{
		Listed_ConsoleButton2->data->visible = false;
		Listed_ConsoleButton2 = Listed_ConsoleButton2->next;
	}
	p2List_item<UI_Item*>* Listed_ConsoleUI2 = Console_UI.start;
	while (Listed_ConsoleUI2 != NULL)
	{
		Listed_ConsoleUI2->data->visible = false;

		Listed_ConsoleUI2 = Listed_ConsoleUI2->next;
	}
}

void j1Scene_UI::ConsoleManager()
{
}

void j1Scene_UI::Revive()
{
	LOG("Revive");
	LifeAt4 = true;
	LifeAt0 = false;
	LifeAt1 = false;
	LifeAt2 = false;
	LifeAt3 = false;
	
}

void j1Scene_UI::SliderManager()
{
	/*if (VolumeMusicBoxPos.x < 600 && (VolumeMusicBoxPos.y <  )) {
		MusicSliderBox->pos.x = VolumeMusicBoxPos.x - 20;
	}*/
}

char j1Scene_UI::ConsoleLOGS(const char * textLOG)
{

	if (OcupyConsoleLOG1 == true) { //FALSE OCUPIED
		ConsoleLOG1->ChangeText(textLOG);
		OcupyConsoleLOG1 = false;
	}
	else if (OcupyConsoleLOG2 == true) {
		ConsoleLOG2->ChangeText(textLOG);
		OcupyConsoleLOG2 = false;
	}
	else if (OcupyConsoleLOG3 == true) {
		ConsoleLOG3->ChangeText(textLOG);
		OcupyConsoleLOG3 = false;
	}
	else if (OcupyConsoleLOG4 == true) {
		ConsoleLOG4->ChangeText(textLOG);
		OcupyConsoleLOG4 = false;
	}
	else if (OcupyConsoleLOG5 == true) {
		ConsoleLOG5->ChangeText(textLOG);
		OcupyConsoleLOG5 = false;
	}
	else {
		OcupyConsoleLOG1 = false;
		OcupyConsoleLOG2 = true;
		OcupyConsoleLOG3 = true;
		OcupyConsoleLOG4 = true;
		OcupyConsoleLOG5 = true;
		ConsoleLOG1->ChangeText(textLOG);
		LOG("ALL 5 OCUPIED");
	}

	return true;
}





