#include "p2Defs.h"
#include "p2Log.h"

#include "Warrior.h"

#include "j1Player.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"
#include "j1Render.h"

Warrior::Warrior(fPoint pos, int damage, j1Module* listener) : Entity(pos, damage, listener) {

	// Handle data and initialize the Warrior
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_WARRIOR;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_MINI;
	maxLife = 30;
	this->currLife = maxLife - damage;
	this->pos = pos;
	size = { 62, 118 };
	isEntityFromPlayer = true;
	CreateEntityCollider(pos);
}

Warrior::~Warrior() {}

void Warrior::Move(fPoint destination) {
	iPoint fPos;
	fPos.x = pos.x;
	fPos.y = pos.y;

	iPoint fDestination;
	fDestination.x = destination.x;
	fDestination.y = destination.y;

	//App->map->WorldToMap()
	App->pathfinding->CreatePath(fPos,fDestination);
}