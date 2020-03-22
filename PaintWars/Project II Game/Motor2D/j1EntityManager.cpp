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

		// Allies
	/// Buildings
	townHallTexture = App->tex->Load("textures/TownHall.png");
	
	/// Units
	painterTexture = App->tex->Load("textures/Painter.png");
	warriorTexture = App->tex->Load("textures/Warrior.png");

		// Enemies
	/// Buildings

	/// Units
	SlimeTexture = App->tex->Load("textures/Slime.png");


	fullLifeTexture = App->tex->Load("textures/FullLife.png");
	zeroLifeTexture = App->tex->Load("textures/ZeroLife.png");

	return ret;
}

bool j1EntityManager::PreUpdate() {
	bool ret = true;

	return ret;
}

bool j1EntityManager::Update(float dt) {
	bool ret = true;

	// Check if there was any unit selected when LEFT MOUSE BUTTON was pressed and if not, unselect all
	// If control was pressed as a unit was selected, the rest of selected units aren't unselected
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {

		bool controlWasPressed = false;
		if (App->input->GetKey(SDL_SCANCODE_LCTRL)) 
			controlWasPressed = true;

		bool isSomeEntitySelected = false;

		list<Entity*>::iterator checkForSelectedEntities = activeEntities.begin();
		while (checkForSelectedEntities != activeEntities.end()) {

			int x, y;
			App->input->GetMousePosition(x, y);
			if (x > (*checkForSelectedEntities)->pos.x && x < ((*checkForSelectedEntities)->pos.x) + (*checkForSelectedEntities)->GetSize().x &&
				y > (*checkForSelectedEntities)->pos.y && y < ((*checkForSelectedEntities)->pos.y) + (*checkForSelectedEntities)->GetSize().y) {
				SelectEntity(*checkForSelectedEntities, controlWasPressed);
				isSomeEntitySelected = true;
				break;

			}

			checkForSelectedEntities++;

		}

		// Unselect all
		if (!isSomeEntitySelected) UnselectAllEntities();
	}


	// LifeBars from selected  on HUD
	list<Entity*>::iterator selectedEntities = entitiesSelected.begin();
	while (selectedEntities != entitiesSelected.end()) {

		if ((*selectedEntities)->GetCurrLife() != (*selectedEntities)->GetMaxLife()) {		
			App->render->AddBlitEvent(1, zeroLifeTexture, 400, 400, { 0, 0, 100, 10 });
		}
		App->render->AddBlitEvent(1, fullLifeTexture, 400, 400, { 0, 0, (int)(((*selectedEntities)->GetCurrLife() / (*selectedEntities)->GetMaxLife()) * 100), 10 });
		
		selectedEntities++;
	}

	// LifeBars from selected units on top of themselves
	list<Entity*>::iterator selectedUnits = unitsSelected.begin();
	while (selectedUnits != unitsSelected.end()) {
		(*selectedUnits)->ShowHealthBar();
		selectedUnits++;
	}


	// Draw all active entities
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


	App->tex->UnLoad(fullLifeTexture);
	App->tex->UnLoad(zeroLifeTexture);

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

	list<Entity*>::iterator unselectEntities = activeEntities.begin();
	while (unselectEntities != activeEntities.end()) {
		(*unselectEntities)->isSelected = false;
		unselectEntities++;
	}

	entitiesSelected.clear();
	unitsSelected.clear();
	buildingsSelected.clear();

}

Entity* j1EntityManager::AddEntity(ENTITY_TYPE entityType, fPoint pos, j1Module* listener, int damage) {

		// Allies
	/// Buildings
	if (entityType == ENTITY_TYPE_TOWN_HALL) {
		TownHall* townHall = new TownHall({ pos.x, pos.y }, damage, this);
		activeEntities.push_back((Entity*)townHall);
		activeBuildings.push_back((Entity*)townHall);

		return (Entity*)townHall;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_PAINTER) {
		Painter* painter = new Painter({ pos.x, pos.y }, damage, this);
		activeEntities.push_back((Entity*)painter);
		activeUnits.push_back((Entity*)painter);

		return (Entity*)painter;
	}

	else if (entityType == ENTITY_TYPE_WARRIOR) {
		Warrior* warrior = new Warrior({ pos.x, pos.y }, damage, this);
		activeEntities.push_back((Entity*)warrior);
		activeUnits.push_back((Entity*)warrior);

		return (Entity*)warrior;
	}

		// Enemies
	/// Buildings

	/// Units
	else if (entityType == ENTITY_TYPE_SLIME) {
		Slime* slime = new Slime({ pos.x, pos.y }, damage, this);
		activeEntities.push_back((Entity*)slime);
		activeUnits.push_back((Entity*)slime);

		return (Entity*) slime;
	}

	else
		return nullptr;
}

bool j1EntityManager::SelectEntity(Entity* entity, bool controlWasPressed) {

	if (!controlWasPressed) {
		UnselectAllEntities();
	}

	if (entity->entityCategory == ENTITY_CATEGORY_DYNAMIC_ENTITY)
		unitsSelected.push_back(entity);

	else if (entity->entityCategory == ENTITY_CATEGORY_STATIC_ENTITY)
		buildingsSelected.push_back(entity);
	
	entitiesSelected.push_back(entity);
	entity->isSelected = true;

	// If a unit is selected, show data on update (Entity.cpp)
	return true;
}

void j1EntityManager::SelectGroupEntities(SDL_Rect rect) {

}