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
	paintExtractorTexture = App->tex->Load("textures/PaintExtractor.png");

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
	if (App->PAUSE_ACTIVE == false) {}

	list<Entity*>::iterator updateCurrentTile = activeUnits.begin();
	while (updateCurrentTile != activeUnits.end()) {

		iPoint mapPosition = App->map->WorldToMap((*updateCurrentTile)->pos.x - App->map->data.tile_width / 2 + (*updateCurrentTile)->GetSize().x / 2, (*updateCurrentTile)->pos.y - App->map->data.tile_height / 2 + (*updateCurrentTile)->GetSize().y);
		(*updateCurrentTile)->currentTile.x = mapPosition.x + 1;
		(*updateCurrentTile)->currentTile.y = mapPosition.y;

		updateCurrentTile++;
	}

	return ret;
}

bool j1EntityManager::Update(float dt) {
	
	bool ret = true;

	if (App->PAUSE_ACTIVE == false) {

		// Spawn entities that finished their spawning time
		list<Entity*>::iterator checkForSpawningEntities = spawningEntities.begin();
		while (checkForSpawningEntities != spawningEntities.end()) {

			// The units first
			if ((*checkForSpawningEntities)->entityCategory == ENTITY_CATEGORY_DYNAMIC_ENTITY) {

				// Check if they have to be spawned
				if ((*checkForSpawningEntities)->spawningProgress * spawningRate >= (*checkForSpawningEntities)->spawningTime) {

					activeUnits.push_back(*checkForSpawningEntities);
					activeEntities.push_back(*checkForSpawningEntities);

					(*checkForSpawningEntities)->CreateEntityCollider((*checkForSpawningEntities)->pos);
					(*checkForSpawningEntities)->spawnedBy->isSpawningAUnit = false;
					(*checkForSpawningEntities)->isActive = true;

					spawningEntities.erase(checkForSpawningEntities);
				}

				// Increase the creation progress if not
				else if ((*checkForSpawningEntities)->spawningProgress * spawningRate < (*checkForSpawningEntities)->spawningTime) {

					(*checkForSpawningEntities)->spawningProgress += spawningRate * dt;
				}
			}

			else if ((*checkForSpawningEntities)->entityCategory == ENTITY_CATEGORY_STATIC_ENTITY) {

				if ((*checkForSpawningEntities)->constructionProgress * constructionRate >= (*checkForSpawningEntities)->constructionTime) {

					activeBuildings.push_back(*checkForSpawningEntities);
					activeEntities.push_back(*checkForSpawningEntities);

					(*checkForSpawningEntities)->CreateEntityCollider((*checkForSpawningEntities)->pos);
					(*checkForSpawningEntities)->spawnedBy->isBuildingSomething = false;
					(*checkForSpawningEntities)->isActive = true;

					spawningEntities.erase(checkForSpawningEntities);
				}

				else if ((*checkForSpawningEntities)->constructionProgress * constructionRate < (*checkForSpawningEntities)->constructionTime) {

					(*checkForSpawningEntities)->constructionProgress += constructionRate * dt;
				}
			}

			checkForSpawningEntities++;

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




		// If there are only painters selected, show building UI
		bool onlyPaintersSelected = false;
		list<Entity*>::iterator paintersSelected = unitsSelected.begin();
		while (paintersSelected != unitsSelected.end()) {

			if ((*paintersSelected)->entityType == ENTITY_TYPE_PAINTER)
				onlyPaintersSelected = true;

			else
				onlyPaintersSelected = false;

			paintersSelected++;
		}

		if (onlyPaintersSelected) {
			paintersSelected = unitsSelected.begin();
			//while (paintersSelected != unitsSelected.end()) { FOR NOW, WE'LL LET ONLY THE FIRST ONE TO BUILD

			(*paintersSelected)->ShowUI();

			//	paintersSelected++;
			//}
		}

		// We'll print the townhall hovering where it would be built
		paintersSelected = unitsSelected.begin();
		while (paintersSelected != unitsSelected.end()) {

			if ((*paintersSelected)->isSelectingPlacement) {

				fPoint mousePosition = App->input->GetMouseWorldPosition();
				iPoint cameraOffset = App->map->WorldToMap(App->render->camera.x, App->render->camera.y);
				iPoint mapCoordinates = App->map->WorldToMap(mousePosition.x - cameraOffset.x, mousePosition.y - cameraOffset.y + App->map->data.tile_height / 2);
				fPoint mapWorldCoordinates = App->map->MapToWorld(mapCoordinates.x, mapCoordinates.y);

				App->render->AddBlitEvent(1, paintExtractorTexture, mapWorldCoordinates.x, mapWorldCoordinates.y, { 0,0,150,150 });

				// If the Left click was pressed we'll check if it can in fact be built there
				if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {

					if (App->pathfinding->IsPaint(mapCoordinates) || App->pathfinding->IsPaint({ mapCoordinates.x - 1, mapCoordinates.y - 1 })) {
						
						(*paintersSelected)->SpawnEntity(mapCoordinates);
					}
				}
			}

			paintersSelected++;
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

			float w = (currentLifeSum / maxLifeSum) * 200;
			App->render->AddBlitEvent(1, zeroLifeTexture, App->win->width / 2 - 100, App->win->height - 100, { 0, 0, 200, 15 }, false, true, 0);
			App->render->AddBlitEvent(1, fullLifeTexture, App->win->width / 2 - 100, App->win->height - 100, { 0, 0, (int)w, 15 }, false, true, 0);

		}




		// LifeBars from selected units on top of themselves
		list<Entity*>::iterator selectedUnits = unitsSelected.begin();
		while (selectedUnits != unitsSelected.end()) {

			(*selectedUnits)->ShowHealthBar();
			selectedUnits++;
		}




		// Extract Paint
		list<Entity*>::iterator paintersToExtract = activeEntities.begin();
		while (paintersToExtract != activeEntities.end()) {

			// We try to extract and it will return if it can't
			if ((*paintersToExtract)->entityType == ENTITY_TYPE_PAINTER || (*paintersToExtract)->entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {

				(*paintersToExtract)->ExtractPaint(dt);
			}
			paintersToExtract++;
		}




		// Change destination for units selected on right-click
		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN && !unitsSelected.empty()) {

			int orderOfPriority = 0;
			list<Entity*>::iterator unitsToRedirect = unitsSelected.begin();

			while (unitsToRedirect != unitsSelected.end()) {

				if ((*unitsToRedirect)->isActive) {

					fPoint xy = App->input->GetMouseWorldPosition();
					iPoint cameraW = App->map->WorldToMap(App->render->camera.x, App->render->camera.y);
					iPoint mapCoordinates = App->map->WorldToMap(xy.x - cameraW.x, xy.y - cameraW.y + App->map->data.tile_height / 2);

					(*unitsToRedirect)->SetDestination(mapCoordinates);
					(*unitsToRedirect)->CalculateMovementLogic(orderOfPriority);

					orderOfPriority++;
				}

				unitsToRedirect++;
			}
		}

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
	}

	//if (App->PAUSE_ACTIVE == true) {

		// Draw all active entities
		list<Entity*>::iterator entitiesToDraw = activeEntities.begin();
		while (entitiesToDraw != activeEntities.end()) {

			if ((*entitiesToDraw)->isActive) {

				if ((*entitiesToDraw)->entityType == ENTITY_TYPE_TOWN_HALL) {
					(*entitiesToDraw)->Draw(townHallTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {
					(*entitiesToDraw)->Draw(paintExtractorTexture);
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

			//	}
		}

	return ret;
}

bool j1EntityManager::PostUpdate() {

	if (App->PAUSE_ACTIVE == false) {}

	bool ret = true;


	// WIN CONDITION
	bool anySpawnerActive = false;
	list<Entity*>::const_iterator checkForSpawners = activeBuildings.begin();
	while (checkForSpawners != activeBuildings.end()) {

		if ((*checkForSpawners)->entityType == ENTITY_TYPE_SPAWNER) {
			anySpawnerActive = true;
			break;
		}
		checkForSpawners++;
	}
	if (!anySpawnerActive)
		TriggerEndGame(true);

	// LOSE CONDITION
	bool anyTownhallActive = false;
	list<Entity*>::const_iterator checkForTownhalls = activeBuildings.begin();
	while (checkForTownhalls != activeBuildings.end()) {

		if ((*checkForTownhalls)->entityType == ENTITY_TYPE_TOWN_HALL) {
			anyTownhallActive = true;
			break;
		}
		checkForTownhalls++;
	}
	if (!anyTownhallActive)
		TriggerEndGame(false);




	// --------------------------------------------------------------------------------------------------------- //
	//																											 //
	// Check if there was anything selected when LEFT MOUSE BUTTON was pressed and if not, unselect all entities //
	// If control was pressed as a unit was selected, the rest of selected units aren't unselected				 //
	//																											 //
	// --------------------------------------------------------------------------------------------------------- //
	if (unitsSelected.size() > 0) {
		list<Entity*>::iterator unitsToBuildEntities = unitsSelected.begin();

		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN) {

			if ((*unitsToBuildEntities)->isSelectingPlacement) {
				(*unitsToBuildEntities)->isSelectingPlacement = false;
			}
		}
		// If we are selcting a placement for a building and we try to select a place not fit to build it doesn't unselect the unit, VERY IMPORTANT!
		if ((*unitsToBuildEntities)->isSelectingPlacement)
			return ret;
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {

		bool isSomethingSelected = false;

		float x, y;
		App->input->GetMousePosition(x, y);
		fPoint mouseMapCoordinates = App->render->ScreenToWorld(x, y);

		fPoint mouseWorldCoordinates;
		App->input->GetMousePosition(mouseWorldCoordinates.x, mouseWorldCoordinates.y);

		// First we check if a button was pressed
		if (spawnEntityUIButton != nullptr) {

			if (mouseWorldCoordinates.x < spawnEntityUIButton->rect.x + spawnEntityUIButton->rect.w && mouseWorldCoordinates.x > spawnEntityUIButton->rect.x &&
				mouseWorldCoordinates.y < spawnEntityUIButton->rect.y + spawnEntityUIButton->rect.h && mouseWorldCoordinates.y > spawnEntityUIButton->rect.y) {

				// if(activeBuildings.size==1){ THIS IS NOT NEEDED BECAUSE IF THERE ISN'T ONLY ONE, THE COLLIDER WOULD BE NULLPTR
				list<Entity*>::iterator buildingsToSpawnEntities = buildingsSelected.begin();
				(*buildingsToSpawnEntities)->SpawnEntity({ 0,0 });

				isSomethingSelected = true;
			}
		}
		else if (buildEntityUIButton != nullptr) {

			if (mouseWorldCoordinates.x < buildEntityUIButton->rect.x + buildEntityUIButton->rect.w && mouseWorldCoordinates.x > buildEntityUIButton->rect.x &&
				mouseWorldCoordinates.y < buildEntityUIButton->rect.y + buildEntityUIButton->rect.h && mouseWorldCoordinates.y > buildEntityUIButton->rect.y) {

				// For now only one
				list<Entity*>::iterator unitsToBuildEntities = unitsSelected.begin();

				if (!(*unitsToBuildEntities)->isSelectingPlacement)
					(*unitsToBuildEntities)->isSelectingPlacement = true;

				isSomethingSelected = true;
			}
		}

		// If not, we check if any units were selected
		if (!isSomethingSelected) {

			bool controlWasPressed = false;

			if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
				controlWasPressed = true;

			list<Entity*>::iterator checkForSelectedEntities = activeEntities.begin();
			while (checkForSelectedEntities != activeEntities.end()) {

				if (mouseMapCoordinates.x < (*checkForSelectedEntities)->pos.x + (*checkForSelectedEntities)->GetSize().x && mouseMapCoordinates.x >(*checkForSelectedEntities)->pos.x &&
					mouseMapCoordinates.y < (*checkForSelectedEntities)->pos.y + (*checkForSelectedEntities)->GetSize().y && mouseMapCoordinates.y >(*checkForSelectedEntities)->pos.y) {

					if (!(*checkForSelectedEntities)->isSelected)
						SelectEntity(*checkForSelectedEntities, controlWasPressed);

					isSomethingSelected = true;

					break;
				}
				checkForSelectedEntities++;
			}
		}


		// And if not, unselect all
		if (!isSomethingSelected)
			UnselectAllEntities();
	}

	return ret;
}

bool j1EntityManager::CleanUp() {
	bool ret = true;

	if (townHallTexture != nullptr)
		App->tex->UnLoad(townHallTexture);

	if (paintExtractorTexture != nullptr)
		App->tex->UnLoad(paintExtractorTexture);

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

Entity* j1EntityManager::AddEntity(ENTITY_TYPE entityType, iPoint tile, j1Module* listener, Entity* creator, int damage,  bool spawnAutomatically) {

		// Allies
	/// Buildings
	if (entityType == ENTITY_TYPE_TOWN_HALL) {
		TownHall* townHall = new TownHall(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)townHall);
			activeBuildings.push_back((Entity*)townHall);
			townHall->isActive = true;
			townHall->CreateEntityCollider(townHall->pos);
		}

		else
			spawningEntities.push_back((Entity*)townHall);

		return (Entity*)townHall;
	}
	
	else if (entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {
		PaintExtractor* paintExtractor = new PaintExtractor(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)paintExtractor);
			activeBuildings.push_back((Entity*)paintExtractor);
			paintExtractor->isActive = true;
			paintExtractor->CreateEntityCollider(paintExtractor->pos);
		}

		else
			spawningEntities.push_back((Entity*)paintExtractor);

		// Change the walkability to non walkable
		App->pathfinding->ChangeWalkability(tile, false);
		App->pathfinding->ChangeWalkability({ tile.x - 1,tile.y - 1 }, false);

		return (Entity*)paintExtractor;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_PAINTER) {
		Painter* painter = new Painter(tile, damage, this, creator);
		activeEntities.push_back((Entity*)painter);
		activeUnits.push_back((Entity*)painter);

		return (Entity*)painter;
	}

	else if (entityType == ENTITY_TYPE_WARRIOR) {
		Warrior* warrior = new Warrior(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)warrior);
			activeUnits.push_back((Entity*)warrior);
			warrior->isActive = true;
			warrior->CreateEntityCollider(warrior->pos);
		}

		else
			spawningEntities.push_back((Entity*)warrior);
	
		return (Entity*)warrior;
	}

		// Enemies
	/// Buildings
	if (entityType == ENTITY_TYPE_SPAWNER) {
		Spawner* spawner = new Spawner(tile, damage, this);
		activeEntities.push_back((Entity*)spawner);
		activeBuildings.push_back((Entity*)spawner);

		return (Entity*)spawner;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_SLIME) {
		Slime* slime = new Slime(tile, damage, this);
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

void j1EntityManager::TriggerEndGame(bool isVictory) {

}