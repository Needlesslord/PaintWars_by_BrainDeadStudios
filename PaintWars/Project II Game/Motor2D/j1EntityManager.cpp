#include "p2Log.h"

#include "j1Module.h"
#include "j1App.h"

#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Collision.h"
#include "j1Input.h"
#include "j1Player.h"

#include "Entity.h"


j1EntityManager::j1EntityManager()
{
	name.create("entities");
}

// Destructor
j1EntityManager::~j1EntityManager() {}

bool j1EntityManager::Awake(pugi::xml_node& config) {
	bool ret = true;

	return ret;
}

bool j1EntityManager::Start() {
	bool ret = true;

	return ret;
}

bool j1EntityManager::PreUpdate() {
	bool ret = true;

	return ret;
}
bool j1EntityManager::Update(float dt) {
	bool ret = true;

	return ret;
}

bool j1EntityManager::PostUpdate() {
	bool ret = true;

	return ret;
}

bool j1EntityManager::CleanUp() {
	bool ret = true;

	return ret;
}

bool j1EntityManager::Save(pugi::xml_node& save) const {
	bool ret = true;

	return ret;
}

bool j1EntityManager::Load(pugi::xml_node& save) {
	bool ret = true;

	return ret;
}

/*void SelectGroupEntities(SDL_Rect rectangleRect) {

}*/

void j1EntityManager::UnselectAllEntities() {

}

Entity* j1EntityManager::AddEntity(ENTITY_TYPE entityType, fPoint pos, const EntityInfo& entityInfo, const UnitInfo& unitInfo, j1Module* listener) {
	if (entityType == TOWN_HALL) {
		TownHall* townHall = new TownHall(pos, { 128, 128 }, 100/*X*/, 100/*X*/, (const TownHallInfo&)entityInfo, listener);
		//townHall->SetStringLife

		toSpawnEntities.push_back((Entity*)townHall);
		return (Entity*)townHall;
	}

	else
		return nullptr;
}
