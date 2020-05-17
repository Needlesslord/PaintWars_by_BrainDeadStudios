#ifndef __j1ENTITY_FACTORY_H__
#define __j1ENTITY_FACTORY_H__

#include "j1Module.h"


	// Allies
/// Buildings
#include "TownHall.h"
#include "PaintExtractor.h"
#include "WoodProducer.h"
#include "House.h"
#include "Barracks.h"

/// Units
#include "Painter.h"
#include "Warrior.h"
#include "Knight.h"
#include "Explorer.h"
#include "Ranger.h"

	// Enemies
/// Buildings
#include "Spawner.h"

/// Units
#include "Slime.h"


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
	bool PostUpdate();
	void OnCollision(Collider* c1, Collider* c2);
	bool CleanUp();

	Entity* AddEntity(ENTITY_TYPE entityType, iPoint tile, j1Module* listener = nullptr, Entity* creator = nullptr, float damage = 0.0f, bool spawnAutomatically = false);

	// Selects an Entity
	bool SelectEntity(Entity* entity, bool controlWasPressed = false);

	// Selects the entities within a rectangle
	void SelectGroupEntities(SDL_Rect rect);

	// Unselects all entities
	void UnselectAllEntities();	

	bool Save(pugi::xml_node& save) const;
	bool Load(pugi::xml_node& save);
	void TriggerEndGame(bool isVictory);
	void LoadEntityTextures();

	void UpdateAnimations();
	
private:

public:

	std::list<Entity*> spawningEntities;
	std::list<Entity*> activeEntities;
	std::list<Entity*> activeBuildings;
	std::list<Entity*> activeUnits;

	std::list<Entity*> entitiesSelected;
	std::list<Entity*> unitsSelected;
	std::list<Entity*> buildingsSelected;

	std::list<iPoint> tilesOccupied;
	std::list<iPoint> destinations;

	std::list<Particles*> particles;

	// Thsese two need to be public so that each entity can use it
	SDL_Texture* fullLifeTexture = nullptr;
	SDL_Texture* zeroLifeTexture = nullptr;
	SDL_Texture* progressTexture = nullptr;
	SDL_Texture* zeroProgressTexture = nullptr;

	//small fix hp bar when blit
	float Entity_HP;

	bool isSelectingPlacement = false;
	ENTITY_TYPE hoveringEntityType = ENTITY_TYPE::ENTITY_TYPE_NONE;

	bool warriorsUpgraded = false;
	bool paintersUpgraded = false;
	bool paintExtractorUpgraded = false;
	bool woodProducersUpgraded = false;
	bool ExtractorQuestDone = false;
	bool titaniumExtractorUpgraded = false;
	bool metalGathererUpgraded = false;

	bool spacePressed = false;

protected:

		// Allies
	/// Buildings
	SDL_Texture* townHallTexture = nullptr;
	SDL_Texture* paintExtractorTexture = nullptr;
	SDL_Texture* woodProducerTexture = nullptr;
	SDL_Texture* houseTexture = nullptr;
	SDL_Texture* barracksTexture = nullptr;
	SDL_Texture* buildingTexture = nullptr;
	SDL_Texture* titaniumExtractorTexture = nullptr;
	SDL_Texture* metalGathererTexture = nullptr;

	/// Units
	SDL_Texture* painterTexture = nullptr;
	SDL_Texture* warriorTexture = nullptr;
	SDL_Texture* knightTexture = nullptr;
	SDL_Texture* explorerTexture = nullptr;
	SDL_Texture* rangerTexture = nullptr;

		// Enemies
	/// Buildings
	SDL_Texture* spawnerTexture = nullptr;

	/// Units
	SDL_Texture* slimeTexture = nullptr;
	SDL_Texture* riderTexture = nullptr;

	float spawningRate = 1.0f;
	float constructionRate = 1.0f;
	

private:

	float currentLifeSum;
	float maxLifeSum;

	SDL_Texture* debug_tex = nullptr;
	bool EntityTexturesAreLoaded;


};

#endif //__j1ENTITY_FACTORY_H__





//--------------------------------------------------------------------------------------------------------


//STD LISTS USE


//std::list<item> list  IGUAL QUE LA LIST DEL P2 LIST

//std::list<item>::iterator PER PASAR PER LA LLISTA D'ITEMS ---- EXEMPLE:

//for (std::list<Module*>::iterator item = modules.begin(); item != modules.end() && ret; ++item)
//{
//	ret = (*item)->Start();
//}



//item = list.begin(); PER COMENÇAR LA LLISTA DESDE EL PRINCIPI



//for(; item != list.end(); ++item)  SI PER EXEMPLE VOLEM QUE PASI PER LA LLISTA FINS AL FINAL
//{
//}


//list.erase(item)   BORRAR COSES DE LA LLISTA


//list.pushback(Module* module)  POSAR ITEMS A UNA LLISTA JA CREADA

// (*item)->itemquequeremos    ACCEDIR AL ITEM DE LA LLISTA  

