#include "p2Defs.h"
#include "p2Log.h"

#include "TownHall.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

TownHall::TownHall(fPoint pos, int damage, j1Module* listener) : Entity(pos, damage, listener, nullptr) {
	
	// Handle data and initialize the TH
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_TOWN_HALL;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_STATIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_VERY_BIG;
	maxLife = 100;
	this->currLife = maxLife - damage;
	this->pos = pos;
	size = { 100, 100 };
	isEntityFromPlayer = true;
	isSpawningAUnit = false;
	CreateEntityCollider(pos);
}

TownHall::~TownHall() {}

void TownHall::SpawnEntity() {

	bool canAffordIt = true;
	if (!canAffordIt)
		return;

	fPoint spawnWorldPosition = App->map->MapToWorld(pos.x, pos.y + size.y / 2);
	iPoint spawnMapPosition = App->map->WorldToMap(spawnWorldPosition.x, spawnWorldPosition.y);

	// Spawn warrior

	// First, we'll check there isn't a unit in the spawn position
	/*list<Entity*>::iterator uniitsIterator = App->entities->activeUnits.begin();
	while (uniitsIterator != App->entities->activeUnits.end()) {
		if()
		uniitsIterator++;
	}*/
	if (!isSpawningAUnit) {
		App->entities->AddEntity(ENTITY_TYPE_WARRIOR, { pos.x + size.x / 2 - 31, pos.y + size.y }, { 62, 118 }, App->entities, this, 0);
		isSpawningAUnit = true;
	}
}