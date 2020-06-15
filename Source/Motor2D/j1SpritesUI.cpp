#include "j1UIElements.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1UI_Manager.h"
#include"j1SpritesUI.h"


j1UISprites::j1UISprites() {

	this->type = TypeOfUI::GUI_IMAGE;
}

j1UISprites::~j1UISprites() {

}

bool j1UISprites::Start()
{

	switch (textureType) {
	case TEXTURE::MAIN_IMAGE:

		if (App->tex->Sprites_UI_Texture_General_Sprites == nullptr)
			App->tex->Sprites_UI_Texture_General_Sprites = App->gui->Get_Texture_From_Image(TEXTURE::MAIN_IMAGE);

		break;

	case TEXTURE::LOGO_SPRITE:

		if (App->tex->Sprites_UI_Texture_LogoImage_LOGO_SCENE == nullptr)
			App->tex->Sprites_UI_Texture_LogoImage_LOGO_SCENE = App->gui->Get_Texture_From_Image(TEXTURE::LOGO_SPRITE);

		break;

	case TEXTURE::ATLAS_SPRITE:

		if (App->tex->Sprites_UI_Texture_General_ATLAS == nullptr)
			App->tex->Sprites_UI_Texture_General_ATLAS = App->gui->Get_Texture_From_Image(TEXTURE::ATLAS_SPRITE);

		break;

	case TEXTURE::MINIMAP_ENTITIES:

		if (App->tex->Sprites_UI_Texture_General_ATLAS == nullptr)
			App->tex->Sprites_UI_Texture_General_ATLAS = App->gui->Get_Texture_From_Image(TEXTURE::MINIMAP_ENTITIES);

		break;

	case TEXTURE::MINIMAP_BACK_SPRITE:

		if (App->tex->Sprites_UI_Texture_Minimap_FULL_SCALE_BACK == nullptr)

			App->tex->Sprites_UI_Texture_Minimap_FULL_SCALE_BACK = App->gui->Get_Texture_From_Image(TEXTURE::MINIMAP_BACK_SPRITE);

		break;

	case TEXTURE::MINIMAP_CAMERA_SPRITE:

		if (App->tex->Sprites_UI_Texture_Minimap_CAMERA_FOLLOW == nullptr)
			App->tex->Sprites_UI_Texture_Minimap_CAMERA_FOLLOW = App->gui->Get_Texture_From_Image(TEXTURE::MINIMAP_CAMERA_SPRITE);

		break;

	case TEXTURE::LOSE_SCREEN_SPRITE:

		if (App->tex->Sprites_UI_Texture_Letters_LOSE_SCENE == nullptr)
			App->tex->Sprites_UI_Texture_Letters_LOSE_SCENE = App->gui->Get_Texture_From_Image(TEXTURE::LOSE_SCREEN_SPRITE);

		break;

	case TEXTURE::WIN_SCREEN_SPRITE:

		if (App->tex->Sprites_UI_Texture_Letters_WIN_SCENE == nullptr)
			App->tex->Sprites_UI_Texture_Letters_WIN_SCENE = App->gui->Get_Texture_From_Image(TEXTURE::WIN_SCREEN_SPRITE);

		break;

	case TEXTURE::BACKGROUND_FOREST:

		if (App->tex->Sprites_UI_Texture_Background_Forest == nullptr)
			App->tex->Sprites_UI_Texture_Background_Forest = App->gui->Get_Texture_From_Image(TEXTURE::BACKGROUND_FOREST);

		break;

	case TEXTURE::BACKGROUND_SNOW:

		if (App->tex->Sprites_UI_Texture_Background_Snow == nullptr)
			App->tex->Sprites_UI_Texture_Background_Snow = App->gui->Get_Texture_From_Image(TEXTURE::BACKGROUND_SNOW);

		break;

	case TEXTURE::BACKGROUND_VOLCANO:

		if (App->tex->Sprites_UI_Texture_Background_Volcano == nullptr)
			App->tex->Sprites_UI_Texture_Background_Volcano = App->gui->Get_Texture_From_Image(TEXTURE::BACKGROUND_VOLCANO);

		break;
	}

	return true;
}

bool j1UISprites::PreUpdate()
{

	return true;
}

