#include "p2Log.h"
#include "j1SpriteUI.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Gui.h"
#include "j1ElementUI.h"
#include "j1App.h"

#include "Brofiler/Brofiler.h"

UI_Sprite::UI_Sprite(SDL_Rect rect, UI_Item* parent)
{
	sprite_rect = rect;
	this->parent = parent;
}



bool UI_Sprite::PostUpdate()
{
	BROFILER_CATEGORY("UI Sprite PostUpdate();", Profiler::Color::NavajoWhite)
	App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &sprite_rect);
	return true;
}
