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

enum ORIENTATION { //This is needed when loading animations from tiled
	
	ORIENTATION_NORTH,
	ORIENTATION_NORTH_EAST,
	ORIENTATION_EAST,
	ORIENTATION_SOUTH_EAST,
	ORIENTATION_SOUTH,
	ORIENTATION_SOUTH_WEST,
	ORIENTATION_WEST,
	ORIENTATION_NORTH_WEST,
	NONE


};
enum ENTITY_CATEGORY {

	ENTITY_CATEGORY_NONE = 0,

	ENTITY_CATEGORY_STATIC_ENTITY,
	ENTITY_CATEGORY_DYNAMIC_ENTITY
};

enum ENTITY_SIZE {

	ENTITY_SIZE_NONE = 0,

	ENTITY_SIZE_MINI,		// 1*1	20
	ENTITY_SIZE_SMALL,		// 2*2	40
	ENTITY_SIZE_MEDIUM,		// 3*3	60
	ENTITY_SIZE_BIG,		// 4*4	80
	ENTITY_SIZE_VERY_BIG,	// 5*5 100
	ENTITY_SIZE_GIGANTIC	// 6*6 120
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
	/// Buildings
	ENTITY_TYPE_TOWN_HALL,

	/// Units
	ENTITY_TYPE_PAINTER,
	ENTITY_TYPE_WARRIOR,
	ENTITY_TYPE_SLIME,

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
	//virtual void Move(iPoint destination);

	// Position and size
	void SetPos(fPoint pos);
	void AddToPos(fPoint pos);
	fPoint GetPos() const;
	iPoint GetSize() const;
	iPoint GetOffsetSize() const;

	// Life and damage
	void SetMaxLife(int life);
	float GetMaxLife() const;
	void SetCurrLife(int currLife);
	float GetCurrLife() const;
	void ApplyDamage(int damage);
	void ApplyHealth(int health);

	// Collision
	Collider* GetEntityCollider() const;
	bool CreateEntityCollider(fPoint pos);

	void ShowHealthBar();
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

	float currLife = 0;
	float maxLife = 0;
	string lifeString;

	j1Module* listener = nullptr; // callback

	// Collision
	Collider* entityCollider = nullptr;


protected:

	Animation North_Animation;
	
	fPoint past_frame_dest;



};

#endif //__Entity_H__