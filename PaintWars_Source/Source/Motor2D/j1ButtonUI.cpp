#include "j1App.h"
#include "j1UIElements.h"
#include "j1ButtonUI.h"
#include "j1Input.h"
#include "j1UI_Manager.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "j1Audio.h"


j1ButtonUI::j1ButtonUI() {
	this->type = TypeOfUI::GUI_BUTTON;
}

j1ButtonUI::~j1ButtonUI() {

}

bool j1ButtonUI::Start()
{
	switch (textureType) {
	case TEXTURE::ATLAS:
		
		if (Button_UI_Texture_General_ATLAS == NULL) //Maybe nullptr
			Button_UI_Texture_General_ATLAS = App->gui->Get_Texture_From_Image(TEXTURE::ATLAS);
		break;

	case TEXTURE::MINIMAP_FULL_FOREST:
		
		if (Button_UI_Texture_Minimap_FULL_SCALE == NULL)
		Button_UI_Texture_Minimap_FULL_SCALE = App->gui->Get_Texture_From_Image(TEXTURE::MINIMAP_FULL_FOREST);
		break;

	case TEXTURE::MINIMAP_MINI_FOREST:
		
		if (Button_UI_Texture_Minimap_MINI_SCALE == NULL)
		Button_UI_Texture_Minimap_MINI_SCALE = App->gui->Get_Texture_From_Image(TEXTURE::MINIMAP_MINI_FOREST);
		break;

	case TEXTURE::MINIMAP_CAMERA:
	
		if (Button_UI_Texture_Minimap_CAMERA_FOLLOW == NULL)
		Button_UI_Texture_Minimap_CAMERA_FOLLOW = App->gui->Get_Texture_From_Image(TEXTURE::MINIMAP_CAMERA);
		break;

	case TEXTURE::CONTINUE_LETTERS:
		
		if (Button_UI_Texture_ContinueLetters_WIN_LOSE_SCENE == NULL)
		Button_UI_Texture_ContinueLetters_WIN_LOSE_SCENE = App->gui->Get_Texture_From_Image(TEXTURE::CONTINUE_LETTERS);
		break;

	case TEXTURE::LOSE_SCREEN:
		
		if (Button_UI_Texture_Letters_LOSE_SCENE == NULL)
		Button_UI_Texture_Letters_LOSE_SCENE = App->gui->Get_Texture_From_Image(TEXTURE::LOSE_SCREEN);
		break;

	case TEXTURE::WIN_SCREEN:
		
		if (Button_UI_Texture_Letters_WIN_SCENE == NULL)
		Button_UI_Texture_Letters_WIN_SCENE = App->gui->Get_Texture_From_Image(TEXTURE::WIN_SCREEN);
		break;

	case TEXTURE::LOGO:
		
		if (Button_UI_Texture_LogoImage_LOGO_SCENE == NULL)
		Button_UI_Texture_LogoImage_LOGO_SCENE = App->gui->Get_Texture_From_Image(TEXTURE::LOGO);
		break;

	case TEXTURE::LOGO_LETTERS:
		
		if (Button_UI_Texture_Letters_LOGO_SCENE == NULL)
		Button_UI_Texture_Letters_LOGO_SCENE = App->gui->Get_Texture_From_Image(TEXTURE::LOGO_LETTERS);
		break;

	case TEXTURE::TEAM_LOGO:

		if (Button_UI_Texture_TeamLogoImage_TEAM_LOGO_SCENE == NULL)
			Button_UI_Texture_TeamLogoImage_TEAM_LOGO_SCENE = App->gui->Get_Texture_From_Image(TEXTURE::TEAM_LOGO);
		break;
	}
	


	if (text != nullptr)
		label = App->gui->AddElement(TypeOfUI::GUI_LABEL, this, map_position, inside_position, true, true, { 0,0,0,0 }, text, nullptr, TEXTURE::NONE, fontType, layer+1);

	return true;
}

