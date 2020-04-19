#include "p2Log.h"

#include "j1Module.h"
#include "j1App.h"

#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "Scene.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "GameScene.h"
#include "j1Collision.h"
#include "j1Input.h"
#include "j1Player.h"
#include "j1Window.h"
#include "TransitionManager.h"
#include "Brofiler/Brofiler.h"
#include "Entity.h"
#include "Sprites.h"

//testing testing testing
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
	
	BROFILER_CATEGORY("Entity Manager Start--Entity Manager();", Profiler::Color::Blue);
	
	bool ret = true;

	debug_tex = App->tex->Load("maps/path2.png");

	// TODO: Initialize all textures

		// Allies
	/// Buildings
	townHallTexture = App->tex->Load("textures/TownHall.png");
	paintExtractorTexture = App->tex->Load("textures/PaintExtractor.png");
	woodProducerTexture = App->tex->Load("textures/WoodProducer.png");
	houseTexture = App->tex->Load("textures/House.png");
	barracksTexture = App->tex->Load("textures/Barracks.png");

	/// Units
	painterTexture = App->tex->Load("textures/Painter.png");	//TODO ELIMINAR
	warriorTexture = App->tex->Load("textures/Warrior.png");	//TODO ELIMINAR
	warrior_Texture = App->tex->Load("textures/Warrior_Sprite_Mod.png");
	painter_Texture = App->tex->Load("textures/spritesheet_painter_mod.png");

		// Enemies
	/// Buildings
	spawnerTexture = App->tex->Load("textures/Spawner.png");

	/// Units
	slimeTexture = App->tex->Load("textures/Slime.png");

	buildingTexture = App->tex->Load("textures/Building.png");

	fullLifeTexture = App->tex->Load("textures/FullLife.png");
	zeroLifeTexture = App->tex->Load("textures/ZeroLife.png");


	WarriorSprites();
	PainterSprites();

	return ret;
}

bool j1EntityManager::PreUpdate() {
	BROFILER_CATEGORY("Entity Manager PreUpdate--Entity Manager();", Profiler::Color::BlueViolet);
	bool ret = true;
	if (App->PAUSE_ACTIVE == false) {}

	// Update the currentTile to the actual pos
	list<Entity*>::iterator setDefaultAnimation = activeUnits.begin();
	while (setDefaultAnimation != activeUnits.end()) {

		if ((*setDefaultAnimation)->entityType == ENTITY_TYPE_WARRIOR) {
			(*setDefaultAnimation)->currentAnimation = &warriorIdle;
		}
		else if ((*setDefaultAnimation)->entityType == ENTITY_TYPE_PAINTER) {
			(*setDefaultAnimation)->currentAnimation = &painterIdle;
		}
		
		setDefaultAnimation++;
	}

	return ret;
}

