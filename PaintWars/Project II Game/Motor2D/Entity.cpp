#include "p2Log.h"

#include "Entity.h"

#include "j1App.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Map.h"
#include "j1EntityManager.h"
#include "j1Player.h"

Entity::Entity(fPoint pos, iPoint size, int currLife, uint maxLife, j1Module* listener) : pos(pos), size(size), currLife(currLife), maxLife(maxLife), listener(listener)
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

bool Entity::CreateEntityCollider(bool isEntityFromPlayer, bool createOffset)
{
	COLLIDER_TYPE collType = COLLIDER_ALLY_BUILDING;

	vector<Collider*> collider;
	SDL_Rect rect = { pos.x, pos.y, size.x, size.y };
	App->col->AddCollider(rect, collType, App->entities);
	//collider.push_back(App->col->CreateCollider(rect));

	return false;
}

//void Entity::UpdateEntityColliderPos()
//{
//	if (entityCollider != nullptr)
//	{
//		Collider* front = entityCollider->colliders.front();
//		if (front != nullptr)
//			entityCollider->colliders.front()->SetPos(pos.x, pos.y);
//
//		// 2. Create/Update the offset collider
//		entityCollider->CreateOffsetCollider();
//	}
//}

// Attack
/// Entity is being attacked by units
bool Entity::AddAttackingUnit(Entity* entity)
{
	bool ret = false;

	if (entity == nullptr)
		return ret;

	if (find(unitsAttacking.begin(), unitsAttacking.end(), entity) == unitsAttacking.end()) {
		unitsAttacking.push_back(entity);
		ret = true;
	}

	return ret;
}

bool Entity::RemoveAttackingUnit(Entity* entity)
{
	bool ret = false;

	if (find(unitsAttacking.begin(), unitsAttacking.end(), entity) != unitsAttacking.end()) {
		unitsAttacking.remove(entity);
		ret = true;
	}

	return ret;
}

uint Entity::GetAttackingUnitsSize(Entity* attackingUnit) const
{
	list<Entity*>::const_iterator it = unitsAttacking.begin();
	uint size = 0;

	while (it != unitsAttacking.end()) {

		if (*it != attackingUnit)
			size++;

		it++;
	}

	return size;
}

// Valid
void Entity::SetIsValid(bool isValid)
{
	this->isValid = isValid;
}

bool Entity::GetIsValid() const
{
	return isValid;
}