#include "p2Log.h"

#include "j1Module.h"
#include "j1App.h"

#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "Scene.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Collision.h"
#include "j1Input.h"
#include "j1Player.h"
#include "j1Window.h"

#include "Entity.h"


j1EntityManager::j1EntityManager()
{
	name = ("entities");
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
	warrior_Texture = App->tex->Load("textures/Warrior_Sprite.png");
		// Enemies
	/// Buildings
	spawnerTexture = App->tex->Load("textures/Spawner.png");

	/// Units
	slimeTexture = App->tex->Load("textures/Slime.png");


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

	

	// Check if a unit was set to spawn


	// Spawn entities that finished their spawning time
	list<Entity*>::iterator checkForSpawningEntities = spawningEntities.begin();
	while (checkForSpawningEntities != spawningEntities.end()) {

		if ((*checkForSpawningEntities)->spawningProgress * spawningRate >= (*checkForSpawningEntities)->spawningTime) {

			(*checkForSpawningEntities)->isActive = true;
			
			if ((*checkForSpawningEntities)->entityCategory == ENTITY_CATEGORY_DYNAMIC_ENTITY) {
				activeEntities.push_back(*checkForSpawningEntities);
				activeUnits.push_back(*checkForSpawningEntities);
			}
			
			else if ((*checkForSpawningEntities)->entityCategory == ENTITY_CATEGORY_STATIC_ENTITY) {
				activeEntities.push_back(*checkForSpawningEntities);
				activeBuildings.push_back(*checkForSpawningEntities);
			}

			(*checkForSpawningEntities)->CreateEntityCollider((*checkForSpawningEntities)->pos);
			(*checkForSpawningEntities)->spawnedBy->isSpawningAUnit = false;

			spawningEntities.erase(checkForSpawningEntities);
	
		}

		else if ((*checkForSpawningEntities)->spawningProgress * spawningRate < (*checkForSpawningEntities)->spawningTime) {

			(*checkForSpawningEntities)->spawningProgress += spawningRate * dt;
		}

		checkForSpawningEntities++;
	}

	// Check if there was any unit selected when LEFT MOUSE BUTTON was pressed and if not, unselect all
	// If control was pressed as a unit was selected, the rest of selected units aren't unselected
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {

		bool isSomethingSelected = false;

		float x, y;
		App->input->GetMousePosition(x, y);
		fPoint mouseMapCoordinates = App->render->ScreenToWorld(x, y);
		//mouseWorldCoordinates.x < spawnEntityUIButton->rect.x + spawnEntityUIButton->rect.w && mouseWorldCoordinates.x + mouseWorldCoordinates.w > spawnEntityUIButton->rect.x && mouseWorldCoordinates.y < spawnEntityUIButton->rect.y + spawnEntityUIButton->rect.h && mouseWorldCoordinates.h + mouseWorldCoordinates.y > spawnEntityUIButton->rect.y
		if (spawnEntityUIButton != nullptr) {

			fPoint mouseWorldCoordinates;
			App->input->GetMousePosition(mouseWorldCoordinates.x, mouseWorldCoordinates.y);

			if 	(mouseWorldCoordinates.x < spawnEntityUIButton->rect.x + spawnEntityUIButton->rect.w && mouseWorldCoordinates.x > spawnEntityUIButton->rect.x && 
				mouseWorldCoordinates.y < spawnEntityUIButton->rect.y + spawnEntityUIButton->rect.h && mouseWorldCoordinates.y > spawnEntityUIButton->rect.y) {

				// if(activeBuildings.size==1){ THIS IS NOT NEEDED BECAUSE IF THERE ISN'T ONLY ONE, THE COLLIDER WOULD BE NULLPTR
				list<Entity*>::iterator buildingsToSpawnEntities = buildingsSelected.begin();
				(*buildingsToSpawnEntities)->SpawnEntity();

				isSomethingSelected = true;
			}
		}

		if (!isSomethingSelected) {

			bool controlWasPressed = false;

			if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
				controlWasPressed = true;

			list<Entity*>::iterator checkForSelectedEntities = activeEntities.begin();
			while (checkForSelectedEntities != activeEntities.end()) {
	
				if (
					//mouseMapCoordinates.x > (*checkForSelectedEntities)->pos.x - (*checkForSelectedEntities)->GetSize().x/* / 2 */&& mouseMapCoordinates.x < (*checkForSelectedEntities)->pos.x + (*checkForSelectedEntities)->GetSize().x/* / 2 */&&
					//mouseMapCoordinates.y > (*checkForSelectedEntities)->pos.y - (*checkForSelectedEntities)->GetSize().y/* / 2*/ && mouseMapCoordinates.y < (*checkForSelectedEntities)->pos.y + (*checkForSelectedEntities)->GetSize().y/* / 2*/
					mouseMapCoordinates.x < (*checkForSelectedEntities)->pos.x + (*checkForSelectedEntities)->GetSize().x && mouseMapCoordinates.x > (*checkForSelectedEntities)->pos.x &&
					mouseMapCoordinates.y < (*checkForSelectedEntities)->pos.y + (*checkForSelectedEntities)->GetSize().y && mouseMapCoordinates.y > (*checkForSelectedEntities)->pos.y
					
					) {

					if (!(*checkForSelectedEntities)->isSelected) {
						SelectEntity(*checkForSelectedEntities, controlWasPressed);
					}

					isSomethingSelected = true;

					break;

				}
				checkForSelectedEntities++;
			}
		}
		// Unselect all
		if (!isSomethingSelected) UnselectAllEntities();
	}

	// Show Building UI if ONLY ONE BUILDING is selected
	if (buildingsSelected.size() == 1) {

		list<Entity*>::iterator buildingToShowUI = buildingsSelected.begin();
		if ((*buildingToShowUI)->isSelected) {
			(*buildingToShowUI)->ShowUI();
		}

		else {
			spawnEntityUIButton = nullptr;
			spawnEntityUIButton->to_delete = true;
		}
	}

	else {
		if (spawnEntityUIButton != nullptr) {
			spawnEntityUIButton->to_delete = true;
			spawnEntityUIButton = nullptr;
		}
	}


	// LifeBars from selected  on HUD
	if (!entitiesSelected.empty()) {

		list<Entity*>::iterator selectedEntities = entitiesSelected.begin();
		currentLifeSum = 0;
		maxLifeSum = 0;

		while (selectedEntities != entitiesSelected.end()) {

			currentLifeSum += (*selectedEntities)->GetCurrLife();
			maxLifeSum += (*selectedEntities)->GetMaxLife();
			selectedEntities++;
		}

		float caca = (currentLifeSum / maxLifeSum) * 200;
		App->render->AddBlitEvent(1, zeroLifeTexture, App->win->width / 2 - 100, App->win->height - 100, { 0, 0, 200, 15 }, false, true, 0);
		App->render->AddBlitEvent(1, fullLifeTexture, App->win->width / 2 - 100, App->win->height - 100, { 0, 0, (int)caca, 15 }, false, true, 0);
		
	}

	// LifeBars from selected units on top of themselves
	list<Entity*>::iterator selectedUnits = unitsSelected.begin();
	while (selectedUnits != unitsSelected.end()) {

		(*selectedUnits)->ShowHealthBar();
		selectedUnits++;
	}

	// Change destination for units selected on right-click
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN && !unitsSelected.empty()) {

		int orderOfPriority = 0;
		list<Entity*>::iterator unitsToRedirect = unitsSelected.begin();

		while (unitsToRedirect != unitsSelected.end()) {

			if ((*unitsToRedirect)->isActive) {

				fPoint xy = App->input->GetMouseWorldPosition();
				iPoint cameraW = App->map->WorldToMap(App->render->camera.x, App->render->camera.y);
				iPoint map_coordinates = App->map->WorldToMap(xy.x - cameraW.x /*+ App->map->data.tile_width / 2*/, xy.y - cameraW.y + App->map->data.tile_height / 2);

				(*unitsToRedirect)->SetDestination(map_coordinates);
				(*unitsToRedirect)->CalculateMovementLogic(orderOfPriority);

				orderOfPriority++;
			}

			unitsToRedirect++;
		}
	}
	
	// Prepare Movement
	/*list<Entity*>::iterator unitsToPrepareMove = activeUnits.begin();
	while (unitsToPrepareMove != activeUnits.end()) {
		(*unitsToPrepareMove)->CalculateMovementLogic();

		unitsToPrepareMove++;
	}*/

	// Move
	list<Entity*>::iterator unitsToMove = activeUnits.begin();
	while (unitsToMove != activeUnits.end()) {

		if ((*unitsToMove)->isOnTheMove)
			(*unitsToMove)->Move(dt);

		unitsToMove++;
	}

	// Move colliders
	list<Entity*>::iterator collidersToMove = activeUnits.begin();
	while (collidersToMove != activeUnits.end()) {

		(*collidersToMove)->entityCollider->rect.x = (*collidersToMove)->pos.x/* - (*collidersToMove)->GetSize().x / 2*/;
		(*collidersToMove)->entityCollider->rect.y = (*collidersToMove)->pos.y/* - (*collidersToMove)->GetSize().y / 1.5*/;

		collidersToMove++;
	}

	// Draw all active entities
	list<Entity*>::iterator entitiesToDraw = activeEntities.begin();
	while (entitiesToDraw != activeEntities.end()) {

		if ((*entitiesToDraw)->isActive) {

			if ((*entitiesToDraw)->entityType == ENTITY_TYPE_TOWN_HALL) {
				(*entitiesToDraw)->Draw(townHallTexture);
			}
			else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_PAINTER) {
				(*entitiesToDraw)->Draw(painterTexture);
			}
			else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_WARRIOR) {
				(*entitiesToDraw)->Draw(warrior_Texture);
			}
			else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_SPAWNER) {
				(*entitiesToDraw)->Draw(spawnerTexture);
			}
			else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_SLIME) {
				(*entitiesToDraw)->Draw(slimeTexture);
			}
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

	if (warrior_Texture != nullptr)
		App->tex->UnLoad(warrior_Texture);

	if (slimeTexture != nullptr)
		App->tex->UnLoad(slimeTexture);

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

