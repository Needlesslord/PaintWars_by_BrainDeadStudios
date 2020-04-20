#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Input.h"
#include "Entity.h"
#include "j1EntityManager.h"
#include "j1Player.h"

// TODO: delete this
#include "j1Map.h"

#define VSYNC true

using namespace std;

j1Render::j1Render() : j1Module()
{
	name = ("renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

j1Render::~j1Render()
{}

bool j1Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;
	// load flags
	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if (config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(App->win->window, -1, flags);

	if (renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{

		camera.w = (App->win->screen_surface->w);
		camera.h = (App->win->screen_surface->h);
		UI_Render_Window_w = App->win->screen_surface->w * 6;
		UI_Render_Window_h = App->win->screen_surface->h * 6;
		camera.x = 0;
		camera.y = 0;
	}

	return ret;
}

bool j1Render::Start()
{
	LOG("render start");
	// back background
	SDL_RenderGetViewport(renderer, &viewport);
	return true;
}

bool j1Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool j1Render::Update(float dt)
{
	BlitEverythingOnList();
	return true;
}

bool j1Render::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	

	return true;
}

bool j1Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

bool j1Render::Load(pugi::xml_node& data)
{



	camera.x = data.child("camera").attribute("x").as_int();
	camera.y = data.child("camera").attribute("y").as_int();

	float x, y;
	int damage;
	iPoint size;
	const char* entityType;
	int numEntities = 3;
	numEntities = data.child("num_entities").attribute("value").as_int();



	//pugi::xml_node entities = save.child("entities").child("warrior");
	for (int i = 0; i < numEntities; i++) { //YOU CANT DO A FOR IN XML LIKE THIS, WE HAVE TO SEARCH EACH NODE WITH THE SAME NAME 


		//cycle_length = config.child("enemies").child("update_cycle_length").attribute("length").as_float(); //Fix pathfinding so it works with doLogic

		//frame_cap = config.child("app").attribute("framerate_cap").as_uint();
		//x = data.child("entity").attribute("position_x").as_float();
		x = data.child("active_entities").child("entity").attribute("postition_x").as_float();
		y = data.child("entity").attribute("position_y").as_float();
		damage = data.attribute("missing_hp").as_int();
		size.x = data.attribute("size_x").as_int();
		size.y = data.attribute("size_y").as_int();

		entityType = data.child("entity").attribute("entity_type").as_string("");

		if (entityType == "warrior") {
			iPoint mapPos = App->map->WorldToMap(x, y);
			App->entities->AddEntity(ENTITY_TYPE_WARRIOR, { mapPos.x, mapPos.y }, App->entities, nullptr, damage);
		}

		data = data.next_sibling();
	}

	return true;
}

bool j1Render::Save(pugi::xml_node& data) const
{

	//TO SAVE ANY KIND OF VALUE IN THE SAVE FILE YOU HAVE TO:

	//1. CREATE A NEW NODE WITH THE NAME THAT YOU WANT TO GIVE TO THAT NODE (ITS LIKE THE TITLE OF THE SECTION)  FOR EXAMPLE:
	//pugi::xml_node cam = data.append_child("camera");  "camera" being the title, cam being the name of the node,
	//just copy this and change camera name with what you want it to be called and the  node name

	//2. Save the value inside that 
	// to save a value you write ->  nodename.append_attribute("nameofthevalueinthesavefile")= name of the value in code

	pugi::xml_node cam = data.append_child("camera");
	cam.append_attribute("x") = camera.x;
	cam.append_attribute("y") = camera.y;

	//cam.append_attribute("current_scene")=
	pugi::xml_node numEntities = data.append_child("num_entities");
	numEntities.append_attribute("value") = App->entities->activeEntities.size();

	pugi::xml_node entities = data.append_child("active_entities");

	list<Entity*>::const_iterator entitiesToSave = App->entities->activeEntities.begin();
	while (entitiesToSave != App->entities->activeEntities.end()) {

		pugi::xml_node entity = entities.append_child("entity");

		if ((*entitiesToSave)->entityType == ENTITY_TYPE_WARRIOR) {
			const char warrior[] = "warrior";
			//entity.append_attribute("entity_type").as_string("warrior");
			entity.append_attribute("entity_type") = warrior;
			entity.append_attribute("position_x") = (*entitiesToSave)->pos.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->pos.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}


		entitiesToSave++;
	}



	return true;
}

void j1Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void j1Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}



fPoint j1Render::ScreenToWorld(float x, float y) const
{
	fPoint ret;
	float scale = App->win->GetScale();

	ret.x = (x - camera.x / scale);
	ret.y = (y - camera.y / scale);

	return ret;
}



////////////////////////////////////////////                        DISCLAIMER                         ////////////////////////////////////////////////////////////////////



//We are currently using a render system  that sets blit queues to be able to order blit drawing on screen that has been 
//Created by DOLIME CORPORATION (https://github.com/Sanmopre/DOLIME-CORP-PROJECT-II) / All code related to rendering queues belongs to them!
void j1Render::RenderQueue(int layer, SDL_Texture* texture, int x, int y, const SDL_Rect section, bool fliped, bool ui, float speed, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	const SDL_Rect* Point_Section = &section;


	//BlitEvent WantToBlit{ texture, x, y, section, fliped, ui, speed, r, g, b, a };

	//This uses culling to know if it has to be blited or not
	if (texture != nullptr)
	{
		if (x > (-camera.x / App->win->GetScale()) - 220 && x < ((-camera.x + camera.w) / App->win->GetScale()) + 100 && y >(-camera.y / App->win->GetScale()) - 150 && y < ((-camera.y + camera.h) / App->win->GetScale()) + 100) {

			//OrderToBlit.insert(make_pair(layer, WantToBlit));

			Blit(texture, x, y, Point_Section, fliped, ui, speed);
		}
	}
	else
	{
		if (section.x > (-camera.x / App->win->GetScale()) - 220 && section.x < (-camera.x + camera.w) / App->win->GetScale() && section.y >(-camera.y / App->win->GetScale()) - 150 && section.y < (-camera.y + camera.h) / App->win->GetScale()) {
			//OrderToBlit.insert(make_pair(layer, WantToBlit));
			Blit(texture, x, y, Point_Section, fliped, ui, speed);
		}
	}

}

void j1Render::RenderQueueUI(int layer, SDL_Texture* texture, int x, int y, const SDL_Rect section, bool fliped, bool ui, float speed, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	//No culling checked in UI because it moves with the camera
	//BlitEvent WantToBlitUI{ texture, x, y, section, fliped, ui, speed, r, g, b, a };
	const SDL_Rect* Point_Section = &section;

	Blit(texture, x, y, Point_Section, fliped, ui, speed);
	//OrderToBlit.insert(make_pair(layer, WantToBlitUI));

}

void j1Render::BlitEverythingOnList()
{
	for (auto BlitIterator = OrderToBlit.begin(); BlitIterator != OrderToBlit.end(); BlitIterator++)
	{
		SDL_Texture* Texture_Iterated = BlitIterator->second.texture;
		bool event_ui = BlitIterator->second.ui;

		if (Texture_Iterated != nullptr)
		{
			int event_x = BlitIterator->second.x;
			int event_y = BlitIterator->second.y;
			const SDL_Rect* event_rect = &BlitIterator->second.section;
			bool event_flip = BlitIterator->second.fliped;

			Blit(Texture_Iterated, event_x, event_y, event_rect, event_flip, event_ui);
		}
		else
		{
			const SDL_Rect& event_rect = BlitIterator->second.section;
			uint event_r = BlitIterator->second.r;
			uint event_g = BlitIterator->second.g;
			uint event_b = BlitIterator->second.b;
			uint event_a = BlitIterator->second.a;

			DrawQuad(event_rect, event_r, event_g, event_b, event_a, event_ui);
		}
	}
	if (OrderToBlit.size() != 0)
	{
		OrderToBlit.erase(OrderToBlit.begin(), OrderToBlit.end());
	}
}

bool j1Render::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, bool fliped, bool ui, float speed, double angle, int pivot_x, int pivot_y) const
{

	bool ret = true;
	float scale = App->win->GetScale();

	SDL_Rect rect;


	if (ui) {
		rect.x = (int)(camera.x * speed) + x;
		rect.y = (int)(camera.y * speed) + y;
	}
	else if (!ui) {
		rect.x = (int)(camera.x * speed) + x * scale;
		rect.y = (int)(camera.y * speed) + y * scale;

	}

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	if (!ui)
	{
		rect.w *= scale;
		rect.h *= scale;
	}

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if (pivot_x != INT_MAX && pivot_y != INT_MAX)
	{
		pivot.x = pivot_x;
		pivot.y = pivot_y;
		p = &pivot;
	}

	SDL_RendererFlip flip;
	if (!fliped)
		flip = SDL_FLIP_NONE;
	else
		flip = SDL_FLIP_HORIZONTAL;

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

//////////////////////////////////////////////                            DISCLAIMER                     ////////////////////////////////////////////////////////////////////


bool j1Render::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool ui, bool filled, bool use_camera, bool guiHitBox) const
{
	bool ret = true;
	float scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);

	if (!ui)
	{
		if (use_camera)
		{
			rec.x = (int)(camera.x + rect.x * scale);
			rec.y = (int)(camera.y + rect.y * scale);
			rec.w *= scale;
			rec.h *= scale;
		}
		else if (guiHitBox)
		{

			rec.x = (int)(rect.x * scale);
			rec.y = (int)(camera.y + rect.y * scale);
			rec.w *= scale;
			rec.h *= scale;

		}
	}
	else
	{
		if (use_camera)
		{
			rec.x = (int)(camera.x + rect.x);
			rec.y = (int)(camera.y + rect.y);
		}
		else if (guiHitBox)
		{

			rec.x = (int)(camera.x + rect.x);
			rec.y = (int)(camera.y + rect.y);

		}
	}


	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

