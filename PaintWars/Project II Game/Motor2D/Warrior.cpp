#include "p2Defs.h"
#include "p2Log.h"
#include <vector>

#include "Warrior.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"
#include "j1Render.h"

Warrior::Warrior(iPoint tile, int damage, j1Module* listener, Entity* creator) : Entity(tile, damage, listener, creator) {

	// Handle data and initialize the Warrior
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_WARRIOR;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_SMALL;
	*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;

	maxLife = 30;
	currLife = maxLife - damage;

	size = { 62, 118 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	speed = 300.0f;
	
	spawningTime = 10.0f;

	destination = currentTile;

	attackDamage = 10.0f;
	attackSpeed = 20.0f;
	attackCooldown = attackSpeed;

	isEntityFromPlayer = true;
}

Warrior::~Warrior() {}

void Warrior::Attack(Entity* target, float dt) {

	if (attackCooldown >= attackSpeed) {

		target->ApplyDamage(attackDamage);
		attackCooldown = 0.0f;
	}

	else {
		attackCooldown += attackSpeed * dt;
	}
}

void Warrior::Draw(SDL_Texture* sprites)
{
	App->render->AddBlitEvent(1, sprites, pos.x, pos.y, currentAnimation->GetCurrentFrame());
}