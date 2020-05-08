#include "p2Defs.h"
#include "p2Log.h"

#include "TownHall.h"
#include "SDL_mixer/include/SDL_mixer.h"
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
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_BIG;

	maxLife = 300;
	currLife = maxLife - damage;

	size = { 400, 403 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	constructionTime = 10.0f;

	isEntityFromPlayer = true;

	isSpawningAUnit = false;

	uint visibilityRadius = 8;

	fow_entity->frontier = App->fow->CreateSightQuad(visibilityRadius, fow_entity->position);
	fow_entity->LOS = App->fow->FulfillSight(fow_entity->frontier);

}

TownHall::~TownHall() {}

void TownHall::SpawnEntity() {

	// TODO: check this positions
	if (!isSpawningAUnit && App->player->paintCount.count > 5 && App->player->housingSpace.count < App->player->housingSpace.maxCount) {
		App->player->paintCount.count -= 5;
		App->player->housingSpace.count++;
		App->entities->AddEntity(ENTITY_TYPE_PAINTER, { currentTile.x + 1, currentTile.y + 1 }, App->entities, this, 0);
		Mix_PlayChannel(-1, App->audio->spawnFromHall, 0);
		isSpawningAUnit = true;
	}
	else
		return;
}