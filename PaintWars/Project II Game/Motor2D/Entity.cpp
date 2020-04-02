#include "p2Log.h"
#include <vector>

#include "Entity.h"

#include "j1App.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Map.h"
#include "j1EntityManager.h"
#include "j1Player.h"

Entity::Entity(fPoint pos, int damage, j1Module* listeners) : pos(pos), currLife(maxLife - damage), listener(listener)
{
	if (this->currLife == 0)
		this->currLife = this->maxLife;
}

Entity::~Entity() {}

void Entity::Draw(SDL_Texture* sprites) {
	if (sprites != nullptr)
		App->render->AddBlitEvent(1, sprites, pos.x - size.x / 2, pos.y - size.y / 2, { 0, 0, size.x, size.y });
}

void Entity::DebugDrawSelected()
{
}

void Entity::OnCollision(ColliderGroup* c1, ColliderGroup* c2, CollisionState collisionState) {}

void Entity::CalculateMovementLogic() {}

void Entity::Move(float dt) {}

void Entity::SetDestination(iPoint des) {}
// -------------------------------------------------------------

// Position and size
void Entity::SetPos(fPoint pos)
{
	this->pos = pos;
}

void Entity::AddToPos(fPoint pos)
{
	this->pos.x += pos.x;
	this->pos.y += pos.y;
}

fPoint Entity::GetPos() const
{
	return pos;
}

iPoint Entity::GetSize() const
{
	return size; 
}

iPoint Entity::GetOffsetSize() const
{
	return offsetSize;
}

void Entity::SetMaxLife(int life)
{
	maxLife = life;
}

// Life and damage
float Entity::GetMaxLife() const
{
	return maxLife;
}

void Entity::SetCurrLife(int currLife)
{
	this->currLife = currLife;
}

float Entity::GetCurrLife() const
{
	return currLife;
}

void Entity::ApplyDamage(int damage)
{
	currLife -= damage;
	if (currLife < 0)
		currLife = 0;
}

void Entity::ApplyHealth(int health) 
{
	if (currLife + health >= maxLife)
		currLife = maxLife;
	else
		currLife += health;

}

// Collision
Collider* Entity::GetEntityCollider() const
{
	return entityCollider;
}

bool Entity::CreateEntityCollider(fPoint pos) {

		// Allies
	/// Buildings
	if (entityType == ENTITY_TYPE_TOWN_HALL) {
		COLLIDER_TYPE collType = COLLIDER_ALLY_BUILDING;
		vector<Collider*> collider;
		SDL_Rect rect = { pos.x - GetSize().x/2, pos.y - GetSize().y / 2, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);
		collider.push_back(entityCollider);

		return true;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_PAINTER) {
		COLLIDER_TYPE collType = COLLIDER_ALLY_UNIT;
		vector<Collider*> collider;
		SDL_Rect rect = { pos.x - GetSize().x / 2, pos.y - GetSize().y / 2, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);
		collider.push_back(entityCollider);

		return true;
	}

	else if (entityType == ENTITY_TYPE_WARRIOR) {
		COLLIDER_TYPE collType = COLLIDER_ALLY_UNIT;
		vector<Collider*> collider;
		SDL_Rect rect = { pos.x - GetSize().x / 2, pos.y - GetSize().y / 2, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);
		collider.push_back(entityCollider);

		return true;
	}
		
		// Enemies
	/// Buildings
	else if (entityType == ENTITY_TYPE_SPAWNER) {
		COLLIDER_TYPE collType = COLLIDER_ENEMY_BUILDING;
		vector<Collider*> collider;
		SDL_Rect rect = { pos.x - GetSize().x / 2, pos.y - GetSize().y / 2, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);
		collider.push_back(entityCollider);

		return true;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_SLIME) {
		COLLIDER_TYPE collType = COLLIDER_ENEMY_UNIT;
		vector<Collider*> collider;
		SDL_Rect rect = { pos.x - GetSize().x / 2, pos.y - GetSize().y / 2, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);
		collider.push_back(entityCollider);

		return true;
	}

	else
		return false;
}

void Entity::ShowHealthBar() {
	if (GetCurrLife() != GetMaxLife()) {
		App->render->AddBlitEvent(1, App->entities->zeroLifeTexture, pos.x - GetSize().x / 2, pos.y - 20 - GetSize().y / 2, { 0, 0, size.x, 8 });
	}
	App->render->AddBlitEvent(1, App->entities->fullLifeTexture, pos.x - GetSize().x / 2, pos.y - 20 - GetSize().y / 2, { 0, 0, (int)((currLife/maxLife)*size.x), 8 });
}