bool j1EntityManager::Update(float dt) {
	BROFILER_CATEGORY("Entity Manager Update-Entity Manager();", Profiler::Color::CornflowerBlue);
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
					(*checkForSpawningEntities)->isAlive = true;

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
					(*checkForSpawningEntities)->isAlive = true;

					spawningEntities.erase(checkForSpawningEntities);
				}

				else if ((*checkForSpawningEntities)->constructionProgress * constructionRate < (*checkForSpawningEntities)->constructionTime) {
							
					App->render->AddBlitEvent(1, buildingTexture, (*checkForSpawningEntities)->pos.x, (*checkForSpawningEntities)->pos.y, { 0,0,(*checkForSpawningEntities)->GetSize().x,(*checkForSpawningEntities)->GetSize().y });
					(*checkForSpawningEntities)->constructionProgress += constructionRate * dt;
				}
			}

			checkForSpawningEntities++;

		}






		// We'll print the building hovering where it would be built

		if (isSelectingPlacement) { // Selecting Placement FOR A BUILDING

			fPoint mousePosition = App->input->GetMouseWorldPosition();
			iPoint cameraOffset = App->map->WorldToMap(App->render->camera.x, App->render->camera.y);
			iPoint mapCoordinates = App->map->WorldToMap(mousePosition.x - cameraOffset.x, mousePosition.y - cameraOffset.y + App->map->data.tile_height / 2);

			fPoint mapWorldCoordinates = App->map->MapToWorld(mapCoordinates.x, mapCoordinates.y);

			App->render->AddBlitEvent(1, debug_tex, mapWorldCoordinates.x, mapWorldCoordinates.y, { 0,0,150,75 });
			App->render->AddBlitEvent(1, debug_tex, mapWorldCoordinates.x - App->map->data.tile_width / 2, mapWorldCoordinates.y - App->map->data.tile_height / 2, { 0,0,150,75 });
			App->render->AddBlitEvent(1, debug_tex, mapWorldCoordinates.x + App->map->data.tile_width / 2, mapWorldCoordinates.y - App->map->data.tile_height / 2, { 0,0,150,75 });
			App->render->AddBlitEvent(1, debug_tex, mapWorldCoordinates.x, mapWorldCoordinates.y - App->map->data.tile_height, { 0,0,150,75 });

			
			if (hoveringEntityType == ENTITY_TYPE_PAINT_EXTRACTOR) {
				App->render->AddBlitEvent(1, paintExtractorTexture, mapWorldCoordinates.x - 125 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 250 + App->map->data.tile_height / 2, { 0,0,250,250 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_WOOD_PRODUCER) {
				App->render->AddBlitEvent(1, woodProducerTexture, mapWorldCoordinates.x - 75 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 200 + App->map->data.tile_height / 2, { 0,0,150,200 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_BARRACKS) {
				App->render->AddBlitEvent(1, barracksTexture, mapWorldCoordinates.x - 125 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 250 + App->map->data.tile_height / 2, { 0,0,250,250 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_HOUSE) {
				App->render->AddBlitEvent(1, houseTexture, mapWorldCoordinates.x - 75 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 200 + App->map->data.tile_height / 2, { 0,0,150,200 });
			}


			// If the Left click was pressed we'll check if it can in fact be built there
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {

				// The painter is not 1x1
				if (hoveringEntityType == ENTITY_TYPE_PAINT_EXTRACTOR) {

					if (App->pathfinding->IsPaint(mapCoordinates) || App->pathfinding->IsPaint({ mapCoordinates.x - 1, mapCoordinates.y - 1 }) ||
						App->pathfinding->IsPaint({ mapCoordinates.x, mapCoordinates.y - 1 }) || App->pathfinding->IsPaint({ mapCoordinates.x - 1, mapCoordinates.y })) {

						if (App->player->woodCount.count >= 20) {
							App->player->woodCount.count -= 20;
							isSelectingPlacement = false;

							AddEntity(ENTITY_TYPE_PAINT_EXTRACTOR, mapCoordinates, App->entities, nullptr, 0);
							hoveringEntityType == ENTITY_TYPE_NONE;
						}
					}
				}

				else if (hoveringEntityType == ENTITY_TYPE_WOOD_PRODUCER) {

					if (App->pathfinding->IsBuildable(mapCoordinates)) {

						if (App->player->paintCount.count >= 20) {
							isSelectingPlacement = false;
							App->player->paintCount.count -= 20;
							AddEntity(ENTITY_TYPE_WOOD_PRODUCER, mapCoordinates, App->entities, nullptr, 0);
							hoveringEntityType == ENTITY_TYPE_NONE;
						}
					}
				}

				else if (hoveringEntityType == ENTITY_TYPE_BARRACKS) {

					if (App->pathfinding->IsBuildable(mapCoordinates) && App->pathfinding->IsBuildable({ mapCoordinates.x - 1, mapCoordinates.y - 1 }) &&
						App->pathfinding->IsBuildable({ mapCoordinates.x, mapCoordinates.y - 1 }) && App->pathfinding->IsBuildable({ mapCoordinates.x - 1, mapCoordinates.y })) {

						if (App->player->woodCount.count >= 50) {
							isSelectingPlacement = false;
							App->player->woodCount.count -= 50;
							AddEntity(ENTITY_TYPE_BARRACKS, mapCoordinates, App->entities, nullptr, 0);
							hoveringEntityType == ENTITY_TYPE_NONE;
						}
					}
				}

				else if (hoveringEntityType == ENTITY_TYPE_HOUSE) {

					if (App->pathfinding->IsBuildable(mapCoordinates)) {

						if (App->player->woodCount.count >= 20) {
							isSelectingPlacement = false;
							App->player->woodCount.count -= 20;
							AddEntity(ENTITY_TYPE_HOUSE, mapCoordinates, App->entities, nullptr, 0);
							hoveringEntityType == ENTITY_TYPE_NONE;
						}
					}
				}
			}
		}

			
		




		// LifeBars from selected on HUD
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
		   App->entities->Entity_HP = w;
			/*App->render->AddBlitEventforUI(1, zeroLifeTexture, App->win->width / 2 - 100, App->win->height - 100, { 0, 0, 200, 15 }, false, true, 0);
			App->render->AddBlitEventforUI(1, fullLifeTexture, 100+ App->render->camera.x*-2 / 2 , App->win->height - 100, { 0, 0, (int)w, 15 }, false, true, 0);*/

		}




		// LifeBars from selected units on top of themselves
		list<Entity*>::iterator selectedUnits = unitsSelected.begin();
		while (selectedUnits != unitsSelected.end()) {

			(*selectedUnits)->ShowHealthBar();
			selectedUnits++;
		}




		// Extract Paint (Painters and PaintExtractor
		list<Entity*>::iterator entitiesToExtractPaint = activeEntities.begin();
		while (entitiesToExtractPaint != activeEntities.end()) {

			// We try to extract and it will return if it can't
			if ((*entitiesToExtractPaint)->entityType == ENTITY_TYPE_PAINTER || (*entitiesToExtractPaint)->entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {

				(*entitiesToExtractPaint)->ExtractPaint(dt);
			}
			entitiesToExtractPaint++;
		}

		// Extract Wood  (ONLY PAINTERS CAN)
		list<Entity*>::iterator paintersToExtractWood = activeUnits.begin();
		while (paintersToExtractWood != activeUnits.end()) {

			// We try to extract and it will return if it can't
			if ((*paintersToExtractWood)->entityType == ENTITY_TYPE_PAINTER) {

				(*paintersToExtractWood)->ExtractWood(dt);
			}
			paintersToExtractWood++;
		}




		// Attack Mode
		list<Entity*>::iterator unitsToFight = activeUnits.begin();
		while (unitsToFight != activeUnits.end()) {

			if ((*unitsToFight)->isEntityFromPlayer) {

				if ((*unitsToFight)->currentTile == (*unitsToFight)->destination) {
					
					int x_distance, y_distance;

					x_distance = (*unitsToFight)->currentTile.x - (*unitsToFight)->target.x;
					y_distance = (*unitsToFight)->currentTile.y - (*unitsToFight)->target.y;

					if (x_distance < 0)
						x_distance *= (-1);

					if (y_distance < 0)
						y_distance *= (-1);

					if (x_distance <= 1 && y_distance <= 1) {
						
						// If we should attack, we check to what
						list<Entity*>::iterator checkWhichSpawner = activeBuildings.begin();
						while (checkWhichSpawner != activeBuildings.end()) {

							if ((*checkWhichSpawner)->entityType == ENTITY_TYPE_SPAWNER) {

								fPoint targetWorldPos = App->map->MapToWorld((*unitsToFight)->target.x, (*unitsToFight)->target.y);
								//targetWorldPos.x -= App->map->data.tile_width;
								//targetWorldPos.y -= App->map->data.tile_height;

								fPoint spawnerCurrentTileWorld = App->map->MapToWorld((*checkWhichSpawner)->currentTile.x - 1, (*checkWhichSpawner)->currentTile.y - 1);

								if (targetWorldPos.x < spawnerCurrentTileWorld.x + (*checkWhichSpawner)->GetSize().x &&
									targetWorldPos.x + App->map->data.tile_width > spawnerCurrentTileWorld.x &&
									targetWorldPos.y < spawnerCurrentTileWorld.y + (*checkWhichSpawner)->GetSize().y &&
									App->map->data.tile_height + targetWorldPos.y > spawnerCurrentTileWorld.y) {

									(*unitsToFight)->Attack((*checkWhichSpawner), dt);
									/*
									(*unitsToFight)->currentAnimation = &warriorAttackingDIRECTION;
									comprobar orientación (OJO: previousOrientation no unitOrientation!!!


									Aqu?compruebas las 8 direcciones y les pones su animación



									*/
								}
							}
							checkWhichSpawner++;
						}

						
					}
				}
			}

			unitsToFight++;
		}




		// Change destination for units selected on right-click
		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN && !unitsSelected.empty()) {

			int orderOfPriority = 0;
			list<Entity*>::iterator unitsToRedirect = unitsSelected.begin();

			while (unitsToRedirect != unitsSelected.end()) {

				if ((*unitsToRedirect)->isAlive) {

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

			if ((*unitsToMove)->isOnTheMove) {

				(*unitsToMove)->MovementLogic();
				(*unitsToMove)->Move(dt);
			}

			unitsToMove++;
		}



		// Move colliders
		list<Entity*>::iterator collidersToMove = activeUnits.begin();
		while (collidersToMove != activeUnits.end()) {

			(*collidersToMove)->entityCollider->rect.x = (*collidersToMove)->pos.x/* - (*collidersToMove)->GetSize().x / 2*/;
			(*collidersToMove)->entityCollider->rect.y = (*collidersToMove)->pos.y/* - (*collidersToMove)->GetSize().y / 1.5*/;

			collidersToMove++;
		}

		std::list<Entity*>::iterator checkMovingAnimation = activeUnits.begin();
		while (checkMovingAnimation != activeUnits.end()) {

			if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_WARRIOR) {

				if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

					(*checkMovingAnimation)->currentAnimation = &warriorMovingNorth;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &warriorMovingNorthEast;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

					(*checkMovingAnimation)->currentAnimation = &warriorMovingEast;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &warriorMovingSouthEast;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

					(*checkMovingAnimation)->currentAnimation = &warriorMovingSouth;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &warriorMovingSouthWest;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

					(*checkMovingAnimation)->currentAnimation = &warriorMovingWest;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &warriorMovingNorthWest;
				}
			}

			else if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_PAINTER) {

				if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

					(*checkMovingAnimation)->currentAnimation = &painterMovingNorth;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &painterMovingNorthEast;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

					(*checkMovingAnimation)->currentAnimation = &painterMovingEast;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &painterMovingSouthEast;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

					(*checkMovingAnimation)->currentAnimation = &painterMovingSouth;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &painterMovingSouthWest;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

					(*checkMovingAnimation)->currentAnimation = &painterMovingWest;
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &painterMovingNorthWest;
				}
			}
			checkMovingAnimation++;
		}
	}



	//if (App->PAUSE_ACTIVE == true) {

		// Draw all active entities
		list<Entity*>::iterator entitiesToDraw = activeEntities.begin();
		while (entitiesToDraw != activeEntities.end()) {

			if ((*entitiesToDraw)->isAlive) {

				if ((*entitiesToDraw)->entityType == ENTITY_TYPE_TOWN_HALL) {
					(*entitiesToDraw)->Draw(townHallTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {
					(*entitiesToDraw)->Draw(paintExtractorTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_WOOD_PRODUCER) {
					(*entitiesToDraw)->Draw(woodProducerTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_HOUSE) {
					(*entitiesToDraw)->Draw(houseTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_BARRACKS) {
					(*entitiesToDraw)->Draw(barracksTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_PAINTER) {
					(*entitiesToDraw)->Draw(painter_Texture);
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
	BROFILER_CATEGORY("Entity Manager PostUpdate--Entity Manager();", Profiler::Color::DarkBlue);
	if (App->PAUSE_ACTIVE == false) {}

	bool ret = true;

	// --------------------------------------------------------------------------------------------------------- //
	//																											 //
	// Check if there was anything selected when LEFT MOUSE BUTTON was pressed and if not, unselect all entities //
	// If control was pressed as a unit was selected, the rest of selected units aren't unselected				 //
	//																											 //
	// --------------------------------------------------------------------------------------------------------- //



	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN) {

		if (isSelectingPlacement) {
			isSelectingPlacement = false;
		}
	}
	// If we are selcting a placement for a building and we try to select a place not fit to build it doesn't unselect the unit, VERY IMPORTANT!
	if (isSelectingPlacement)
		return ret;


	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {

		float x, y;
		App->input->GetMousePosition(x, y);
		fPoint mouseMapCoordinates = App->render->ScreenToWorld(x, y);

		fPoint mouseWorldCoordinates;
		App->input->GetMousePosition(mouseWorldCoordinates.x, mouseWorldCoordinates.y);

		bool isSomethingSelected = false;

		// We check if any units were selected
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


	list<Entity*>::iterator checkForDeadUnits = activeUnits.begin();
	while (checkForDeadUnits != activeUnits.end()) {

		if ((*checkForDeadUnits)->GetCurrLife() <= 0) {

			App->player->housingSpace.count--;
			activeUnits.erase(checkForDeadUnits);
		}
		checkForDeadUnits++;
	}

	list<Entity*>::iterator checkForDeadBuildings = activeBuildings.begin();
	while (checkForDeadBuildings != activeBuildings.end()) {

		if ((*checkForDeadBuildings)->GetCurrLife() <= 0) {

			activeBuildings.erase(checkForDeadBuildings);
		}
		checkForDeadBuildings++;
	}

	list<Entity*>::iterator checkForDeadEntities = activeEntities.begin();
	while (checkForDeadEntities != activeEntities.end()) {

		if ((*checkForDeadEntities)->GetCurrLife() <= 0) {

			(*checkForDeadEntities)->isAlive = false;
			activeEntities.erase(checkForDeadEntities);

			(*checkForDeadEntities)->~Entity();
		}
		checkForDeadEntities++;
	}

	return ret;
}

bool j1EntityManager::CleanUp() {
	BROFILER_CATEGORY("Entity Manager CleanUp--Entity Manager();", Profiler::Color::LightBlue);
	bool ret = true;

	App->tex->UnLoad(townHallTexture);
	App->tex->UnLoad(paintExtractorTexture);
	App->tex->UnLoad(woodProducerTexture);
	App->tex->UnLoad(houseTexture);
	App->tex->UnLoad(barracksTexture);
	App->tex->UnLoad(painterTexture);
	App->tex->UnLoad(warrior_Texture);
	App->tex->UnLoad(slimeTexture);

	App->tex->UnLoad(buildingTexture);

	App->tex->UnLoad(fullLifeTexture);
	App->tex->UnLoad(zeroLifeTexture);

	list<Entity*>::iterator destroyEntities = activeEntities.begin();
	while (destroyEntities != activeEntities.end()) {

		(*destroyEntities)->entityCollider->to_delete = true;
		delete (*destroyEntities);

		destroyEntities++;
	}

	activeEntities.clear();
	activeBuildings.clear();
	activeUnits.clear();
	entitiesSelected.clear();
	unitsSelected.clear();
	buildingsSelected.clear();
	
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

Entity* j1EntityManager::AddEntity(ENTITY_TYPE entityType, iPoint tile, j1Module* listener, Entity* creator, float damage,  bool spawnAutomatically) {
	
		// Allies
	/// Buildings
	if (entityType == ENTITY_TYPE_TOWN_HALL) {

		TownHall* townHall = new TownHall(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)townHall);
			activeBuildings.push_back((Entity*)townHall);
			townHall->isAlive = true;
			townHall->CreateEntityCollider(townHall->pos);
		}

		else
			spawningEntities.push_back((Entity*)townHall);

		// Change the walkability to non walkable
		App->pathfinding->ChangeWalkability(tile, false, townHall->entitySize);
	
		return (Entity*)townHall;
	}
	
	else if (entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {

		PaintExtractor* paintExtractor = new PaintExtractor(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)paintExtractor);
			activeBuildings.push_back((Entity*)paintExtractor);
			paintExtractor->isAlive = true;
			paintExtractor->CreateEntityCollider(paintExtractor->pos);
		}

		else
			spawningEntities.push_back((Entity*)paintExtractor);

		// Change the walkability to non walkable
		App->pathfinding->ChangeWalkability(tile, false, paintExtractor->entitySize);

		return (Entity*)paintExtractor;
	}

	else if (entityType == ENTITY_TYPE_WOOD_PRODUCER) {

		WoodProducer* woodProducer = new WoodProducer(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)woodProducer);
			activeBuildings.push_back((Entity*)woodProducer);
			woodProducer->isAlive = true;
			woodProducer->CreateEntityCollider(woodProducer->pos);
		}

		else
			spawningEntities.push_back((Entity*)woodProducer);

		// Change the walkability to non walkable
		App->pathfinding->ChangeWalkability(tile, false, woodProducer->entitySize);

		// Change to Wood the 4 directly adjacent tiles
		App->pathfinding->ChangeToWood(tile);

		return (Entity*)woodProducer;
	}

	else if (entityType == ENTITY_TYPE_HOUSE) {

		House* house = new House(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)house);
			activeBuildings.push_back((Entity*)house);
			house->isAlive = true;
			house->CreateEntityCollider(house->pos);
		}

		else
			spawningEntities.push_back((Entity*)house);

		// Change the walkability to non walkable
		App->pathfinding->ChangeWalkability(tile, false, house->entitySize);

		return (Entity*)house;
	}

	else if (entityType == ENTITY_TYPE_BARRACKS) {

		Barracks* barracks = new Barracks(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)barracks);
			activeBuildings.push_back((Entity*)barracks);
			barracks->isAlive = true;
			barracks->CreateEntityCollider(barracks->pos);
		}

		else
			spawningEntities.push_back((Entity*)barracks);

		// Change the walkability to non walkable
		App->pathfinding->ChangeWalkability(tile, false, barracks->entitySize);

		return (Entity*)barracks;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_PAINTER) {

		Painter* painter = new Painter(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)painter);
			activeUnits.push_back((Entity*)painter);
			painter->isAlive = true;
			painter->CreateEntityCollider(painter->pos);
		}

		else
			spawningEntities.push_back((Entity*)painter);

		return (Entity*)painter;
	}

	else if (entityType == ENTITY_TYPE_WARRIOR) {

		Warrior* warrior = new Warrior(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)warrior);
			activeUnits.push_back((Entity*)warrior);
			warrior->isAlive = true;
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

		// Change the walkability to non walkable
		App->pathfinding->ChangeToSpawner(tile);

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


	if (isVictory == false) {
		App->entities->CleanUp();
		App->transition_manager->CreateExpandingBars(SCENES::LOSE_SCENE, 0.5f, true);
	}

	else if(isVictory==true) {
		App->entities->CleanUp();
	   App->transition_manager->CreateExpandingBars(SCENES::WIN_SCENE, 0.5f, true);  //DOESNT WORK YET BECAUSE SPAWNERS NOT IMPLEMENTED
	}

}