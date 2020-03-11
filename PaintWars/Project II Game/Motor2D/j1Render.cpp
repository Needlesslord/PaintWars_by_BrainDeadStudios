#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Input.h"

#define VSYNC true

using namespace std;

j1Render::j1Render() : j1Module()
{
	name.create("renderer");
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

	if(config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(App->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		camera.w = App->win->screen_surface->w;
		camera.h = App->win->screen_surface->h;
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
	BlitAll();
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

	return true;
}

bool j1Render::Save(pugi::xml_node& data) const
{
	pugi::xml_node cam = data.append_child("camera");

	cam.append_attribute("x") = camera.x;
	cam.append_attribute("y") = camera.y;

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

void j1Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

iPoint j1Render::ScreenToWorld(int x, int y) const
{
	iPoint ret;
	float scale = App->win->GetScale();

	ret.x = (x - camera.x / scale);
	ret.y = (y - camera.y / scale);

	return ret;
}

void j1Render::AddBlitEvent(int layer, SDL_Texture* texture, int x, int y, const SDL_Rect section, bool fliped, bool ui, float speed, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	BlitEvent event{ texture, x, y, section, fliped, ui, speed, r, g, b, a };

	if (texture != nullptr) //differentiate texture blits from quad draws
	{
		if (x > (-camera.x / App->win->GetScale()) - 100 && x < ((-camera.x + camera.w) / App->win->GetScale()) + 100 &&
			y >(-camera.y / App->win->GetScale()) - 100 && y < ((-camera.y + camera.h) / App->win->GetScale()) + 100)
			blit_queue.insert(make_pair(layer, event));
	}
	else
	{
		if (section.x > (-camera.x / App->win->GetScale()) - 100 && section.x < (-camera.x + camera.w) / App->win->GetScale() &&
			section.y >(-camera.y / App->win->GetScale()) - 100 && section.y < (-camera.y + camera.h) / App->win->GetScale())
			blit_queue.insert(make_pair(layer, event));
	}
}

void j1Render::BlitAll()
{
	for (auto e = blit_queue.begin(); e != blit_queue.end(); e++)
	{
		SDL_Texture* event_texture = e->second.texture;
		bool event_ui = e->second.ui;

		if (event_texture != nullptr)//differentiate texture blits from quad draws
		{
			int event_x = e->second.x;
			int event_y = e->second.y;
			const SDL_Rect* event_rect = &e->second.section;
			bool event_flip = e->second.fliped;
			float event_speed = e->second.speed;
			if (event_x > (-camera.x / App->win->GetScale()) - 200 && 
				event_x < (-camera.x + camera.w) / App->win->GetScale() &&
				event_y >(-camera.y / App->win->GetScale()) - 200 && 
				event_y < (-camera.y + camera.h) / App->win->GetScale())
				Blit(event_texture, event_x, event_y, event_rect, event_flip, event_ui, event_speed);
		}
		else
		{
			const SDL_Rect& event_rect = e->second.section;
			uint event_r = e->second.r;
			uint event_g = e->second.g;
			uint event_b = e->second.b;
			uint event_a = e->second.a;
			DrawQuad(event_rect, event_r, event_g, event_b, event_a, event_ui);
		}
	}
	if(blit_queue.size() != 0)
		blit_queue.erase(blit_queue.begin(), blit_queue.end());
}

bool j1Render::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, bool fliped, bool ui, float speed, double angle, int pivot_x, int pivot_y) const
{
	bool ret = true;
	float scale = App->win->GetScale();

	SDL_Rect rect;
	if (!ui)
	{
		rect.x = (int)(camera.x * speed) + x * scale;
		rect.y = (int)(camera.y * speed) + y * scale;
	}
	else
	{
		rect.x = (int)(camera.x * speed) + x;
		rect.y = (int)(camera.y * speed) + y;
	}

	if(section != NULL)
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

	if(pivot_x != INT_MAX && pivot_y != INT_MAX)
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

			rec.x = (int)(rect.x);
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

bool j1Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	float scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;

	if(use_camera)
		result = SDL_RenderDrawLine(renderer, camera.x + x1 * scale, camera.y + y1 * scale, camera.x + x2 * scale, camera.y + y2 * scale);
	else
		result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	float scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for(uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor));
		points[i].y = (int)(y + radius * sin(i * factor));
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}