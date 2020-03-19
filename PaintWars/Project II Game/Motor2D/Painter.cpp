#include "p2Defs.h"
#include "p2Log.h"

#include "Painter.h"

#include "j1Player.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

Painter::Painter(fPoint pos, int currLife, j1Module* listener) : Entity(pos, currLife, listener) {

	// Handle data and initialize the Painter
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_PAINTER;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_MINI;
	this->pos = pos;
	isEntityFromPlayer = true;
	CreateEntityCollider(pos);
}

Painter::~Painter() {}