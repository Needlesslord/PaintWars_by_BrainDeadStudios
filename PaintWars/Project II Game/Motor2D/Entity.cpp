#include "p2Log.h"

#include "Entity.h"

#include "j1App.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Map.h"
#include "j1EntityManager.h"
#include "j1Player.h"

Entity::Entity(fPoint pos, int currLife, j1Module* listener) : pos(pos), currLife(currLife), listener(listener)
{
	if (this->currLife == 0)
		this->currLife = this->maxLife;
}

Entity::~Entity() {}

void Entity::Draw(SDL_Texture* sprites)
{
}

void Entity::DebugDrawSelected()
{
}

void Entity::OnCollision(ColliderGroup* c1, ColliderGroup* c2, CollisionState collisionState) {}

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
	SetStringLife(currLife, maxLife);
}

// Life and damage
int Entity::GetMaxLife() const
{
	return maxLife;
}

void Entity::SetCurrLife(int currLife)
{
	this->currLife = currLife;
	SetStringLife(currLife, maxLife);
}

int Entity::GetCurrLife() const
{
	return currLife;
}

void Entity::ApplyDamage(int damage)
{
	currLife -= damage;
	if (currLife < 0)
		currLife = 0;
	SetStringLife(currLife, maxLife);	
}

void Entity::ApplyHealth(int health) 
{
	if (currLife + health >= maxLife)
		currLife = maxLife;
	else
		currLife += health;

	SetStringLife(currLife, maxLife);
}

string Entity::GetStringLife() const
{
	return lifeString;
}

void Entity::SetStringLife(int currentLife, int maxLife) 
{
	lifeString = to_string(currentLife) + "/" + to_string(maxLife);
}

// Collision
ColliderGroup* Entity::GetEntityCollider() const
{
	return entityCollider;
}

bool Entity::CreateEntityCollider(fPoint pos) {
	if (entitySize == ENTITY_SIZE_MEDIUM) {
		if (entityType == ENTITY_TYPE_TOWN_HALL) {
			COLLIDER_TYPE collType = COLLIDER_ALLY_BUILDING;
			vector<Collider*> collider;
			SDL_Rect rect = { pos.x, pos.y, 30, 30 };
			App->col->AddCollider(rect, collType, App->entities);
			collider.push_back(App->col->AddCollider(rect, collType, App->entities));

			return true;
		}
	}
	else
		return false;
}
