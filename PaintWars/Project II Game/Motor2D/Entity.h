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

enum ENTITY_CATEGORY {

	ENTITY_CATEGORY_NONE = 0,

	ENTITY_CATEGORY_STATIC_ENTITY,
	ENTITY_CATEGORY_DYNAMIC_ENTITY,
	ENTITY_CATEGORY_MAX
};

enum ENTITY_SIZE {

	ENTITY_SIZE_NONE = 0,

	ENTITY_SIZE_MINI,	// 1*1
	ENTITY_SIZE_SMALL,  // 2*2
	ENTITY_SIZE_MEDIUM, // 3*3
	ENTITY_SIZE_BIG		// 4*4

};

//enum EntitiesEvent
//{
//	EntitiesEvent_NONE,
//	EntitiesEvent_RIGHT_CLICK,
//	EntitiesEvent_LEFT_CLICK,
//	EntitiesEvent_HOVER,
//	EntitiesEvent_LEAVE,
//	EntitiesEvent_CREATED,
//};

enum ENTITY_TYPE
{
	ENTITY_TYPE_NONE = 0,

	// TODO: Add all entities here

	ENTITY_TYPE_TOWN_HALL,
	ENTITY_TYPE_PAINTER,

	ENTITY_TYPE_MAX = 500
};

class Entity;

class Entity
{
public:

	Entity(fPoint pos, int currLife, j1Module* listener);
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
	bool CreateEntityCollider(fPoint pos);

public:
	const ENTITY_CATEGORY entityCategory = ENTITY_CATEGORY_NONE;
	const ENTITY_TYPE entityType = ENTITY_TYPE_NONE;
	const ENTITY_SIZE entitySize = ENTITY_SIZE_NONE;

	bool isSelected = false;
	bool isEntityFromPlayer = NULL;

	fPoint pos = { 0.0f,0.0f };

	SDL_Color minimapDrawColor{ 0,0,0,0 };

protected:

	iPoint size = { 0,0 };
	iPoint offsetSize = { 0,0 };

	int currLife = 0;
	uint maxLife = 0;
	string lifeString;

	j1Module* listener = nullptr; // callback

	SDL_Texture* texture = nullptr;

	// Collision
	ColliderGroup* entityCollider = nullptr;
};

#endif //__Entity_H__