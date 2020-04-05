#include "j1Minimap.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Map.h"

#include "p2Log.h"
#include <list>

j1Minimap::j1Minimap()
{
	name = "minimap";
}

j1Minimap::~j1Minimap() {}

bool j1Minimap::Awake(pugi::xml_node & config)
{
	size = config.attribute("size").as_int(1);
	position.x = config.attribute("position.x").as_int(50);
	position.y = config.attribute("position.y").as_int(50);

	return true;
}

bool j1Minimap::Start()
{
	display = true;
	Load();

	return true;
}


bool j1Minimap::Update(float dt)
{
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		int map_x, map_y;

		if (MinimapCoords(map_x, map_y))
		{
			App->render->camera.x = -map_x + App->win->width / 2;
			App->render->camera.y = -map_y + App->win->height / 2;
		}
	}

	return true;
}

bool j1Minimap::PostUpdate()
{
	if (display) {
		App->render->AddBlitEvent(3, minimap_tex, position.x, position.y, rect);

		MinimapBorders();
		DrawCamera();
	}

	return true;
}

bool j1Minimap::CleanUp()
{
	SDL_DestroyTexture(minimap_tex);

	return true;
}

void j1Minimap::Load() {
	if (App->map->active)
	{

		minimap_scale = (float)size / (float)App->map->data.tile_height;


		float map_width = App->map->data.width * App->map->data.tile_width;
		minimap_width = map_width * minimap_scale;
		float map_height = App->map->data.height * App->map->data.tile_height;
		minimap_height = map_height * minimap_scale;

		minimap_tex = SDL_CreateTexture(App->render->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, minimap_width, minimap_height);
		SDL_SetRenderTarget(App->render->renderer, minimap_tex);
	}
	DrawMinimap();

	SDL_SetRenderTarget(App->render->renderer, NULL);
	SDL_SetTextureBlendMode(minimap_tex, SDL_BLENDMODE_BLEND);
}

bool j1Minimap::MinimapCoords(int& map_x, int& map_y)
{
	float mouse_x, mouse_y;
	App->input->GetMousePosition(mouse_x, mouse_y);

	//if we click inside the minimap
	if (mouse_x >= position.x && mouse_x <= minimap_width + position.x	&&	mouse_y >= position.y && mouse_y <= minimap_height + position.y)
	{
		if (App->map->data.type == MAPTYPE_ISOMETRIC) {
			map_x = ((mouse_x - position.x - minimap_width / 2) / minimap_scale);
			map_y = ((mouse_y - position.y) / minimap_scale);
		}
	}

	else
		return false;

	return true;
}

void j1Minimap::DrawMinimap()
{

	std::list<MapLayer*>::iterator  item = App->map->data.layers.begin();

	for (; item != App->map->data.layers.end(); item++)
	{
		MapLayer* layer = (*item);
		if (layer->properties.Get("Nodraw") != 0)
			continue;

		for (int y = 0; y < App->map->data.height; ++y)
		{
			for (int x = 0; x < App->map->data.width; ++x)
			{
				int tile_id = layer->Get(x, y);
				if (tile_id > 0)
				{
					TileSet* tileset = App->map->GetTilesetFromTileId(tile_id);

					SDL_Rect r = tileset->GetTileRect(tile_id);
					fPoint pos = App->map->MapToWorld(x, y);

					pos.x *= minimap_scale;
					pos.y *= minimap_scale;

					App->render->AddBlitEvent(4, tileset->texture, pos.x, pos.y, r);

				}
			}
		}
	}
}

void j1Minimap::DrawCamera()
{

	if (App->map->data.type == MAPTYPE_ISOMETRIC) {
		SDL_Rect map_camera = { -App->render->camera.x * minimap_scale + minimap_width / 2 + position.x,-App->render->camera.y * minimap_scale + position.y,App->render->camera.w * minimap_scale,App->render->camera.h * minimap_scale };
		App->render->DrawQuad(map_camera, 255, 255, 0, 255, false, false);
	}
}

void j1Minimap::MinimapBorders()
{
	int isotile_x_offset = App->map->data.tile_width / 2 * minimap_scale;
	int isotile_y_offset = App->map->data.tile_height / 2 * minimap_scale;

	if (App->map->data.type == MAPTYPE_ISOMETRIC) {
		App->render->DrawLine(isotile_x_offset + position.x, minimap_height / 2 + position.y + isotile_y_offset, minimap_width / 2 + isotile_x_offset + position.x, isotile_y_offset + position.y, 255, 255, 255, 255, false);
		App->render->DrawLine(minimap_width + isotile_x_offset + position.x, minimap_height / 2 + isotile_y_offset + position.y, minimap_width / 2 + isotile_x_offset + position.x, isotile_y_offset + position.y, 255, 255, 255, 255, false);
		App->render->DrawLine(minimap_width + isotile_x_offset + position.x, minimap_height / 2 + isotile_y_offset + position.y, minimap_width / 2 + isotile_x_offset + position.x, minimap_height + isotile_y_offset + position.y, 255, 255, 255, 255, false);
		App->render->DrawLine(isotile_x_offset + position.x, minimap_height / 2 + isotile_y_offset + position.y, minimap_width / 2 + isotile_x_offset + position.x, minimap_height + isotile_y_offset + position.y, 255, 255, 255, 255, false);
	}

}

void j1Minimap::Scale() {
	if (size < (App->map->data.tile_height / 2)) {
		size += 1;
		CleanUp();
		Load();
	}
}

void j1Minimap::Descale() {
	if (size > 1) {
		size -= 1;
		CleanUp();
		Load();
	}
}