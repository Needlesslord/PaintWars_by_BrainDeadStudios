#include "p2Defs.h"
#include "p2Log.h"

#include "WoodProducer.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Pathfinding.h"
#include "j1Textures.h"
#include "j1EntityManager.h"

WoodProducer::WoodProducer(iPoint tile, int damage, j1Module* listener, Entity* creator) : Entity(tile, damage, listener, creator) {

	// Handle data and initialize the PE
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_WOOD_PRODUCER;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_STATIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_SMALL; // But it changes 4 more tile around it

	maxLife = 200;
	if (App->entities->woodProducersUpgraded)
		maxLife *= 1.5;
	
	currLife = maxLife - damage;

	size = { 150, 199 }; // TODO

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	constructionTime = 10.0f;

	uint visibilityRadius = 6;

	isEntityFromPlayer = true;

	fow_entity->frontier = App->fow->CreateSightQuad(visibilityRadius, fow_entity->position);
	fow_entity->LOS = App->fow->FulfillSight(fow_entity->frontier);

}

WoodProducer::~WoodProducer() {}
