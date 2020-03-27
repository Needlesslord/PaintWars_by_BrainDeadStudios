#ifndef _SCENE_UI__H
#define _SCENE_UI_H

#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "p2List.h"
#include "j1Gui.h"
#include "j1Button.h"
#include "j1SpriteUI.h"
#include "j1LabelUI.h"


class j1Scene_UI : public j1Module
{
public:

	j1Scene_UI();

	// Destructor
	virtual ~j1Scene_UI();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate(float dt);

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


	//void IngameMenu(); // OPEN AND CLOSE MENU WHEN INGAME
	//void IngamePlayerUI();
	void IngamePlayerUIOFF();
	void IngamePlayerUION();
	//void MainMenu(); //MAIN MENU SCREEN
	void MainMenuOFF();
	void MainMenuON();
	void IngameMenuON();
	void IngameMenuOFF();
	void SettingsMenuON();
	void SettingsMenuOFF();
	void CreditsMenuON();
	void CreditsMenuOFF();
	void MuteSettingsON();
	void MuteSettingsOFF();
	void MuteIngameON();
	void MuteIngameOFF();
	void UnMuteSettingsON();
	void UnMuteSettingsOFF();
	void UnMuteIngameON();
	void UnMuteIngameOFF();
	void ConsoleON();
	void ConsoleOFF();
	void ConsoleManager();
	void Revive();
	void SliderManager();
	//bool OnlyOnce;
	
	

public:

	char		player_score_string[5] = "0";
	char		timer_string[20] = "0";
	uint        player_lifes = 3;
	UI_Item*    lifes[4] = { nullptr,nullptr,nullptr,nullptr };
	UI_Item*    player_status[4] = { nullptr,nullptr,nullptr,nullptr };
	UI_Item*    Character_Back[1] = { nullptr};
	UI_Item*    Map_Icon[1] = { nullptr };
	UI_Label*	score_label = nullptr;
	UI_Label*	timer_label = nullptr;
	UI_Label*   ConsoleWarning = nullptr;
	
	bool LifeAt4;
	bool LifeAt3;
	bool LifeAt2;
	bool LifeAt1;
	bool LifeAt0;
	bool PlayerInvencibility;
	bool HealthChanged;
	bool HealthBoosted;
	bool HealthFill;



	p2List<UIitem_Button*>	Buttons_Listed_Ingame;
	p2List<UI_Item*>		Menu_Listed_Ingame; 
	p2List<UI_Item*>        PlayerUI_Ingame;
	p2List<UI_Item*>        MainMenu_UI;
	p2List<UIitem_Button*>  MainMenu_Buttons;
	p2List<UI_Item*>        SettingsMenu_UI;
	p2List<UIitem_Button*>  SettingsMenu_Buttons;
	p2List<UI_Item*>        CreditsMenu_UI;
	p2List<UIitem_Button*>  CreditsMenu_Buttons;

	p2List<UIitem_Button*> MuteSettings_Button;
	p2List<UIitem_Button*> UnMuteSettings_Button;
	p2List<UIitem_Button*> MuteIngame_Button;
	p2List<UIitem_Button*> UnMuteIngame_Button;

	p2List<UIitem_Button*> Console_Button;
	p2List<UI_Item*>       Console_UI;

	bool OnConsole;

	bool Menu_Music;
	p2SString				Music_Menu_Load;
	
	bool OnMainMenu;
	bool OnIngameMenu;
	bool OnIngameUI;
	bool OnSettingsMenu;
	bool OnCreditsMenu;

	bool bMuteSettingsON;
	bool bMuteSettingsOFF;
	bool bMuteIngameON;
	bool bMuteIngameOFF;

	bool ConsoleSecurity;
	bool OcupyConsoleLOG1;
	bool OcupyConsoleLOG2;
	bool OcupyConsoleLOG3;
	bool OcupyConsoleLOG4;
	bool OcupyConsoleLOG5;

	UI_Label*  ConsoleLOG1;
	UI_Label*  ConsoleLOG2;
	UI_Label*  ConsoleLOG3;
	UI_Label*  ConsoleLOG4;
	UI_Label*  ConsoleLOG5;

	iPoint VolumeMusicBoxPos;
	iPoint VolumeFXBoxPos;
	UIitem_Button* MusicSliderBox;
	UIitem_Button* FXSliderBox;

	
	char ConsoleLOGS(const char* textLOG);

	bool ResetEntitiesPositionNewGame;

	
private:
	p2SString			path;
	p2List<j1Module*>	current_level;
	j1PerfTimer			ptimer;
};

#endif // !_SCENE_UI_H