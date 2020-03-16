#ifndef __Entity_H__
#define __Entity_H__

#include "p2Point.h"
#include "Animation.h"

#include "j1App.h"
#include "j1Audio.h"

class j1Module;

struct SDL_Texture;

struct Collider;
struct ColliderGroup;

enum CollisionState;

enum ENTITY_CATEGORY 
{

	EntityCategory_NONE,
	EntityCategory_STATIC_ENTITY,
	EntityCategory_DYNAMIC_ENTITY,
	EntityCategory_MAX
};

enum EntitiesEvent
{
	EntitiesEvent_NONE,
	EntitiesEvent_RIGHT_CLICK,
	EntitiesEvent_LEFT_CLICK,
	EntitiesEvent_HOVER,
	EntitiesEvent_LEAVE,
	EntitiesEvent_CREATED,
};

enum ENTITY_TYPE
{
	EntityType_NONE = 0,

	// TODO: Add all entities here

	TOWN_HALL,

	EntityType_MAX = 500
};

class Entity;

class Entity
{
public:

	Entity(fPoint pos, iPoint size, int currLife, uint maxLife, j1Module* listener);
	virtual ~Entity();
	virtual void Draw(SDL_Texture* sprites);
	virtual void DebugDrawSelected();
	virtual void OnCollision(ColliderGroup* c1, ColliderGroup* c2, CollisionState collisionState);

	// Position and size
	void SetPos(fPoint pos);
	void AddToPos(fPoint pos);
	fPoint GetPos() const;
	iPoint GetSize() const;
	iPoint GetOffsetSize() const;

	// Life and damage
	void SetMaxLife(int life);
	int GetMaxLife() const;
	void SetCurrLife(int currLife);
	int GetCurrLife() const;
	void ApplyDamage(int damage);
	void ApplyHealth(int health);

	string GetStringLife() const;
	void SetStringLife(int currentLife, int maxLife);

	// Collision
	ColliderGroup* GetEntityCollider() const;
	bool CreateEntityCollider(bool isEntityFromPlayer, bool createOffset = false);
	void UpdateEntityColliderPos();

	// Attack
	/// Entity is being attacked by units
	bool AddAttackingUnit(Entity* entity);
	bool RemoveAttackingUnit(Entity* entity);
	uint GetAttackingUnitsSize(Entity* attackingUnit) const;

	// Valid
	void SetIsValid(bool isValid);
	bool GetIsValid() const;

public:

	const ENTITY_CATEGORY entityType = EntityCategory_NONE;

	bool isRemove = false;
	bool isSelected = false;
	bool isEntityFromPlayer = true;

	fPoint pos = { 0.0f,0.0f };

	SDL_Color minimapDrawColor{ 0,0,0,0 };

	int enemyGroup = -1;

protected:

	iPoint size = { 0,0 };
	iPoint offsetSize = { 0,0 };

	int currLife = 0;
	uint maxLife = 0;
	string lifeString;

	j1Module* listener = nullptr; // callback

	// Collision
	ColliderGroup* entityCollider = nullptr;

	// Attack
	list<Entity*> unitsAttacking;

	// Valid
	bool isValid = true;
};

#endif //__Entity_H__