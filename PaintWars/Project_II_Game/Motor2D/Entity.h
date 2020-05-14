#ifndef __Entity_H__
#define __Entity_H__

#include "p2Point.h"
#include <vector>

#include "Animation.h"

#include "j1App.h"
#include "j1Audio.h"

class j1Module;

struct SDL_Texture;

struct Collider;

enum CollisionState;

enum UNIT_ORIENTATION { //This is needed when loading animations from tiled
	
	UNIT_ORIENTATION_NORTH = 8,
	UNIT_ORIENTATION_NORTH_EAST = 9,
	UNIT_ORIENTATION_EAST = 6,
	UNIT_ORIENTATION_SOUTH_EAST = 3,
	UNIT_ORIENTATION_SOUTH = 2,
	UNIT_ORIENTATION_SOUTH_WEST = 1,
	UNIT_ORIENTATION_WEST = 4,
	UNIT_ORIENTATION_NORTH_WEST = 7,
	UNIT_ORIENTATION_NONE = 0

};
enum ENTITY_CATEGORY {

	ENTITY_CATEGORY_NONE = 0,

	ENTITY_CATEGORY_STATIC_ENTITY,
	ENTITY_CATEGORY_DYNAMIC_ENTITY,
	ENTITY_CATEGORY_NEUTRAL_ENTITY
};

enum ENTITY_SIZE {

	ENTITY_SIZE_NONE = 0,

	ENTITY_SIZE_SMALL,		// 1*1
	ENTITY_SIZE_MEDIUM,		// 2*2
	ENTITY_SIZE_BIG,		// 3*3
	ENTITY_SIZE_VERY_BIG	// 4*4
};

enum ENTITY_TYPE {

	ENTITY_TYPE_NONE = 0,

		// TODO: Add all entities here
	// Allies
	/// Buildings
	ENTITY_TYPE_TOWN_HALL,
	ENTITY_TYPE_PAINT_EXTRACTOR,
	ENTITY_TYPE_WOOD_PRODUCER,
	ENTITY_TYPE_HOUSE,
	ENTITY_TYPE_BARRACKS,


	/// Units
	ENTITY_TYPE_PAINTER,
	ENTITY_TYPE_WARRIOR,
	ENTITY_TYPE_KNIGHT,
	ENTITY_TYPE_EXPLORER,
	ENTITY_TYPE_RANGER,

	// Enemies
	/// Buildings
	ENTITY_TYPE_SPAWNER,

	/// Units
	ENTITY_TYPE_SLIME,

	ENTITY_TYPE_MAX = 500
};

class Entity
{
public:

	Entity(iPoint tile, int damage, j1Module* listener, Entity* creator);
	virtual ~Entity();
	virtual void Draw(SDL_Texture* sprites);
	virtual void DebugDrawSelected();
	virtual void OnCollision(Collider* c1, Collider* c2);
	virtual void CalculateMovementLogic();
	virtual void MovementLogic();
	virtual void Move(float dt);
	virtual void SetDestination(iPoint des);
	virtual void SpawnEntity();
	virtual void ExtractPaint(float dt);
	virtual void ExtractWood(float dt);
	virtual void Attack(Entity* target, float dt);

	// Position and size
	void SetPos(fPoint pos);
	fPoint GetPos() const;
	iPoint GetSize() const;
	iPoint GetOffsetSize() const;

	// Life and damage
	void SetMaxLife(int life);
	float GetMaxLife() const;
	void SetCurrLife(int currLife);
	float GetCurrLife() const;
	void ApplyDamage(float damage);
	void ApplyHealth(float health);

	// Collision
	Collider* GetEntityCollider() const;

	bool CreateEntityCollider(fPoint pos, Entity* entity);

	void ShowHealthBar();
	void ShowProgressBar();

public:

	const ENTITY_CATEGORY entityCategory = ENTITY_CATEGORY_NONE;
	const ENTITY_TYPE entityType = ENTITY_TYPE_NONE;
	const ENTITY_SIZE entitySize = ENTITY_SIZE_NONE;
	const UNIT_ORIENTATION unitOrientation = UNIT_ORIENTATION_NONE;

	bool isSelected = false;
	bool isEntityFromPlayer = NULL;
	bool isOnTheMove;

	float speed = 0;
	float Entity_HP;
	fPoint pos = { 0.0f,0.0f };
	iPoint currentTile = { 0,0 };

	iPoint destination;
	iPoint nextTile;

	std::vector<iPoint>currentPath;
	uint pathIterator;

	Entity* target;
	SDL_Rect target_rect;

	float attackDamage = 0.0f;
	float attackSpeed = 0.0f;
	float attackCooldown = 1.0f;
	uint attackRadius = 1; // In tiles
	//float attackProgress = 0.0f;

	SDL_Color minimapDrawColor{ 0,0,0,0 };

	// Collision
	Collider* entityCollider = nullptr;

	float spawningTime;
	float spawningProgress;

	float constructionTime;
	float constructionProgress;

	bool isSpawningAUnit;
	bool isBuildingSomething;
	bool isAlive;

	Entity* spawnedBy;
	Entity* builtBy;

	Animation* currentAnimation;
	UNIT_ORIENTATION previousOrientation = UNIT_ORIENTATION_NONE;

	// Paint speed
	float extractionRate = 0.0f;

protected:

	iPoint size = { 0,0 };
	iPoint offsetSize = { 0,0 };

	float currLife = 0;
	float maxLife = 0;
	string lifeString;

	j1Module* listener = nullptr; // callback

	

	
	
	fPoint past_frame_dest;


};

#endif //__Entity_H__