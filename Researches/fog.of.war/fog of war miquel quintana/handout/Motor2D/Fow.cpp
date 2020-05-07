#include "Fow.h"
#include "j1App.h"
#include "j2EntityManager.h"
#include "j2Entity.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Textures.h"

Fow::Fow()
{
}

Fow::~Fow()
{
	//Delete all 2D Fog data containers
	if (visibility_map != nullptr && visibility_map != debug_map)
	{
		delete[] visibility_map;
		visibility_debug_holder = nullptr;
	}
	else if (visibility_debug_holder != nullptr)
		delete[] visibility_debug_holder;
	
	
	if (debug_map != nullptr)
		delete[] debug_map;
}

bool Fow::Awake()
{
	return true;
}

bool Fow::Start()
{
	fogtexture = App->tex->Load("maps/fow_texture.png");

	return true;
}

bool Fow::Update(float dt)
{
	if (debug == false)
	{
		// We manage fow_entities that manipulate the visibility map 
		ManageEntitiesFOWManipulation();
	}
	//Manage the entities visibibility, check if they are visible or not
	//depending on their position
	ManageEntitiesVisibility();

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		debug = !debug;

		// If we enter debug mode, our visibility map should be clear.
		// We will point to a clear visibility map (debug_map) so all calls depending on visibility_map don't
		// need further management. But before we store our current visibility map!
		if (debug == true)
		{
			//To keep the pointer to the visibility map we use our debug_holder;
			visibility_debug_holder = visibility_map;
			visibility_map = debug_map;
		}
		else // Debug == false
		{
			visibility_map = visibility_debug_holder;
		}
	}

	return true;
}

bool Fow::CleanUp()
{
	App->tex->UnLoad(fogtexture);
	fogtexture = nullptr;

	for (std::list<FOW_Entity*>::iterator item = fow_entities.begin(); item != fow_entities.end(); ++item)
	{
		if((*item)!=nullptr)
		delete (*item);
	}

	fow_entities.clear();
	return true;
}

//Create and add a FOW_entity to the list of fow_entities
FOW_Entity * Fow::CreateFOWEntity(iPoint position, bool gives_sight)
{
	FOW_Entity* ret = nullptr;

	ret = new FOW_Entity(position, gives_sight);

	if(ret != nullptr)
	fow_entities.push_back(ret);

	return ret;
}

//Delete and remove a FOW_entity to the list of fow_entities
bool Fow::DestroyFOWEntity(FOW_Entity* to_destroy)
{
	bool ret = false;

	for (std::list<FOW_Entity*>::iterator item = fow_entities.begin(); item != fow_entities.end(); ++item)
	{
		if (to_destroy == (*item))
		{
			delete (*item);
			fow_entities.remove(*item);
			ret = true;
			break;
		}
	}

	return ret;
}

//Set the visibility map
void Fow::SetVisibilityMap(uint w, uint h)
{
	if (visibility_map != nullptr)
	{
		if (visibility_debug_holder == visibility_map)
		{
			visibility_debug_holder = nullptr;
		}
		else
		{
			delete[] visibility_debug_holder;
			visibility_debug_holder = nullptr;
		}

		if (visibility_map != debug_map)
		{
			delete[] visibility_map;
			visibility_map = nullptr;
		}
	}

	if (debug_map != nullptr)
	{
		delete[] debug_map;
		debug_map = nullptr;
	}

	width = w;
	height = h;

	//Visibility map will contain the 3 basic states of logic in FOW
	visibility_map = new int8_t [width*height];
	memset(visibility_map, 0,width*height);

	// Keep a totally clear map for debug purposes
	debug_map = new int8_t[width*height];
	memset(debug_map, 255, width*height);
}

int8_t Fow::GetVisibilityTileAt(const iPoint& pos) const
{
	// Utility: return the visibility value of a tile
	if (CheckBoundaries(pos)) // Since both maps will have the same size we can check with the main one
			return visibility_map[(pos.y * width) + pos.x];
	else
		return 0;
}

SDL_Rect& Fow::GetFOWMetaRect(FOW_TileState state)
{
	SDL_Rect ret;
	ret.w = 64;
	ret.h = 64;
	//uint real_sprite_pos = uint(state) - (uint(FOW_TileState::UNVISITED)); // tile inside the FOWmeta spritesheet
	uint spritex = 0;
	if (state == FOW_TileState::FOGGED)
		spritex = 64;
	else if (state == FOW_TileState::UNVISITED)
		spritex = 128;
	else
		spritex = 128;
	// 64 is the width and height between different tiles in the spritesheet, thats done this way because it's the
	// total rect we use to print tiles from the tileset. The Map module should provide you that data but for this
	//Implementation you must not have calls to 
	ret.x = spritex;
	ret.y = 0;

	return ret;
}

void Fow::SetVisibilityTile(iPoint pos, FOW_TileState state)
{
	if (CheckBoundaries(pos))
			visibility_map[(pos.y * width) + pos.x] = (int8_t)state;
}

