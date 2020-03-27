#include "j1App.h"
#include "p2Log.h"
#include "p2Point.h"
#include "j1Gui.h"
#include "j1Window.h"
#include "j1SceneUI.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1BarUI.h"
#include "j1Thumb.h"
#include "j1Audio.h"
#include "j1ElementUI.h"



UiItem_Thumb::UiItem_Thumb(SDL_Rect s_thumb, UI_Item* parent)
{
	thumb_box = s_thumb;	
	this->parent = parent;

}

bool UiItem_Thumb::Start()
{

	return true;
}


bool UiItem_Thumb::PostUpdate()
{
	bool ret = true;

	ret = App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &thumb_box);

	
	return ret;
}


bool UiItem_Thumb::OnHover()
{
	return true;

}
