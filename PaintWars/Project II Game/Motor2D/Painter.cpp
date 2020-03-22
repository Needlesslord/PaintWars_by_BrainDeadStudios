#include "p2Defs.h"
#include "p2Log.h"

#include "Painter.h"

#include "j1Player.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

Painter::Painter(fPoint pos, int damage, j1Module* listener) : Entity(pos, damage, listener) {

	// Handle data and initialize the Painter
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_PAINTER;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_MINI;
	maxLife = 10;
	this->currLife = maxLife - damage;
	this->pos = pos;
	size = { 20, 20 };
	isEntityFromPlayer = true;
	CreateEntityCollider(pos);
}

Painter::~Painter() {}

//void Painter::Move(iPoint destination) {
//	iPoint posI;
//	posI.x = pos.x; posI.y = pos.y;
//	App->pathfinding->CreatePath(posI, destination);
//}