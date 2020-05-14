#include "p2Log.h"

#include "j1Module.h"
#include "j1App.h"
#include "j1Audio.h"
#include "SDL_mixer/include/SDL_mixer.h"
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
#include "j1UI_Manager.h"

//testing testing testing
j1EntityManager::j1EntityManager()
{
	name = ("entities");
}

// Destructor
j1EntityManager::~j1EntityManager() {}

bool j1EntityManager::Awake(pugi::xml_node& config) {
	bool ret = true;
	EntityTexturesAreLoaded = false;
	return ret;
}

bool j1EntityManager::Start() {
	
	BROFILER_CATEGORY("Entity Manager Start--Entity Manager();", Profiler::Color::Blue);
	//AS ENTITY MANAGER DOESNT GET REMOVED WHEN CLEANUP (THE MODULE ITSELF) IT WONT ACCES START AGAIN BECAUSE IT NEVER CLOSED......
	bool ret = true;
	LoadEntityTextures(); //I MOVED EVERYTHING IN START TO A FUNCTION WHILE START IS NOT FIXED
	

	return ret;
}

bool j1EntityManager::PreUpdate() {
	BROFILER_CATEGORY("Entity Manager PreUpdate--Entity Manager();", Profiler::Color::BlueViolet);
	bool ret = true;

	/*if (EntityTexturesAreLoaded == false) {
		EntityTexturesAreLoaded = true;
		LoadEntityTextures();
	}*/

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
		// TODO: knights
		
		setDefaultAnimation++;
	}


		/// Reset destinations list
	// First we clear the list
	destinations.clear();

	// Then we fill it again, this time with only the ones we want to take into account
	list<Entity*>::iterator resetDestinations = activeUnits.begin();
	while (resetDestinations != activeUnits.end()) {

		if ((*resetDestinations)->destination != (*resetDestinations)->currentTile) {
			if((*resetDestinations)->isOnTheMove)
				destinations.push_back((*resetDestinations)->destination);
		}

		resetDestinations++;
	}

	list<Entity*>::iterator updatingTargets = activeUnits.begin();
	while (updatingTargets != activeUnits.end()) {

		// Only interested in the ones who have a target
		if ((*updatingTargets)->target != nullptr) {

			// If the target is a unit
			if ((*updatingTargets)->target->entityCategory == ENTITY_CATEGORY_DYNAMIC_ENTITY) {
				(*updatingTargets)->target_rect = { (*updatingTargets)->target->currentTile.x, (*updatingTargets)->target->currentTile.y, 1, 1 };
			}

			// If not, it will be a spawner
			else {
				(*updatingTargets)->target_rect = { (*updatingTargets)->target->currentTile.x, (*updatingTargets)->target->currentTile.y, 2, 2 };
			}
		}

		updatingTargets++;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		spacePressed = true;
	else
		spacePressed = false;
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
				if ((*checkForSpawningEntities)->spawningProgress >= (*checkForSpawningEntities)->spawningTime) {

					activeUnits.push_back(*checkForSpawningEntities);
					activeEntities.push_back(*checkForSpawningEntities);

					(*checkForSpawningEntities)->CreateEntityCollider((*checkForSpawningEntities)->pos, (*checkForSpawningEntities));
					(*checkForSpawningEntities)->spawnedBy->isSpawningAUnit = false;
					(*checkForSpawningEntities)->isAlive = true;


					if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_PAINTER)
						(*checkForSpawningEntities)->currentAnimation = &painterIdle;

					else if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_WARRIOR)
						(*checkForSpawningEntities)->currentAnimation = &warriorIdle;


					spawningEntities.erase(checkForSpawningEntities);
				}

				// Increase the creation progress if not
				else if ((*checkForSpawningEntities)->spawningProgress < (*checkForSpawningEntities)->spawningTime) {

					(*checkForSpawningEntities)->spawningProgress += spawningRate * dt;
				}
			}

			else if ((*checkForSpawningEntities)->entityCategory == ENTITY_CATEGORY_STATIC_ENTITY) {

				if ((*checkForSpawningEntities)->constructionProgress >= (*checkForSpawningEntities)->constructionTime) {

					activeBuildings.push_back(*checkForSpawningEntities);
					activeEntities.push_back(*checkForSpawningEntities);

					(*checkForSpawningEntities)->CreateEntityCollider((*checkForSpawningEntities)->pos, (*checkForSpawningEntities));
					(*checkForSpawningEntities)->isAlive = true;

					if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_HOUSE)
						App->player->housingSpace.maxCount += 5;

					spawningEntities.erase(checkForSpawningEntities);
				}

				else if ((*checkForSpawningEntities)->constructionProgress < (*checkForSpawningEntities)->constructionTime) {

					fPoint tileWorld = App->map->MapToWorld((*checkForSpawningEntities)->currentTile.x, (*checkForSpawningEntities)->currentTile.y);

					if ((*checkForSpawningEntities)->entitySize == ENTITY_SIZE_SMALL) {
						
						App->render->RenderQueueUI(1, buildingTexture, (*checkForSpawningEntities)->pos.x, (*checkForSpawningEntities)->pos.y, { 0,0,150,150 });
					}

					else if ((*checkForSpawningEntities)->entitySize == ENTITY_SIZE_MEDIUM) {

						App->render->RenderQueueUI(1, buildingTexture, (*checkForSpawningEntities)->pos.x, (*checkForSpawningEntities)->pos.y, { 0,0,260,260 });
					}

					else if ((*checkForSpawningEntities)->entitySize == ENTITY_SIZE_BIG) {

						App->render->RenderQueueUI(1, buildingTexture, (*checkForSpawningEntities)->pos.x, (*checkForSpawningEntities)->pos.y, { 0,0,410,410 });
					}
					
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

			//App->render->RenderQueue(1, debug_tex, mapWorldCoordinates.x, mapWorldCoordinates.y, { 0,0,150,75 });
			//App->render->RenderQueue(1, debug_tex, mapWorldCoordinates.x - App->map->data.tile_width / 2, mapWorldCoordinates.y - App->map->data.tile_height / 2, { 0,0,150,75 });
			//App->render->RenderQueue(1, debug_tex, mapWorldCoordinates.x + App->map->data.tile_width / 2, mapWorldCoordinates.y - App->map->data.tile_height / 2, { 0,0,150,75 });
			//App->render->RenderQueue(1, debug_tex, mapWorldCoordinates.x, mapWorldCoordinates.y - App->map->data.tile_height, { 0,0,150,75 });
			
			
			if (hoveringEntityType == ENTITY_TYPE_PAINT_EXTRACTOR) {
				App->render->RenderQueue(1, paintExtractorTexture, mapWorldCoordinates.x - 125 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 250 + App->map->data.tile_height / 2, { 0,0,250,250 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_WOOD_PRODUCER) {
				App->render->RenderQueue(1, woodProducerTexture, mapWorldCoordinates.x - 75 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 200 + App->map->data.tile_height / 2, { 0,0,150,200 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_BARRACKS) {
				App->render->RenderQueue(1, barracksTexture, mapWorldCoordinates.x - 125 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 250 + App->map->data.tile_height / 2, { 0,0,250,250 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_HOUSE) {
				App->render->RenderQueue(1, houseTexture, mapWorldCoordinates.x - 200 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 400 + App->map->data.tile_height / 2, { 0,0,400,400 });
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
							ExtractorQuestDone = true;
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
		   Entity_HP = w;
			

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
		//list<Entity*>::iterator unitsToFight = activeUnits.begin();
		//while (unitsToFight != activeUnits.end()) {

		//	if ((*unitsToFight)->isEntityFromPlayer) {

		//		if ((*unitsToFight)->currentTile == (*unitsToFight)->destination) {
		//			
		//			int x_distance, y_distance;

		//			x_distance = (*unitsToFight)->currentTile.x - (*unitsToFight)->target.x;
		//			y_distance = (*unitsToFight)->currentTile.y - (*unitsToFight)->target.y;

		//			if (x_distance < 0)
		//				x_distance *= (-1);

		//			if (y_distance < 0)
		//				y_distance *= (-1);

		//			if (x_distance <= 1 && y_distance <= 1) {
		//				
		//				// If we should attack, we check to what
		//				list<Entity*>::iterator checkWhichSpawner = activeBuildings.begin();
		//				while (checkWhichSpawner != activeBuildings.end()) {

		//					if ((*checkWhichSpawner)->entityType == ENTITY_TYPE_SPAWNER) {

		//						fPoint targetWorldPos = App->map->MapToWorld((*unitsToFight)->target.x, (*unitsToFight)->target.y);
		//						//targetWorldPos.x -= App->map->data.tile_width;
		//						//targetWorldPos.y -= App->map->data.tile_height;

		//						fPoint spawnerCurrentTileWorld = App->map->MapToWorld((*checkWhichSpawner)->currentTile.x - 1, (*checkWhichSpawner)->currentTile.y - 1);

		//						if (targetWorldPos.x < spawnerCurrentTileWorld.x + (*checkWhichSpawner)->GetSize().x &&
		//							targetWorldPos.x + App->map->data.tile_width > spawnerCurrentTileWorld.x &&
		//							targetWorldPos.y < spawnerCurrentTileWorld.y + (*checkWhichSpawner)->GetSize().y &&
		//							App->map->data.tile_height + targetWorldPos.y > spawnerCurrentTileWorld.y) {

		//							(*unitsToFight)->Attack((*checkWhichSpawner), dt);
		//							/*
		//							(*unitsToFight)->currentAnimation = &warriorAttackingDIRECTION;
		//							comprobar orientación (OJO: previousOrientation no unitOrientation!!!


		//							Aqu?compruebas las 8 direcciones y les pones su animación */

		//							std::list<Entity*>::iterator checkAttackAnimation = activeUnits.begin();
		//							while (checkAttackAnimation != activeUnits.end()) {

		//								if ((*checkAttackAnimation)->entityType == ENTITY_TYPE_WARRIOR) {

		//									if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_NORTH) {

		//										(*checkAttackAnimation)->currentAnimation = &warriorAttackNorth;
		//									}

		//									else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_NORTH_EAST) {

		//										(*checkAttackAnimation)->currentAnimation = &warriorAttackNorthEast;
		//									}

		//									else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_EAST) {

		//										(*checkAttackAnimation)->currentAnimation = &warriorAttackEast;
		//									}

		//									else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

		//										(*checkAttackAnimation)->currentAnimation = &warriorAttackSouthEast;
		//									}

		//									else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_SOUTH) {

		//										(*checkAttackAnimation)->currentAnimation = &warriorAttackSouth;
		//									}

		//									else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

		//										(*checkAttackAnimation)->currentAnimation = &warriorAttackSouthWest;
		//									}

		//									else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_WEST) {

		//										(*checkAttackAnimation)->currentAnimation = &warriorAttackWest;
		//									}

		//									else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_NORTH_WEST) {

		//										(*checkAttackAnimation)->currentAnimation = &warriorAttackNorthWest;
		//									}
		//								}
		//								checkAttackAnimation++;
		//							}
		//						}
		//					}

		//					checkWhichSpawner++;
		//				}
		//			}
		//		}
		//	}

		//	unitsToFight++;
		//}




		// Change destination for units selected on right-click
		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN && !unitsSelected.empty()) {

			fPoint mouseWorldPosition = App->input->GetMouseWorldPosition();

			bool attacking = false;

			list<Entity*>::iterator subjects = unitsSelected.begin();

			list<Entity*>::iterator checkForAttackedEntities = activeEntities.begin();
			while (checkForAttackedEntities != activeEntities.end()) {

				if (!(*checkForAttackedEntities)->isEntityFromPlayer) {

					if (mouseWorldPosition.x < (*checkForAttackedEntities)->pos.x + (*checkForAttackedEntities)->GetSize().x && mouseWorldPosition.x >(*checkForAttackedEntities)->pos.x &&
						mouseWorldPosition.y < (*checkForAttackedEntities)->pos.y + (*checkForAttackedEntities)->GetSize().y && mouseWorldPosition.y >(*checkForAttackedEntities)->pos.y) {

						while (subjects != unitsSelected.end()) {

							(*subjects)->target = (*checkForAttackedEntities);
							subjects++;
						}
						attacking = true;
						break;
					}
				}

				checkForAttackedEntities++;
			}
				
			
			if (attacking) {

				
			}
			else {
				list<Entity*>::iterator unitsToRedirect = unitsSelected.begin();
				while (unitsToRedirect != unitsSelected.end()) {

					if ((*unitsToRedirect)->isAlive) {

						// We get the mouse's position
						iPoint cameraW = App->map->WorldToMap(App->render->camera.x, App->render->camera.y);
						iPoint mapCoordinates = App->map->WorldToMap(mouseWorldPosition.x - cameraW.x, mouseWorldPosition.y - cameraW.y + App->map->data.tile_height / 2);

						// We'll leave the mapCoordinates unaltered just in case
						iPoint destination = mapCoordinates;

						// This will dictate whether or not we can send the unit there
						bool locationAvailable = true;

						// We'll cicle throw all OTHER units
						list<Entity*>::iterator someoneElse = activeUnits.begin();
						while (someoneElse != activeUnits.end()) {

							if ((*someoneElse) != (*unitsToRedirect)) {

								// We can't send someone to where there's another unit
								if (destination == (*someoneElse)->currentTile && !(*someoneElse)->isOnTheMove) {
									locationAvailable = false;
									break;
								}
							}

							someoneElse++;
						}

						// We'll check if this possibleDestination is included in the destinations list
						list<iPoint>::iterator destinationsList = destinations.begin();
						while (destinationsList != destinations.end()) {

							// If it is, there's no need to keep searching, we'll just exit it and try another one
							if (destination == (*destinationsList)) {
								locationAvailable = false;
								break;
							}
							else {
								locationAvailable = true;
							}
							destinationsList++;
						}

						// And we can't send someone to where someone else is already going
						if (!locationAvailable) {

							int i = 0;
							iPoint possibleDestination;

							// If true, we'll continue the loop until reaching the safety check
							bool continueLoop = true;

							while (continueLoop) {

								// Safety check so we don't have an infinte loop
								if (i > App->pathfinding->FindClosestDestination(mapCoordinates).size() - 1) {
									break;
								}

								// Let's try an adjacent tile
								possibleDestination = App->pathfinding->FindClosestDestination(mapCoordinates).at(i);

								// We'll check if this possibleDestination is included in the destinations list
								list<iPoint>::iterator destinationsList = destinations.begin();
								while (destinationsList != destinations.end()) {

									// If it is, there's no need to keep searching, we'll just exit it and try another one
									if (possibleDestination == (*destinationsList)) {
										continueLoop = true;
										locationAvailable = false;
										break;
									}
									else {
										destination = possibleDestination;
										locationAvailable = true;
										continueLoop = false;
									}
									destinationsList++;
								}

								i++;
							}
						}





						if (locationAvailable) {
							(*unitsToRedirect)->SetDestination(destination);
							destinations.push_back(destination);
							(*unitsToRedirect)->CalculateMovementLogic(0);
						}

					}

					unitsToRedirect++;
				}
			}
		}



		// Attacking Logic
		list<Entity*>::iterator unitsToAttackLogic = activeUnits.begin();
		while (unitsToAttackLogic != activeUnits.end()) {

			// First, we will get the units that need to AttackLogic
			if ((*unitsToAttackLogic)->target != nullptr) {

				// Checking if the unit is range to attack
				// If it's in range, attack
				if (App->pathfinding->DistanceTo((*unitsToAttackLogic)->currentTile, (*unitsToAttackLogic)->target->currentTile) <= (*unitsToAttackLogic)->attackRadius) {

					(*unitsToAttackLogic)->Attack((*unitsToAttackLogic)->target, dt);
				}

				// If not, move closer and we'll continue to check until it can attack
				else {

				}
			}

			unitsToAttackLogic++;
		}




		// Move
		list<Entity*>::iterator unitsToMove = activeUnits.begin();
		while (unitsToMove != activeUnits.end()) {

			if ((*unitsToMove)->isOnTheMove) {

				(*unitsToMove)->MovementLogic();
			}

			// Checked twice beacuse MovementLogic() can change it
			if ((*unitsToMove)->isOnTheMove) {

				(*unitsToMove)->Move(dt);
			}

			unitsToMove++;
		}



		// Move colliders
		list<Entity*>::iterator collidersToMove = activeUnits.begin();
		while (collidersToMove != activeUnits.end()) {

			(*collidersToMove)->entityCollider->rect.x = (*collidersToMove)->pos.x;
			(*collidersToMove)->entityCollider->rect.y = (*collidersToMove)->pos.y;

			collidersToMove++;
		}






		// Update the animations for the units
		UpdateAnimations();






		// Kill first selected unit on SUPR press
		if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN) {

			if (!unitsSelected.empty()) {

				list<Entity*>::iterator unitsToKill = unitsSelected.begin();
				(*unitsToKill)->isAlive = false;
				unitsSelected.erase(unitsToKill);
			}
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
					(*entitiesToDraw)->Draw(painterTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_WARRIOR) {
					(*entitiesToDraw)->Draw(warriorTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_KNIGHT) {
					(*entitiesToDraw)->Draw(knightTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_EXPLORER) {
					(*entitiesToDraw)->Draw(explorerTexture);
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




		// LifeBars from selected units on top of themselves
		list<Entity*>::iterator selectedUnits = unitsSelected.begin();
		while (selectedUnits != unitsSelected.end()) {

			(*selectedUnits)->ShowHealthBar();
			selectedUnits++;
		}




		// Progress Bars
		list<Entity*>::iterator spawningBuildingsProgressBars = spawningEntities.begin();
		while (spawningBuildingsProgressBars != spawningEntities.end()) {

			(*spawningBuildingsProgressBars)->ShowProgressBar();
			spawningBuildingsProgressBars++;
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

		if ((*checkForDeadUnits)->GetCurrLife() <= 0 || !(*checkForDeadUnits)->isAlive) {

			App->player->housingSpace.count--;
			activeUnits.erase(checkForDeadUnits);
		}
		checkForDeadUnits++;
	}

	list<Entity*>::iterator checkForDeadBuildings = activeBuildings.begin();
	while (checkForDeadBuildings != activeBuildings.end()) {

		if ((*checkForDeadBuildings)->GetCurrLife() <= 0 || !(*checkForDeadBuildings)->isAlive) {

			activeBuildings.erase(checkForDeadBuildings);
		}
		checkForDeadBuildings++;
	}

	list<Entity*>::iterator checkForDeadEntities = activeEntities.begin();
	while (checkForDeadEntities != activeEntities.end()) {

		if ((*checkForDeadEntities)->GetCurrLife() <= 0 || !(*checkForDeadEntities)->isAlive) {

			(*checkForDeadEntities)->isAlive = false;
			activeEntities.erase(checkForDeadEntities);

			(*checkForDeadEntities)->~Entity();
		}
		checkForDeadEntities++;
	}

	


	return ret;
}

void j1EntityManager::OnCollision(Collider* c1, Collider* c2) {

	if (c1->type == COLLIDER_ALLY_UNIT && c2->type == COLLIDER_ALLY_UNIT) {
		c1->entity->OnCollision(c1, c2);
		c2->entity->OnCollision(c1, c2);
	}
}

bool j1EntityManager::CleanUp() {
	BROFILER_CATEGORY("Entity Manager CleanUp--Entity Manager();", Profiler::Color::LightBlue);
	bool ret = true;

	/*App->tex->UnLoad(townHallTexture);
	App->tex->UnLoad(paintExtractorTexture);
	App->tex->UnLoad(woodProducerTexture);
	App->tex->UnLoad(houseTexture);
	App->tex->UnLoad(barracksTexture);
	App->tex->UnLoad(painterTexture);
	App->tex->UnLoad(warrior_Texture);
	App->tex->UnLoad(slimeTexture);

	App->tex->UnLoad(buildingTexture);

	App->tex->UnLoad(fullLifeTexture);
	App->tex->UnLoad(zeroLifeTexture);*/

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
	spawningEntities.clear();

	EntityTexturesAreLoaded = false;
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

Entity* j1EntityManager::AddEntity(ENTITY_TYPE entityType, iPoint tile, j1Module* listener, Entity* creator, float damage, bool spawnAutomatically) {

	// Allies
/// Buildings
	if (entityType == ENTITY_TYPE_TOWN_HALL) {

		TownHall* townHall = new TownHall(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)townHall);
			activeBuildings.push_back((Entity*)townHall);
			townHall->isAlive = true;
			townHall->CreateEntityCollider(townHall->pos, (Entity*)townHall);
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
			paintExtractor->CreateEntityCollider(paintExtractor->pos, (Entity*)paintExtractor);
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
			woodProducer->CreateEntityCollider(woodProducer->pos, (Entity*)woodProducer);
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
			house->CreateEntityCollider(house->pos, (Entity*)house);
			App->player->housingSpace.maxCount += 5;
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
			barracks->CreateEntityCollider(barracks->pos, (Entity*)barracks);
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
			painter->CreateEntityCollider(painter->pos, (Entity*)painter);
			painter->currentAnimation = &painterIdle;
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
			warrior->CreateEntityCollider(warrior->pos, (Entity*)warrior);
			warrior->currentAnimation = &warriorIdle;
		}

		else
			spawningEntities.push_back((Entity*)warrior);

		return (Entity*)warrior;
	}

	else if (entityType == ENTITY_TYPE_KNIGHT) {

		Knight* knight = new Knight(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)knight);
			activeUnits.push_back((Entity*)knight);
			knight->isAlive = true;
			knight->CreateEntityCollider(knight->pos, (Entity*)knight);
			knight->currentAnimation = &warriorIdle; // TODO: change
		}

		else
			spawningEntities.push_back((Entity*)knight);

		return (Entity*)knight;
	}

	else if (entityType == ENTITY_TYPE_KNIGHT) {

		Explorer* explorer = new Explorer(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)explorer);
			activeUnits.push_back((Entity*)explorer);
			explorer->isAlive = true;
			explorer->CreateEntityCollider(explorer->pos, (Entity*)explorer);
			explorer->currentAnimation = &warriorIdle; // TODO: change
		}

		else
			spawningEntities.push_back((Entity*)explorer);

		return (Entity*)explorer;
	}


		// Enemies
	/// Buildings
	if (entityType == ENTITY_TYPE_SPAWNER) {

		Spawner* spawner = new Spawner(tile, damage, this);
		activeEntities.push_back((Entity*)spawner);
		activeBuildings.push_back((Entity*)spawner);
		spawner->isAlive = true;
		spawner->CreateEntityCollider(spawner->pos, (Entity*)spawner);

		// Change the walkability to non walkable
		App->pathfinding->ChangeToSpawner(tile);

		return (Entity*)spawner;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_SLIME) {

		Slime* slime = new Slime(tile, damage, this);
		activeEntities.push_back((Entity*)slime);
		activeUnits.push_back((Entity*)slime);
		slime->isAlive = true;
		slime->CreateEntityCollider(slime->pos, (Entity*)slime);

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

void j1EntityManager::LoadEntityTextures()
{
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
	warriorTexture = App->tex->Load("textures/Warrior_Sprite_Mod.png");
	painterTexture = App->tex->Load("textures/spritesheet_painter_mod.png");
	knightTexture = App->tex->Load("textures/");// TODO: Add

	// Enemies
/// Buildings
	spawnerTexture = App->tex->Load("textures/Spawner.png");

	/// Units
	slimeTexture = App->tex->Load("textures/Slime.png");

	buildingTexture = App->tex->Load("textures/Building.png");

	fullLifeTexture = App->tex->Load("textures/FullLife.png");
	zeroLifeTexture = App->tex->Load("textures/ZeroLife.png");
	progressTexture = App->tex->Load("textures/ProgressBar.png");
	zeroProgressTexture=App->tex->Load("textures/ZeroProgress.png");

	WarriorSprites();
	PainterSprites();

	
}

void j1EntityManager::UpdateAnimations() {

	std::list<Entity*>::iterator checkMovingAnimation = activeUnits.begin();
	while (checkMovingAnimation != activeUnits.end()) {

		if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_WARRIOR) {

			if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingNorth;
				Mix_PlayChannel(-1, App->audio->walkingWarrior_sound, 0);

			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingNorthEast;
				Mix_PlayChannel(-1, App->audio->walkingWarrior_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingEast;
				Mix_PlayChannel(-1, App->audio->walkingWarrior_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingSouthEast;
				Mix_PlayChannel(-1, App->audio->walkingWarrior_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingSouth;
				Mix_PlayChannel(-1, App->audio->walkingWarrior_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingSouthWest;
				Mix_PlayChannel(-1, App->audio->walkingWarrior_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingWest;
				Mix_PlayChannel(-1, App->audio->walkingWarrior_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingNorthWest;
				Mix_PlayChannel(-1, App->audio->walkingWarrior_sound, 0);
			}
		}

		else if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_PAINTER) {

			if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingNorth;
				Mix_PlayChannel(-1, App->audio->walkingPainter_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingNorthEast;
				Mix_PlayChannel(-1, App->audio->walkingPainter_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingEast;
				Mix_PlayChannel(-1, App->audio->walkingPainter_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingSouthEast;
				Mix_PlayChannel(-1, App->audio->walkingPainter_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingSouth;
				Mix_PlayChannel(-1, App->audio->walkingPainter_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingSouthWest;
				Mix_PlayChannel(-1, App->audio->walkingPainter_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingWest;
				Mix_PlayChannel(-1, App->audio->walkingPainter_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingNorthWest;
				Mix_PlayChannel(-1, App->audio->walkingPainter_sound, 0);
			}
		}
		checkMovingAnimation++;
	}
}

bool j1EntityManager::Load(pugi::xml_node& save)
{
	CleanUp();
	int numEntities = save.child("num_entities").attribute("value").as_int();

	pugi::xml_node entities_node = save.child("active_entities").child("entity");

	//pugi::xml_node entities = save.child("entities").child("warrior");
	for (int i = 0; i < numEntities; i++) {

		int x, y;
		int damage;
		//iPoint size;
		int size_x;
		int size_y;
		const char* entityType;

		x = entities_node.attribute("position_x").as_int();
		y = entities_node.attribute("position_y").as_int();
		damage = entities_node.attribute("missing_hp").as_int();
		size_x = entities_node.attribute("size_x").as_int();
		size_y = entities_node.attribute("size_y").as_int();

		entityType = entities_node.attribute("entity_type").as_string();

		if (entityType == "painter") {

			//AddEntity(ENTITY_TYPE_PAINTER, { x, y }, { size_x, size_y }, App->entities, damage);
			App->entities->AddEntity(ENTITY_TYPE_PAINTER, { x,y }, App->entities, nullptr, 0, true);
			//App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { 42, 42 }, App->entities, nullptr, 0, true);
		}

		entities_node = entities_node.next_sibling();
	}

	return true;
}

bool j1EntityManager::Save(pugi::xml_node& save) const
{
	pugi::xml_node numEntities = save.append_child("num_entities");
	numEntities.append_attribute("value") = activeEntities.size();

	pugi::xml_node entities = save.append_child("active_entities");

	list<Entity*>::const_iterator entitiesToSave = activeEntities.begin();
	while (entitiesToSave != activeEntities.end()) {

		pugi::xml_node entity = entities.append_child("entity");

		if ((*entitiesToSave)->entityType == ENTITY_TYPE_PAINTER) {

			entity.append_attribute("entity_type").as_string("painter");
			entity.append_attribute("position_x") = (*entitiesToSave)->pos.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->pos.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}


		entitiesToSave++;
	}

	return true;
}