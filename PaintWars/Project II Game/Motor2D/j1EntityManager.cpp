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

	// TODO: Initialize all textures
	townHallTexture = App->tex->Load("textures/TownHall.png");
	painterTexture = App->tex->Load("textures/Painter.png");

	return ret;
}

bool j1EntityManager::PreUpdate() {
	bool ret = true;

	return ret;
}

bool j1EntityManager::Update(float dt) {
	bool ret = true;

	list<Entity*>::iterator entitiesToDraw = activeEntities.begin();
	while (entitiesToDraw != activeEntities.end()) {
		if ((*entitiesToDraw)->entityType == ENTITY_TYPE_TOWN_HALL) {
			(*entitiesToDraw)->Draw(townHallTexture);
		}
		else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_PAINTER) {
			(*entitiesToDraw)->Draw(painterTexture);
		}

		entitiesToDraw++;
	}

	return ret;
}

bool j1EntityManager::PostUpdate() {
	bool ret = true;

	return ret;
}

bool j1EntityManager::CleanUp() {
	bool ret = true;

	if (townHallTexture != nullptr)
		App->tex->UnLoad(townHallTexture);

	if (painterTexture != nullptr)
		App->tex->UnLoad(painterTexture);

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

void j1EntityManager::UnselectAllEntities() {

}

Entity* j1EntityManager::AddEntity(ENTITY_TYPE entityType, fPoint pos, j1Module* listener) {
	if (entityType == ENTITY_TYPE_TOWN_HALL) {
		TownHall* townHall = new TownHall({ pos.x, pos.y }, 100, this);
		activeEntities.push_back((Entity*)townHall);

		return (Entity*)townHall;
	}

	else if (entityType == ENTITY_TYPE_PAINTER) {
		Painter* painter = new Painter({ pos.x, pos.y }, 100, this);
		activeEntities.push_back((Entity*)painter);

		return (Entity*)painter;
	}

	else
		return nullptr;
}
