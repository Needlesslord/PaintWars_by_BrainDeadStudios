#include "p2Defs.h"
#include "p2Log.h"

#include "Painter.h"

#include "j1Player.h"
#include "Scene.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"
#include "j1Timer.h"
#include "j1Render.h"

Painter::Painter(iPoint tile, int damage, j1Module* listener, Entity* creator) : Entity(tile, damage, listener, creator) {

	// Handle data and initialize the Painter
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_PAINTER;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_SMALL;
	*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;

	maxLife = 10;
	currLife = maxLife - damage;
	
	size = { 70, 150 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	speed = 200.0f;

	spawningTime = 10.0f;

	destination = currentTile;

	isEntityFromPlayer = true;

	extractionRate = 0.5f;

	if (App->entities->paintersUpgraded)
		extractionRate *= 1.33f;

	isBuildingSomething = false;

	visibilityRadius = 2;

	fow_entity->frontier = App->fow->CreateSightQuad(visibilityRadius, fow_entity->position);
	fow_entity->LOS = App->fow->FulfillSight(fow_entity->frontier);


}

Painter::~Painter() {}

void Painter::ExtractPaint(float dt) {

	if (App->pathfinding->IsPaintShore(currentTile) && currentTile == destination) {
		App->player->paintCount.count += extractionRate * dt;
	}
}

void Painter::ExtractWood(float dt) {
	

	if (App->pathfinding->IsWood(currentTile) && currentTile == destination) {
		//App->player->woodCount.count += 0.01;
		App->player->woodCount.count += extractionRate*dt;
	}
}

void Painter::Draw(SDL_Texture* sprites) {

	App->render->RenderQueue(1, sprites, pos.x, pos.y, currentAnimation->GetCurrentFrame());
}