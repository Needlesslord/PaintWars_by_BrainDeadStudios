#include "j1App.h"
#include "p2Log.h"
#include "j1Gui.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Thumb.h"
#include "j1BarUI.h"
#include "j1SpriteUI.h"
#include "j1Button.h"
#include "j1SceneUI.h"

UiItem_Bar::UiItem_Bar(SDL_Rect slider_box, UI_Item* parent) {
	s_box = slider_box;

	thumb2 = App->gui->CreateThumb({ 375,466,38,34 }, this);
	thumb2->pos = { 435,125 };

	
}

bool UiItem_Bar::Start()
{
	return true;
}

bool UiItem_Bar::PostUpdate()
{
	bool ret = true;

	ret = App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &s_box);

	return ret;
}

bool UiItem_Bar::Awake()
{
return false;
}

bool UiItem_Bar::Start2()
{

	return false;
}

float UiItem_Bar::GetThumbValue2()
{
	float ipos_bar1 = thumb1->thumb_box.x + (thumb1->thumb_box.w / 2);
	float fixed_pos1 = box.x + (thumb1->thumb_box.w / 2);
	float fpos_bar1 = box.x + box.w - (thumb1->thumb_box.w / 2);
	float final_pos1 = (ipos_bar1 - fixed_pos1) / (fpos_bar1 - fixed_pos1);

	return final_pos1;
}

float UiItem_Bar::GetThumbValue()
{
	float ipos_bar2 = thumb1->thumb_box.x + (thumb1->thumb_box.w / 2);
	float fixed_pos2 = box.x + (thumb1->thumb_box.w / 2);
	float fpos_bar2 = box.x + box.w - (thumb1->thumb_box.w / 2);
	float final_pos2 = (ipos_bar2 - fixed_pos2) / (fpos_bar2 - fixed_pos2);

	return final_pos2;
}