// We will manage the bool is_visible in the fow_entities, entities from the entity manager should check this value of
// their own fow_entity to determine if they're visible
void Fow::ManageEntitiesVisibility()
{
	for (std::list<FOW_Entity*>::iterator item = fow_entities.begin(); item != fow_entities.end(); ++item)
	{
		int8_t st = GetVisibilityTileAt((*item)->position);
		// If the tile isn't visible or a smoothing tile from black to Fogged
		if (st == (int8_t)FOW_TileState::VISIBLE)
		{
			(*item)->is_visible = true;
		} else {
			(*item)->is_visible = false;
		}
	}
}

void Fow::ManageEntitiesFOWManipulation()
{
	//Iterate all fow_entities
	for (std::list<FOW_Entity*>::iterator item = fow_entities.begin(); item != fow_entities.end(); ++item)
	{
		// If an entity provides visibility and has moved
		if ((*item)->provides_visibility == true && (*item)->moved_in_map == true)
		{
			//We store the LOS of the current entity, since the LOS will change this will be our previous LOS
			std::list<iPoint> prev_LOS = (*item)->LOS;

			//Since the Entity moved, we update the LOS position and make the tiles contained inside it visible 
			for (std::list<iPoint>::iterator tile = (*item)->LOS.begin(); tile != (*item)->LOS.end(); tile++)
			{
				// TODO 6: Whenever we move our providing sight entity, we need to update the LOS so the tiles of the LOS are updated with the range of the entity. 
				// We do this checking the amount of distance the entity has moved in tiles

				// TODO 7: Set the visibility of every tile we just moved to VISIBLE

			}

			(*item)->moved_in_map = false;
		
			// TODO 8: To finish, we now need to apply foggness to the tiles we left behind. We do this with SetVisibilityTile. 
			// We previously stored the tiles in prev_LOS. 
			// To ensure we take the tiles that are no longer in the LOS, we compare it with the prev_LOS, with the function TileInsideList
			for (std::list<iPoint>::const_iterator tile = prev_LOS.cbegin(); tile != prev_LOS.end(); tile++)
			{
				//compare it here
			}
		}
	}
}

bool Fow::TileInsideList(iPoint tile, const std::list<iPoint>& list_checked) const
{
	for (std::list<iPoint>::const_iterator item = list_checked.cbegin(); item != list_checked.end(); item++)
	{
		if ((*item).x == tile.x && (*item).y == tile.y)
		{
			return true;
		}
	}

	return false;
}

void Fow::ResetVisibilityMap()
{
	// We simply set the map again this way other modules can call and it will be
	// easier to understand rather than setting the the map again manually
	SetVisibilityMap(width,height);

	if (debug)
	{
		debug = false;
	}
}


bool Fow::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x < (int)width &&
		pos.y >= 0 && pos.y <= (int)height);
}

std::list<iPoint> Fow::CreateSightRect(uint w, uint h, iPoint center)
{
	std::list<iPoint> frontier_to_fill;

	iPoint start_pos = { 
		center.x - (int)(w/2),
		center.y - (int)(h / 2) };
	iPoint final_pos = { 
		start_pos.x + (int)w, 
		(int)start_pos.y + (int)h};

	// We iterate to find the iPoints that ARE part of the frontier
	for (int j = start_pos.y; j < final_pos.y; j++)
	{
		int i = start_pos.x;
		for (; i < final_pos.x - 1; i++) //check the explanations below to understand why i < w -1
		{
			// Since it's a rectangle some assumptions can be made: i== 0 will always be at the 
			// frontier as the left-most tile, i == w -1 will be for the right-most tile
			if (i == start_pos.x || j == start_pos.y || j == final_pos.y )
			{
				frontier_to_fill.push_back({ i, j });
			}
		}
		// We exit the for loop when i == w
		frontier_to_fill.push_back({ i, j });
	}
	
	return frontier_to_fill;
}

std::list<iPoint> Fow::CreateSightQuad(uint rad, iPoint center)
{
	return CreateSightRect(2*rad, 2*rad, center);
}

std::list<iPoint> Fow::FulfillSight(std::list<iPoint>& frontier)
{
	std::list<iPoint> ret;

	//Iterate the frontier
	for (std::list<iPoint>::const_iterator curr = frontier.cbegin(); curr != frontier.cend(); ++curr)
	{
		if ((*curr).y == (*std::next(curr)).y)
		{
			int w = (*std::next(curr)).x - (*curr).x;
			for (int i = 0; i < w; ++i)
			{
				ret.push_back({ (*curr).x + i ,(*curr).y });
			}
		}
		else
		{
			ret.push_back(*curr);
		}
	}

	return ret;
}

FOW_Entity::FOW_Entity(iPoint position, bool provides_visibility):
	position(App->map->WorldToMap(position.x, position.y)),
	provides_visibility(provides_visibility)
{}


void FOW_Entity::SetPos(iPoint new_pos)
{
	new_pos = App->map->WorldToMap(new_pos.x, new_pos.y);
	//world to map makes the tiles go with 
	if (position != new_pos)
	{
		moved_in_map = true;
		motion = { (new_pos.x - position.x), (new_pos.y - position.y) };
		position = new_pos;

	}
}
