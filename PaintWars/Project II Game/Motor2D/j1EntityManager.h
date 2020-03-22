#ifndef __j1ENTITY_FACTORY_H__
#define __j1ENTITY_FACTORY_H__

#include "j1Module.h"
#include "p2Point.h"

// Units
#include "Painter.h"

// Buildings
#include "TownHall.h"


#include <string>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX_UNITS_SELECTED 8
#define MAX_SAVED_GROUPS 3

struct SDL_Texture;
struct SDL_Rect;

class Entity;

enum ENTITY_TYPE;

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	virtual ~j1EntityManager();
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	//void OnCollision(ColliderGroup* c1, ColliderGroup* c2, CollisionState collisionState);
	bool PostUpdate();
	bool CleanUp();

	Entity* AddEntity(ENTITY_TYPE entityType, fPoint pos, j1Module* listener = nullptr, int damage = 0);

	// Selects an Entity
	bool SelectEntity(Entity* entity, bool controlWasPressed = false);

	// Selects the entities within a rectangle
	void SelectGroupEntities(SDL_Rect rect);

	// Unselects all entities
	void UnselectAllEntities();	

	bool Save(pugi::xml_node& save) const;
	bool Load(pugi::xml_node& save);

public:

	list<Entity*> toSpawnEntities;
	list<Entity*> activeEntities;
	list<Entity*> activeBuildings;
	list<Entity*> activeUnits;

	list<Entity*> entitiesSelected;
	list<Entity*> unitsSelected;
	list<Entity*> buildingsSelected;

	// Thsese two need to be public so that each entity can use it
	SDL_Texture* fullLifeTexture = nullptr;
	SDL_Texture* zeroLifeTexture = nullptr;

protected:

	SDL_Texture* townHallTexture = nullptr;
	SDL_Texture* painterTexture = nullptr;

};

#endif //__j1ENTITY_FACTORY_H__