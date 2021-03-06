#include "Rider.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

Rider::Rider(iPoint tile, int damage, j1Module* listener) : Entity(tile, damage, listener, nullptr) {

	// Handle data and initialize the Warrior
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_RIDER;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_SMALL;

	maxLife = 150;
	currLife = maxLife - damage;

	size = { 20, 20 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	speed = 100;

	spawningTime = 1.0f;

	attackDamage = 13.0f;
	attackSpeed = 12.0f;
	attackCooldown = attackSpeed;



	destination = currentTile;

	isEntityFromPlayer = false;
}

Rider::~Rider() {}

void Rider::Attack(Entity* target, float dt) {

	if (attackCooldown >= attackSpeed) {

		target->ApplyDamage(attackDamage);
		attackCooldown = 0.0f;

		//Mix_PlayChannel(-1, App->audio->WarriorAttack_Sound, 0);

		//if (target->GetCurrLife() <= 0)
		//	Mix_PlayChannel(-1, App->audio->Spawner_Destroyed, 0);
	}

	else {
		attackCooldown += attackSpeed * dt;
	}
}