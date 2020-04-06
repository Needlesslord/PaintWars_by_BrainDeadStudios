#include "p2Defs.h"
#include "p2Log.h"
#include <vector>

#include "Warrior.h"

#include "j1Player.h"
#include "j1SceneManager.h"
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
	*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;
	maxLife = 30;
	this->currLife = maxLife - damage;
	this->pos = pos;

	speed = 300;

	iPoint mapPos = App->map->WorldToMap(pos.x, pos.y);
	destination = mapPos;

	size = { 62, 118 };
	isEntityFromPlayer = true;
	CreateEntityCollider(pos);
}

Warrior::~Warrior() {}