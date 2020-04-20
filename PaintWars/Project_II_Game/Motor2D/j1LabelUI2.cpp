#include "j1LabelUI.h"
#include "j1ElementUI.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Defs.h"
#include "Brofiler\Brofiler.h"

UI_Label::UI_Label(const char* text, Label_Type type, SDL_Color color, UI_Item* parent)
{
	label_text = text;
	label_type = type;
	label_color = color;

	this->parent = parent;
}

UI_Label::~UI_Label()
{
	if (tex != nullptr)
	{
		App->tex->UnLoad(tex);
		tex = nullptr;
	}
}


bool UI_Label::Start()
{
	ChangeTexture(label_color);
	return true;
}

bool UI_Label::PostUpdate()
{
	App->render->Blit(tex, position.x, position.y);

	switch (state)
	{
	case IDLE:
		ChangeTexture({ 0,0,0,0 });
		break;
	case HOVER:
		if (label_type != FONT && label_type != TITLE && label_type != CREDITS) {
			ChangeTexture({ 230,214,144,255 });
		}
		break;

	case CLICK:
		break;
	}

	return true;
}

bool UI_Label::OnHover()
{
	uint w, h;
	App->tex->GetSize(tex, w, h);
	bool ret = false;
	if (parent != nullptr)
	{
		ret = parent->OnHover();
	}
	return ((position.x < mouse_position.x && position.y < mouse_position.y && position.x + (int)w > mouse_position.x && position.y + (int)h > mouse_position.y) || ret);
}

void UI_Label::ChangeTexture(SDL_Color color)
{
	if (tex != nullptr)
	{
		App->tex->UnLoad(tex);
		tex = nullptr;
	}


	label_color = color;

	switch (label_type) {
	case TITLE:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->Button_Title); //TITLE BLOOD JUNGLE FONT
		break;
	case FONT:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->title_settings); //CHOCOLATE
		break;
	case CONFIG:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->title_config);
		break;
	case CREDITS:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->credits);
		break;
	case BUTTON:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->Button_Title);
		break;

	case MAIN_TITLE:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->MainTitle); //TITLE BLOOD JUNGLE FONT
		break;

	case TEXT:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->Regular_Text); //TITLE BLOOD JUNGLE FONT
		break;

	case TEXT_SMALL:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->Regular_Text_Small); //TITLE BLOOD JUNGLE FONT
		break;

	case CONSOLE:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->Console_Font); //TITLE BLOOD JUNGLE FONT
		break;

	case SLIDERS_FONTS:

		tex = App->font->Print(label_text.GetString(), label_color, App->font->SliderFont); //TITLE BLOOD JUNGLE FONT
		break;
	}
}

void UI_Label::ChangeText(const char * text)
{
	if (tex != nullptr)
	{
		App->tex->UnLoad(tex);
		tex = nullptr;
	}

	label_text.Clear();
	label_text.create(text);

	switch (label_type) {
	case TITLE:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->Button_Title);
		break;
	case FONT:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->MainTitle);
		break;
	case CONFIG:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->title_config);
		break;
	case CREDITS:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->credits);
		break;
	case BUTTON:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->title_buttons);
		break;

	case MAIN_TITLE:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->title_buttons);
		break;

	case TEXT:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->UI_Title);
		break;

	case TIME_MENU:
		tex = App->font->Print(label_text.GetString(), label_color, App->font->Timer_Ingame_Font);
		break;
	}
}