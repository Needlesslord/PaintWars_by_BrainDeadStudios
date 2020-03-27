#include "p2Defs.h"
#include "p2Log.h"
#include "p2List.h"
#include "p2Point.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1ElementUI.h"
#include "j1LabelUI.h"
#include "j1BarUI.h"
#include "j1SpriteUI.h"
#include "j1Thumb.h"
#include "j1SceneUI.h"
#include "SDL/include/SDL.h"


j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");
	fx_button_pressed_string = conf.child("FX_Audios_UI").child_value();

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	
	atlas = App->tex->Load(atlas_file_name.GetString());
	fx_buton_pressed = App->audio->LoadFx(fx_button_pressed_string.GetString());

	p2List_item<UI_Item*>* item_gui = gui_list.start;
	
	while (item_gui != nullptr)
	{
		item_gui->data->Start();
		item_gui = item_gui->next;
	}

	return true;
}

// Update all guis
bool j1Gui::PreUpdate(float dt)
{
	
	p2List_item<UI_Item*>* item_gui = gui_list.start;
	while (item_gui != nullptr)
	{
		item_gui->data->PreUpdate(dt);
		item_gui = item_gui->next;
	}
	return true;
}

bool j1Gui::Update(float dt)
{
	
	p2List_item<UI_Item*>* item_gui = gui_list.start;
	while (item_gui != nullptr)
	{
		if (item_gui->data->visible)
			item_gui->data->Update(dt);
		item_gui = item_gui->next;
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	
	p2List_item<UI_Item*>* item_gui = gui_list.start;
	while (item_gui != nullptr)
	{
		if (item_gui->data->visible)
			item_gui->data->PostUpdate();
		if (item_gui->data->parent != nullptr)
			item_gui->data->visible = item_gui->data->parent->visible;
		item_gui = item_gui->next;
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	
	LOG("Freeing GUI");

	p2List_item<UI_Item*>* item;
	item = gui_list.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	gui_list.clear();

	if (atlas != nullptr)
	{
		App->tex->UnLoad(atlas);
		atlas = nullptr;
	}

	return true;
}


UI_Label* j1Gui::CreateLabel(iPoint pos, const char * text, Label_Type type, SDL_Color color, bool static_obj, UI_Item* parent)
{
	
	UI_Item* label = nullptr;
	label = new UI_Label(text, type, color, parent);
	label->pos.x = pos.x;
	label->pos.y = pos.y;

	label->static_object = static_obj;

	gui_list.add(label);

	return (UI_Label*)label;
}

UI_Item* j1Gui::CreateSprite(iPoint pos, SDL_Rect rect, bool static_obj, UI_Item* parent)
{
	
	UI_Item* sprite = nullptr;
	sprite = new UI_Sprite(rect, parent);
	sprite->pos.x = pos.x;
	sprite->pos.y = pos.y;

	sprite->static_object = static_obj;

	gui_list.add(sprite);

	return sprite;
}

UIitem_Button* j1Gui::CreateButton(iPoint pos, Button_Type type, SDL_Rect idle_rect, SDL_Rect* idle_hover, SDL_Rect* idle_click, const char* text, bool static_obj, UI_Item* parent)
{
	
	UI_Item* button = nullptr;
	button = new UIitem_Button(text, type, idle_rect, idle_hover, idle_click, parent);
	button->pos.x = pos.x;
	button->pos.y = pos.y;

	button->static_object = static_obj;

	gui_list.add(button);

	return (UIitem_Button*)button;
}
UiItem_Bar * j1Gui::CreateSlider(iPoint pos, SDL_Rect slider_box, bool static_obj, UI_Item* parent)
{
	
	UI_Item*slider = nullptr;
	slider = new UiItem_Bar(slider_box, parent);
	slider->pos.x = pos.x;
	slider->pos.y = pos.y;

	gui_list.add(slider);

	return (UiItem_Bar*)slider;
}


UiItem_Thumb * j1Gui::CreateThumb(SDL_Rect s_thumb, UI_Item * parent)
{
	UI_Item* thumb = nullptr;
	thumb = new UiItem_Thumb(s_thumb, parent);
	thumb->pos.x = parent->pos.x + 1;
	thumb->pos.y = parent->pos.y + 1;

	gui_list.add(thumb);

	return (UiItem_Thumb*)thumb;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	
	return atlas;
}

bool j1Gui::Load(pugi::xml_node &node)
{
	/*App->scene_ui->player_score = node.child("score").attribute("value").as_uint();
	sprintf_s(App->scene_ui->player_score_string, 5, "%1d", App->scene_ui->player_score);
	App->scene_ui->score_label->ChangeText(App->scene_ui->player_score_string);*/

	return true;
}

bool j1Gui::Save(pugi::xml_node &node) const
{
	/*pugi::xml_node score = node.append_child("score");

	score.append_attribute("value") = App->scene_ui->player_score;*/
	return true;
}