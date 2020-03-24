#include "Slime.h"

#include "j1Player.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

Slime::Slime(fPoint pos, int damage, j1Module* listener) : Entity(pos, damage, listener) {

	// Handle data and initialize the Warrior
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_SLIME;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_MINI;
	maxLife = 50;
	this->currLife = maxLife - damage;
	this->pos = pos;
	size = { 20, 20 };
	isEntityFromPlayer = false;
	CreateEntityCollider(pos);
}

Slime::~Slime() {}

//void Slime::Move(iPoint destination) {
//	iPoint posI;
//	posI.x = pos.x; posI.y = pos.y;
//	App->pathfinding->CreatePath(posI, destination);
//}