#include "j1GUIElements.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1GUI.h"


j1Image::j1Image() {

	this->type = GUItype::GUI_IMAGE;
}

j1Image::~j1Image() {

}

bool j1Image::Start()
{
	if (textureType == TEXTURE::IMAGE) 
		texture = App->gui->Load_Texture(TEXTURE::IMAGE);

	if (textureType == TEXTURE::MANAGER_IMAGE) 
		texture = App->gui->Load_Texture(TEXTURE::MANAGER_IMAGE);

	if (textureType == TEXTURE::MAIN_IMAGE)
		texture = App->gui->Load_Texture(TEXTURE::MAIN_IMAGE);

	if (textureType == TEXTURE::LOGO)
		texture = App->gui->Load_Texture(TEXTURE::LOGO);

	if (textureType == TEXTURE::ATLAS)
		texture = App->gui->Load_Texture(TEXTURE::ATLAS);

	if (textureType == TEXTURE::MINIMAP_BACK)
		texture = App->gui->Load_Texture(TEXTURE::MINIMAP_BACK);

	if (textureType == TEXTURE::MINIMAP_CAMERA)
		texture = App->gui->Load_Texture(TEXTURE::MINIMAP_CAMERA);

	if (textureType == TEXTURE::LOSE_SCREEN)
		texture = App->gui->Load_Texture(TEXTURE::LOSE_SCREEN);

	if (textureType == TEXTURE::WIN_SCREEN)
		texture = App->gui->Load_Texture(TEXTURE::WIN_SCREEN);

	

	return true;
}

bool j1Image::PreUpdate()
{

	return true;
}

bool j1Image::Update(float dt) {


	if (enabled) {
		if (textureType == TEXTURE::MAIN_IMAGE || textureType == TEXTURE::ATLAS||textureType==TEXTURE::MINIMAP_BACK||textureType==TEXTURE::MINIMAP_CAMERA||
			textureType==TEXTURE::LOSE_SCREEN || textureType == TEXTURE::WIN_SCREEN || textureType == TEXTURE::LOGO)


		App->render->RenderQueueUI(2, texture, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false,true, 0, 0, 0, 0, true);
		else
		App->render->RenderQueueUI(3, texture, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
	}



return true; 
}

bool j1Image::PostUpdate()
{
	if (enabled)
		Draw();

	return true;
}

bool j1Image::CleanUp()
{
	App->tex->UnLoad(texture);
	return true;
}

