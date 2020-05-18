#include "p2Defs.h"
#include "p2Log.h"

#include "TitaniumExtractor.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Pathfinding.h"
#include "j1Textures.h"
#include "j1EntityManager.h"

TitaniumExtractor::TitaniumExtractor(iPoint tile, int damage, j1Module* listener, Entity* creator) : Entity(tile, damage, listener, creator) {

	// Handle data and initialize the PE
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_TITANIUM_EXTRACTOR;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_STATIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_BIG; // But it changes 4 more tile around it

	maxLife = 400;
	
	currLife = maxLife - damage;

	size = { 150, 199 }; // TODO

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	constructionTime = 20.0f;

	extractionRate = 0.05f;

	isEntityFromPlayer = true;

	visibilityRadius = 3;
	fow_entity->frontier = App->fow->CreateSightQuad(visibilityRadius, fow_entity->position);
	fow_entity->LOS = App->fow->FulfillSight(fow_entity->frontier);

}

TitaniumExtractor::~TitaniumExtractor() {}

void TitaniumExtractor::ExtractTitanium(float dt) {

	App->player->titaniumCount.count += extractionRate * dt;
}
