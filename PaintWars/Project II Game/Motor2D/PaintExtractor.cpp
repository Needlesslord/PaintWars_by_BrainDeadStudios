#include "p2Defs.h"
#include "p2Log.h"

#include "PaintExtractor.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Pathfinding.h"
#include "j1Textures.h"

PaintExtractor::PaintExtractor(iPoint tile, int damage, j1Module* listener, Entity* creator) : Entity(tile, damage, listener, creator) {

	// Handle data and initialize the PE
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_PAINT_EXTRACTOR;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_STATIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_MEDIUM;

	maxLife = 100;
	currLife = maxLife - damage;

	size = { 250, 250 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	constructionTime = 10.0f;

	extractionRate = 50.0f;

	isEntityFromPlayer = true;
}

PaintExtractor::~PaintExtractor() {}

void PaintExtractor::ExtractPaint(float dt) {

	App->player->paintCount.count += extractionRate * dt;
}