bool j1ButtonUI::PreUpdate()
{
	if (label != nullptr)
		label->enabled = enabled;

	above = MouseOnRect();

	return true;
}

bool j1ButtonUI::Update(float dt)
{


	if (enabled) {
		
	
		switch ((textureType))
		{

		case TEXTURE::ATLAS:
			if (above && interactable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {


				App->render->RenderQueueUI(layer, Button_UI_Texture_General_ATLAS, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, click_rect, false, true, 0u, 0u, 0u, 255, true);
				Mix_PlayChannel(-1, App->audio->Click_Button_Sound, 0);
				Mouse_On_Click();

			}
			else if (above && interactable) {
				App->render->RenderQueueUI(layer, Button_UI_Texture_General_ATLAS, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, hover_rect, false, true, 0u, 0u, 0u, 255, true);

			}
			else {
				App->render->RenderQueueUI(layer, Button_UI_Texture_General_ATLAS, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0u, 0u, 0u, 255, true);
			}
			break;

		
		case TEXTURE::MINIMAP_FULL_FOREST:
			if (above && interactable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {


				App->render->RenderQueueUI(layer, Button_UI_Texture_Minimap_FULL_SCALE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, click_rect, false, true, 0u, 0u, 0u, 255, true);
				
				Mix_PlayChannel(-1, App->audio->Click_Button_Sound, 0);
				Mouse_On_Click();
			}
			else if (above && interactable) {

				App->render->RenderQueueUI(layer, Button_UI_Texture_Minimap_FULL_SCALE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, hover_rect, false, true, 0u, 0u, 0u, 255, true);
			}
			else {
				App->render->RenderQueueUI(layer, Button_UI_Texture_Minimap_FULL_SCALE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0u, 0u, 0u, 255, true);
			}
			break;


		case TEXTURE::MINIMAP_MINI_FOREST:
			if (above && interactable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {


				App->render->RenderQueueUI(layer, Button_UI_Texture_Minimap_MINI_SCALE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, click_rect, false, true, 0u, 0u, 0u, 255, true);
				Mix_PlayChannel(-1, App->audio->Click_Button_Sound, 0);
				Mouse_On_Click();

			}
			else if (above && interactable) {
				App->render->RenderQueueUI(layer, Button_UI_Texture_Minimap_MINI_SCALE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, hover_rect, false, true, 0u, 0u, 0u, 255, true);

			}
			else {
				App->render->RenderQueueUI(layer, Button_UI_Texture_Minimap_MINI_SCALE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0u, 0u, 0u, 255, true);
			}
			break;


		case TEXTURE::MINIMAP_CAMERA:
			if (above && interactable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {


				App->render->RenderQueueUI(layer, Button_UI_Texture_Minimap_CAMERA_FOLLOW, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, click_rect, false, true, 0u, 0u, 0u, 255, true);
				Mix_PlayChannel(-1, App->audio->Click_Button_Sound, 0);
				Mouse_On_Click();

			}
			else if (above && interactable) {
				App->render->RenderQueueUI(layer, Button_UI_Texture_Minimap_CAMERA_FOLLOW, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, hover_rect, false, true, 0u, 0u, 0u, 255, true);

			}
			else {
				App->render->RenderQueueUI(layer, Button_UI_Texture_Minimap_CAMERA_FOLLOW, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0u, 0u, 0u, 255, true);
			}
			break;


		case TEXTURE::CONTINUE_LETTERS:
			if (above && interactable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {


				App->render->RenderQueueUI(layer, Button_UI_Texture_ContinueLetters_WIN_LOSE_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, click_rect, false, true, 0u, 0u, 0u, 255, true);
				Mix_PlayChannel(-1, App->audio->Click_Button_Sound, 0);
				Mouse_On_Click();

			}
			else if (above && interactable) {
				App->render->RenderQueueUI(layer, Button_UI_Texture_ContinueLetters_WIN_LOSE_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, hover_rect, false, true, 0u, 0u, 0u, 255, true);

			}
			else {
				App->render->RenderQueueUI(layer, Button_UI_Texture_ContinueLetters_WIN_LOSE_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0u, 0u, 0u, 255, true);
			}
			break;


		case TEXTURE::LOGO:
			if (above && interactable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {


				App->render->RenderQueueUI(layer, Button_UI_Texture_LogoImage_LOGO_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, click_rect, false, true, 0u, 0u, 0u, 255, true);

				Mix_PlayChannel(-1, App->audio->Click_Button_Sound, 0); //Click_Logo_Sound

				Mouse_On_Click();

			}
			else if (above && interactable) {
				App->render->RenderQueueUI(layer, Button_UI_Texture_LogoImage_LOGO_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, hover_rect, false, true, 0u, 0u, 0u, 255, true);

			}
			else {
				App->render->RenderQueueUI(layer, Button_UI_Texture_LogoImage_LOGO_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0u, 0u, 0u, 255, true);
			}
			break;


		case TEXTURE::TEAM_LOGO:
			if (above && interactable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {


				App->render->RenderQueueUI(layer, Button_UI_Texture_TeamLogoImage_TEAM_LOGO_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, click_rect, false, true, 0u, 0u, 0u, 255, true);

				Mix_PlayChannel(-1, App->audio->Click_Button_Sound, 0); //Click_Logo_Sound

				Mouse_On_Click();

			}
			else if (above && interactable) {
				App->render->RenderQueueUI(layer, Button_UI_Texture_TeamLogoImage_TEAM_LOGO_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, hover_rect, false, true, 0u, 0u, 0u, 255, true);

			}
			else {
				App->render->RenderQueueUI(layer, Button_UI_Texture_TeamLogoImage_TEAM_LOGO_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0u, 0u, 0u, 255, true);
			}
			break;

		}



	}
	
	return true;
}

bool j1ButtonUI::PostUpdate()
{


	return true;
}

bool j1ButtonUI::CleanUp()
{
	//IF SOMEONE ADDS A NEW TEXTURE FILE ADD IT HERE
	App->tex->UnLoad(Button_UI_Texture_General_ATLAS);
	App->tex->UnLoad(Button_UI_Texture_Minimap_FULL_SCALE);
	App->tex->UnLoad(Button_UI_Texture_Minimap_MINI_SCALE);
	App->tex->UnLoad(Button_UI_Texture_Minimap_CAMERA_FOLLOW);
	App->tex->UnLoad(Button_UI_Texture_Letters_WIN_SCENE);
	App->tex->UnLoad(Button_UI_Texture_Letters_LOSE_SCENE);
	App->tex->UnLoad(Button_UI_Texture_Letters_LOGO_SCENE);
	App->tex->UnLoad(Button_UI_Texture_LogoImage_LOGO_SCENE);
	App->tex->UnLoad(Button_UI_Texture_ContinueLetters_WIN_LOSE_SCENE);
	App->tex->UnLoad(Button_UI_Texture_TeamLogoImage_TEAM_LOGO_SCENE);


	Button_UI_Texture_General_ATLAS = nullptr;
	Button_UI_Texture_Minimap_FULL_SCALE = nullptr;
	Button_UI_Texture_Minimap_MINI_SCALE = nullptr;
	Button_UI_Texture_Minimap_CAMERA_FOLLOW = nullptr;
	Button_UI_Texture_Letters_WIN_SCENE = nullptr;
	Button_UI_Texture_Letters_LOSE_SCENE = nullptr;
	Button_UI_Texture_Letters_LOGO_SCENE = nullptr;
	Button_UI_Texture_LogoImage_LOGO_SCENE = nullptr;
	Button_UI_Texture_ContinueLetters_WIN_LOSE_SCENE = nullptr;
	Button_UI_Texture_TeamLogoImage_TEAM_LOGO_SCENE = nullptr;

	if (label != nullptr)
	label->CleanUp();
	
	return true;
}


















