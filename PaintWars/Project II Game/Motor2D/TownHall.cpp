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

TownHall::TownHall(iPoint tile, int damage, j1Module* listener, Entity* creator) : Entity(tile, damage, listener, creator) {
	
	// Handle data and initialize the TH
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_TOWN_HALL;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_STATIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_VERY_BIG;

	maxLife = 100;
	currLife = maxLife - damage;

	size = { 100, 100 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	constructionTime = 10.0f;

	isEntityFromPlayer = true;

	isSpawningAUnit = false;
}

TownHall::~TownHall() {}

void TownHall::SpawnEntity(iPoint pos) {

	if (App->player->paintCount.count > 5 && App->player->housingSpace.count < App->player->housingSpace.maxCount) {
		App->player->paintCount.count -= 5;
		App->player->housingSpace.count++;
	}
	else
		return;

	// Spawn warrior

	// First, we'll check there isn't a unit in the spawn position
	/*list<Entity*>::iterator uniitsIterator = App->entities->activeUnits.begin();
	while (uniitsIterator != App->entities->activeUnits.end()) {
		if()
		uniitsIterator++;
	}*/

	// TODO: check this positions
	if (!isSpawningAUnit) {
		App->entities->AddEntity(ENTITY_TYPE_WARRIOR, { currentTile.x + 2, currentTile.y + 2 }, App->entities, this, 0);
		isSpawningAUnit = true;
	}
}