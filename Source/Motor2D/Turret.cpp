#include "p2Defs.h"
#include "p2Log.h"

#include "Turret.h"

#include "j1SceneManager.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Pathfinding.h"
#include "j1Textures.h"

Turret::Turret(iPoint tile, int damage, j1Module* listener, Entity* creator) : Entity(tile, damage, listener, creator) {

	// Handle data and initialize the House
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_TURRET;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_STATIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_SMALL;

	maxLife = 80;
	currLife = maxLife - damage;

	size = { 400, 400 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;


	attackDamage = 10.0f;
	attackRadius = 10;
	attackSpeed = 5.0f;
	attackCooldown = attackSpeed;

	constructionTime = 15.0f;

	isEntityFromPlayer = true;

	visibilityRadius = 5;
	fow_entity->frontier = App->fow->CreateSightQuad(visibilityRadius, fow_entity->position);
	fow_entity->LOS = App->fow->FulfillSight(fow_entity->frontier);

}

Turret::~Turret() {}

void Turret::Attack(Entity* target, float dt) {

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