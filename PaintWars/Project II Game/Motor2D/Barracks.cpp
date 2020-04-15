#include "p2Defs.h"
#include "p2Log.h"

#include "Barracks.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

Barracks::Barracks(iPoint tile, int damage, j1Module* listener, Entity* creator) : Entity(tile, damage, listener, creator) {

	// Handle data and initialize the TH
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_BARRACKS;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_STATIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_MEDIUM;

	maxLife = 100;
	currLife = maxLife - damage;

	size = { 250,250 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	constructionTime = 10.0f;

	isEntityFromPlayer = true;

	isSpawningAUnit = false;
}

Barracks::~Barracks() {}

void Barracks::SpawnEntity(iPoint pos) {

	if (App->player->paintCount.count > 20 && App->player->housingSpace.count < App->player->housingSpace.maxCount) {
		App->player->paintCount.count -= 20;
		App->player->housingSpace.count++;
	}
	else
		return;

	// TODO: check this positions
	if (!isSpawningAUnit) {
		App->entities->AddEntity(ENTITY_TYPE_WARRIOR, { currentTile.x + 1, currentTile.y + 1 }, App->entities, this, 0);
		isSpawningAUnit = true;
	}
}