Entity* j1EntityManager::AddEntity(ENTITY_TYPE entityType, fPoint pos, j1Module* listener, Entity* creator, int damage,  bool spawnAutomatically) {

		// Allies
	/// Buildings
	if (entityType == ENTITY_TYPE_TOWN_HALL) {
		TownHall* townHall = new TownHall({ pos.x/* - size.x/2*/, pos.y/* - size.y/2 */}, damage, this);
		activeEntities.push_back((Entity*)townHall);
		activeBuildings.push_back((Entity*)townHall);

		return (Entity*)townHall;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_PAINTER) {
		Painter* painter = new Painter({ pos.x/* - size.x / 2*/, pos.y/* - size.y / 2 */}, damage, this, creator);
		activeEntities.push_back((Entity*)painter);
		activeUnits.push_back((Entity*)painter);

		return (Entity*)painter;
	}

	else if (entityType == ENTITY_TYPE_WARRIOR) {
		Warrior* warrior = new Warrior({ pos.x/* - size.x / 2*/, pos.y/* - size.y / 2 */}, damage, this, creator);

		if (spawnAutomatically) {
			activeEntities.push_back((Entity*)warrior);
			activeUnits.push_back((Entity*)warrior);
			warrior->isActive = true;
			warrior->CreateEntityCollider(pos);
		}

		else
			spawningEntities.push_back((Entity*)warrior);
	
		return (Entity*)warrior;
	}

		// Enemies
	/// Buildings
	if (entityType == ENTITY_TYPE_SPAWNER) {
		Spawner* spawner = new Spawner({ pos.x/* - size.x / 2*/, pos.y/* - size.y / 2*/ }, damage, this);
		activeEntities.push_back((Entity*)spawner);
		activeBuildings.push_back((Entity*)spawner);

		return (Entity*)spawner;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_SLIME) {
		Slime* slime = new Slime({ pos.x/* - size.x / 2*/, pos.y/* - size.y / 2*/ }, damage, this);
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

	if (!App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
		UnselectAllEntities();

	int entitiesForGroup = 0;

	list<Entity*>::iterator chechUnitsToSelect = activeUnits.begin();
	while (chechUnitsToSelect != activeUnits.end()) {
		if (rect.x < (*chechUnitsToSelect)->pos.x + (*chechUnitsToSelect)->GetSize().x &&
			rect.x + rect.w >(*chechUnitsToSelect)->pos.x &&
			rect.y < (*chechUnitsToSelect)->pos.y + (*chechUnitsToSelect)->GetSize().y &&
			rect.h + rect.y >(*chechUnitsToSelect)->pos.y) {

			entitiesForGroup++;

			if (entitiesForGroup < 10) { // This caps the maximum of units selected in a group to 9 so we can move them with ease
				unitsSelected.push_back((*chechUnitsToSelect));
				entitiesSelected.push_back((*chechUnitsToSelect));
				(*chechUnitsToSelect)->isSelected = true;
			}
		}
		chechUnitsToSelect++;
	}

	if (entitiesForGroup == 0)
		UnselectAllEntities();
}