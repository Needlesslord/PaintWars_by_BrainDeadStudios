#include "p2Defs.h"
#include "p2Log.h"
#include "SDL_mixer/include/SDL_mixer.h"

#include "Turret.h"

#include "j1Audio.h"
#include "j1SceneManager.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Pathfinding.h"
#include "j1Textures.h"
#include "j1Particles.h"

Turret::Turret(iPoint tile, int damage, j1Module* listener, Entity* creator) : Entity(tile, damage, listener, creator) {

	// Handle data and initialize the House
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_TURRET;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_STATIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_MEDIUM;

	maxLife = 250;
	currLife = maxLife - damage;

	size = { 250, 400 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;


	attackDamage = 10.0f;
	attackRadius = 6;
	attackSpeed = 15.0f;
	attackCooldown = attackSpeed;

	constructionTime = 25.0f;

	isEntityFromPlayer = true;

	visibilityRadius = 6;
	fow_entity->frontier = App->fow->CreateSightQuad(visibilityRadius, fow_entity->position);
	fow_entity->LOS = App->fow->FulfillSight(fow_entity->frontier);

}

Turret::~Turret() {}

void Turret::Attack(Entity* target, float dt) {

	if (attackCooldown >= attackSpeed) {

		Particles * p = AddParticle(PARTICLE_TYPE::PARTICLE_RANGER, { pos.x + size.x / 2,pos.y + size.y / 2 }, { 0, 0 });

		particles.push_back(p);

		attackCooldown = 0.0f;

		// TODO: change
		App->audio->PlayFx(App->audio->attack_Sound);
	}

	else {
		attackCooldown += 10 * dt;
	}
}