#include "p2Defs.h"
#include "p2Log.h"

#include "Painter.h"

#include "j1Player.h"
#include "Scene.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

Painter::Painter(fPoint pos, int damage, j1Module* listener, Entity* creator) : Entity(pos, damage, listener, spawnedBy) {

	// Handle data and initialize the Painter
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_PAINTER;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_MINI;
	maxLife = 10;
	this->currLife = maxLife - damage;
	this->pos = pos;

	speed = 200;
	iPoint mapPos = App->map->WorldToMap(pos.x, pos.y);
	destination = mapPos;

	size = { 20, 20 };
	isEntityFromPlayer = true;
	CreateEntityCollider(pos);

	isActive = true; //FOR NOW


	for (std::vector<Animation>::iterator i = App->map->allAnimations.begin(); i != App->map->allAnimations.end(); i++)
	{
		/*if (this->type == (i)->type)
		{
			if ((i)->orientation == ORIENTATION::ORIENTATION_NORTH)
			{
				this->north = i->GetAnimation(); continue;
			}
			
		}*/
	}


}

Painter::~Painter() {}