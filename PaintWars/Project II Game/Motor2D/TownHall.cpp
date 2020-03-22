#include "p2Defs.h"
#include "p2Log.h"

#include "TownHall.h"

#include "j1Player.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

TownHall::TownHall(fPoint pos, int damage, j1Module* listener) : Entity(pos, damage, listener) {
	
	// Handle data and initialize the TH
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_TOWN_HALL;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_STATIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_VERY_BIG;
	maxLife = 100;
	this->currLife = maxLife - damage;
	this->pos = pos;
	size = { 100, 100 };
	isEntityFromPlayer = true;
	CreateEntityCollider(pos);
}

TownHall::~TownHall() {}