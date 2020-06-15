#include "ChromaKing.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Particles.h"

ChromaKing::ChromaKing(iPoint tile, int damage, j1Module* listener) : Entity(tile, damage, listener, nullptr) {

	// Handle data and initialize the Warrior
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_CHROMA_KING;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_SMALL;

	maxLife = 500;
	currLife = maxLife - damage;

	size = { 250, 250 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	speed = 250.0f;

	destination = currentTile;

	attackDamage = 15.0f;
	attackRadius = 2;

	attackSpeed = 35.0f;
	attackCooldown = attackSpeed;

	isEntityFromPlayer = false;
}

ChromaKing::~ChromaKing() {}


void ChromaKing::Attack(Entity* target, float dt) {

	if (attackCooldown >= attackSpeed) {

		Particles * p = AddParticle(PARTICLE_TYPE::PARTICLE_SLIME, { pos.x + size.x / 2,pos.y + size.y / 2 }, { 0, 0 });

		particles.push_back(p);

		attackCooldown = 0.0f;

		//Mix_PlayChannel(-1, App->audio->WarriorAttack_Sound, 0);

		//if (target->GetCurrLife() <= 0)
		//	Mix_PlayChannel(-1, App->audio->Spawner_Destroyed, 0);
	}

	else {
		attackCooldown += 10 * dt;
	}
}

void ChromaKing::Draw(SDL_Texture* sprites) {

	App->render->RenderQueue(1, sprites, pos.x, pos.y, currentAnimation->GetCurrentFrame());
}
