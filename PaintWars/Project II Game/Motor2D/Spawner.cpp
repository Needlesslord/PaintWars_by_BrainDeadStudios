#include "p2Defs.h"
#include "p2Log.h"

#include "Spawner.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

Spawner::Spawner(iPoint tile, int damage, j1Module* listener) : Entity(tile, damage, listener, nullptr) {

	// Handle data and initialize the Spawner
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_SPAWNER;
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

	isEntityFromPlayer = false;

	CreateEntityCollider(pos);
}

Spawner::~Spawner() {}