bool j1UISprites::Update(float dt) {

	switch ((textureType))
	{
	case TEXTURE::MAIN_IMAGE:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_General_Sprites, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	case TEXTURE::LOGO_SPRITE:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_LogoImage_LOGO_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	case TEXTURE::ATLAS_SPRITE:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_General_ATLAS, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	case TEXTURE::MINIMAP_ENTITIES:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_General_ATLAS, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	case TEXTURE::MINIMAP_BACK_SPRITE:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_General_ATLAS, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	case TEXTURE::MINIMAP_CAMERA_SPRITE:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_Minimap_CAMERA_FOLLOW, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	case TEXTURE::LOSE_SCREEN_SPRITE:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_Letters_LOSE_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	case TEXTURE::WIN_SCREEN_SPRITE:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_Letters_WIN_SCENE, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	case TEXTURE::BACKGROUND_FOREST:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_Background_Forest, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	case TEXTURE::BACKGROUND_SNOW:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_Background_Snow, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	case TEXTURE::BACKGROUND_VOLCANO:

		App->render->RenderQueueUI(2, App->tex->Sprites_UI_Texture_Background_Volcano, map_position.x - App->render->camera.x, map_position.y - App->render->camera.y, rect, false, true, 0, 0, 0, 0, true);
		break;

	}

	return true;
}

bool j1UISprites::PostUpdate()
{


	return true;
}

bool j1UISprites::CleanUp() {


	if (App->tex->Sprites_UI_Texture_General_ATLAS != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_General_ATLAS);
		App->tex->Sprites_UI_Texture_General_ATLAS = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_General_Sprites != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_General_Sprites);
		App->tex->Sprites_UI_Texture_General_Sprites = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_Minimap_FULL_SCALE_BACK != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Minimap_FULL_SCALE_BACK);
		App->tex->Sprites_UI_Texture_Minimap_FULL_SCALE_BACK = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_Minimap_MINI_SCALE_forest != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Minimap_MINI_SCALE_forest);
		App->tex->Sprites_UI_Texture_Minimap_MINI_SCALE_forest = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_Minimap_MINI_SCALE_snow != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Minimap_MINI_SCALE_snow);
		App->tex->Sprites_UI_Texture_Minimap_MINI_SCALE_snow = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_Minimap_MINI_SCALE_volcano != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Minimap_MINI_SCALE_volcano);
		App->tex->Sprites_UI_Texture_Minimap_MINI_SCALE_volcano = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_Minimap_CAMERA_FOLLOW != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Minimap_CAMERA_FOLLOW);
		App->tex->Sprites_UI_Texture_Minimap_CAMERA_FOLLOW = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_Letters_WIN_SCENE != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Letters_WIN_SCENE);
		App->tex->Sprites_UI_Texture_Letters_WIN_SCENE = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_Letters_LOSE_SCENE != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Letters_LOSE_SCENE);
		App->tex->Sprites_UI_Texture_Letters_LOSE_SCENE = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_Letters_LOGO_SCENE != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Letters_LOGO_SCENE);
		App->tex->Sprites_UI_Texture_Letters_LOGO_SCENE = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_LogoImage_LOGO_SCENE != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_LogoImage_LOGO_SCENE);
		App->tex->Sprites_UI_Texture_LogoImage_LOGO_SCENE = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_ContinueLetters_WIN_LOSE_SCENE != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_ContinueLetters_WIN_LOSE_SCENE);
		App->tex->Sprites_UI_Texture_ContinueLetters_WIN_LOSE_SCENE = nullptr;
	}

	if (App->tex->Sprites_UI_Texture_Background_Forest != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Background_Forest);
		App->tex->Sprites_UI_Texture_Background_Forest = nullptr;
	}
	if (App->tex->Sprites_UI_Texture_Background_Snow != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Background_Snow);
		App->tex->Sprites_UI_Texture_Background_Snow = nullptr;
	}
	if (App->tex->Sprites_UI_Texture_Background_Volcano != nullptr) {
		App->tex->UnLoad(App->tex->Sprites_UI_Texture_Background_Volcano);
		App->tex->Sprites_UI_Texture_Background_Volcano = nullptr;
	}
	


	return true;
}