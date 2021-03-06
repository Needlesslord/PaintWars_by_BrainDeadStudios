#include "p2Log.h"

#include <algorithm>

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
#include "j1Particles.h"
#include "j1SceneManager.h"
#include "j1QuestManager.h"

bool j1EntityManager::customLess(Entity* a, Entity* b)
{
	if ((a->entityCategory == ENTITY_CATEGORY::ENTITY_CATEGORY_DYNAMIC_ENTITY && b->entityCategory == ENTITY_CATEGORY::ENTITY_CATEGORY_DYNAMIC_ENTITY) ||
		(a->entityCategory == ENTITY_CATEGORY::ENTITY_CATEGORY_STATIC_ENTITY && b->entityCategory == ENTITY_CATEGORY::ENTITY_CATEGORY_STATIC_ENTITY)     )
		return ((float)a->pos.y + (float)a->size.y) < ((float)b->pos.y + (float)b->size.y);
	else if (a->entityCategory == ENTITY_CATEGORY::ENTITY_CATEGORY_DYNAMIC_ENTITY && b->entityCategory == ENTITY_CATEGORY::ENTITY_CATEGORY_STATIC_ENTITY)
		return ((float)a->pos.y + (float)a->size.y) < ((float)b->pos.y + ((float)b->size.y / 1.4));
	else if (a->entityCategory == ENTITY_CATEGORY::ENTITY_CATEGORY_STATIC_ENTITY && b->entityCategory == ENTITY_CATEGORY::ENTITY_CATEGORY_DYNAMIC_ENTITY)
		return ((float)a->pos.y + ((float)a->size.y / 1.4)) < ((float)b->pos.y + (float)b->size.y);
}


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

	if (isChromaKingAwakening) {
		isChromaKingAwakening = false;

		list<Entity*>::iterator lastSpawner = activeBuildings.begin();
		while (lastSpawner != activeBuildings.end()) {

			if ((*lastSpawner)->entityType == ENTITY_TYPE_SPAWNER) {
				AddEntity(ENTITY_TYPE_CHROMA_KING, { (*lastSpawner)->currentTile.x + 3,(*lastSpawner)->currentTile.y + 3 }, App->entities);
				break;
			}
			lastSpawner++;
		}	
	}

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
		else if ((*setDefaultAnimation)->entityType == ENTITY_TYPE_KNIGHT) {
			(*setDefaultAnimation)->currentAnimation = &knightIdle;
		}
		else if ((*setDefaultAnimation)->entityType == ENTITY_TYPE_EXPLORER) {
			(*setDefaultAnimation)->currentAnimation = &explorerIdle;
		}
		else if ((*setDefaultAnimation)->entityType == ENTITY_TYPE_RANGER) {
			(*setDefaultAnimation)->currentAnimation = &rangerIdle;
		}
		else if ((*setDefaultAnimation)->entityType == ENTITY_TYPE_RIDER) {
			(*setDefaultAnimation)->currentAnimation = &riderIdle;
		}
		else if ((*setDefaultAnimation)->entityType == ENTITY_TYPE_SLIME) {
			(*setDefaultAnimation)->currentAnimation = &slimeIdle;
		}
		else if ((*setDefaultAnimation)->entityType == ENTITY_TYPE_CHROMA_KING) {
			(*setDefaultAnimation)->currentAnimation = &chromaKingIdle;
		}
		else if ((*setDefaultAnimation)->entityType == ENTITY_TYPE_EXPLOSIVE_BLOB) {
			(*setDefaultAnimation)->currentAnimation = &explosiveBlobIdle;
		}

		
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


	// Updating targets
	list<Entity*>::iterator updatingTargets = activeUnits.begin();
	while (updatingTargets != activeUnits.end()) {

		// Only interested in the ones who have a target
		if ((*updatingTargets)->target != nullptr) {

			if ((*updatingTargets)->target->GetCurrLife() <= 0) {
				(*updatingTargets)->target = nullptr;
			}

			// If the target is a unit
			else if ((*updatingTargets)->target->entityCategory == ENTITY_CATEGORY_DYNAMIC_ENTITY) {
				(*updatingTargets)->target_rect = { (*updatingTargets)->target->currentTile.x, (*updatingTargets)->target->currentTile.y, 1, 1 };
			}

			// If not, it will be a spawner
			else {
				(*updatingTargets)->target_rect = { (*updatingTargets)->target->currentTile.x, (*updatingTargets)->target->currentTile.y, 2, 2 };
			}
		}
		else
			(*updatingTargets)->target = nullptr;

		updatingTargets++;
	}

	/*if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		spacePressed = true;
	else
		spacePressed = false;*/


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
					else if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_KNIGHT)
						(*checkForSpawningEntities)->currentAnimation = &knightIdle;
					else if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_EXPLORER)
						(*checkForSpawningEntities)->currentAnimation = &explorerIdle;
					else if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_RANGER)
						(*checkForSpawningEntities)->currentAnimation = &rangerIdle;
					else if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_RIDER)
						(*checkForSpawningEntities)->currentAnimation = &riderIdle;
					else if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_SLIME)
						(*checkForSpawningEntities)->currentAnimation = &slimeIdle;
					else if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_CHROMA_KING)
						(*checkForSpawningEntities)->currentAnimation = &chromaKingIdle;
					else if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_EXPLOSIVE_BLOB)
						(*checkForSpawningEntities)->currentAnimation = &explosiveBlobIdle;

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

						if ((*checkForSpawningEntities)->entityType == ENTITY_TYPE_TURRET)
							App->render->RenderQueueUI(1, buildingTexture, (*checkForSpawningEntities)->pos.x, (*checkForSpawningEntities)->pos.y + 150, { 0,0,260,260 });

						else
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
			else if (hoveringEntityType == ENTITY_TYPE_TITANIUM_EXTRACTOR) {
				App->render->RenderQueue(1, titaniumExtractorTexture, mapWorldCoordinates.x - 125 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 250 + App->map->data.tile_height / 2, { 0,0,250,250 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_WOOD_PRODUCER) {
				App->render->RenderQueue(1, woodProducerTexture, mapWorldCoordinates.x - 75 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 200 + App->map->data.tile_height / 2, { 0,0,150,200 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_METAL_GATHERER) {
				App->render->RenderQueue(1, metalGathererTexture, mapWorldCoordinates.x - 75 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 200 + App->map->data.tile_height / 2, { 0,0,150,200 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_BARRACKS) {
				App->render->RenderQueue(1, barracksTexture, mapWorldCoordinates.x - 125 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 250 + App->map->data.tile_height / 2, { 0,0,250,250 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_HOUSE) {
				App->render->RenderQueue(1, houseTexture, mapWorldCoordinates.x - 200 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 400 + App->map->data.tile_height / 2, { 0,0,400,400 });
			}
			else if (hoveringEntityType == ENTITY_TYPE_TURRET) {
				App->render->RenderQueue(1, turretTexture, mapWorldCoordinates.x - 125 + App->map->data.tile_width / 2, mapWorldCoordinates.y - 250 + App->map->data.tile_height / 2, { 0,0,250,400 });
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
							bought = true;
						}
					}
				}

				else if (hoveringEntityType == ENTITY_TYPE_TITANIUM_EXTRACTOR) {
				
					if (App->player->metalScrapCount.count >= 50) {

						App->player->metalScrapCount.count -= 50;
						isSelectingPlacement = false;
						AddEntity(ENTITY_TYPE_TITANIUM_EXTRACTOR, mapCoordinates, App->entities, nullptr, 0);
						hoveringEntityType == ENTITY_TYPE_NONE;
						bought = true;
					}
				}

				else if (hoveringEntityType == ENTITY_TYPE_WOOD_PRODUCER) {

					if (App->pathfinding->IsBuildable(mapCoordinates)) {

						if (App->player->paintCount.count >= 20) {
							isSelectingPlacement = false;
							App->player->paintCount.count -= 20;
							AddEntity(ENTITY_TYPE_WOOD_PRODUCER, mapCoordinates, App->entities, nullptr, 0);
							hoveringEntityType == ENTITY_TYPE_NONE;
							bought = true;
						}
					}
				}

				else if (hoveringEntityType == ENTITY_TYPE_METAL_GATHERER) {

					if (App->pathfinding->IsBuildable(mapCoordinates)) {

						if (App->player->paintCount.count >= 100) {
							isSelectingPlacement = false;
							App->player->paintCount.count -= 100;
							AddEntity(ENTITY_TYPE_METAL_GATHERER, mapCoordinates, App->entities, nullptr, 0);
							hoveringEntityType == ENTITY_TYPE_NONE;
							bought = true;
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
							BarracksQuestDone = true;
							bought = true;
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
							bought = true;
						}
					}
				}

				else if (hoveringEntityType == ENTITY_TYPE_TURRET) {

					if (App->pathfinding->IsBuildable(mapCoordinates)) {

						if (App->player->woodCount.count >= 75) {
							isSelectingPlacement = false;
							App->player->woodCount.count -= 75;
							AddEntity(ENTITY_TYPE_TURRET, mapCoordinates, App->entities, nullptr, 0);
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




		// Extract Paint (Painters and PaintExtractor)
		list<Entity*>::iterator entitiesToExtractPaint = activeEntities.begin();
		while (entitiesToExtractPaint != activeEntities.end()) {

			// We try to extract and it will return if it can't
			if ((*entitiesToExtractPaint)->entityType == ENTITY_TYPE_PAINTER && (*entitiesToExtractPaint)->currentTile == (*entitiesToExtractPaint)->destination && App->pathfinding->IsPaintShore((*entitiesToExtractPaint)->currentTile)) {

				(*entitiesToExtractPaint)->ExtractPaint(dt);
				(*entitiesToExtractPaint)->currentAnimation = &painterRecollection;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);

			}

			else if ((*entitiesToExtractPaint)->entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {
				
				(*entitiesToExtractPaint)->ExtractPaint(dt);
			}
			
			entitiesToExtractPaint++;
		}

		// Extract Wood  (ONLY PAINTERS CAN)
		list<Entity*>::iterator paintersToExtractWood = activeUnits.begin();
		while (paintersToExtractWood != activeUnits.end()) {

			// We try to extract and it will return if it can't
			if ((*paintersToExtractWood)->entityType == ENTITY_TYPE_PAINTER && (App->pathfinding->IsWood((*paintersToExtractWood)->currentTile) && (*paintersToExtractWood)->currentTile == (*paintersToExtractWood)->destination)) {

				(*paintersToExtractWood)->ExtractWood(dt);
				(*paintersToExtractWood)->currentAnimation = &painterRecollection;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);

			}
			paintersToExtractWood++;
		}

		// Extract Metal scrap  (ONLY PAINTERS CAN)
		list<Entity*>::iterator paintersToExtractMetal = activeUnits.begin();
		while (paintersToExtractMetal != activeUnits.end()) {

			// We try to extract and it will return if it can't
			if ((*paintersToExtractMetal)->entityType == ENTITY_TYPE_PAINTER && (App->pathfinding->IsMetalScrap((*paintersToExtractMetal)->currentTile) && (*paintersToExtractMetal)->currentTile == (*paintersToExtractMetal)->destination)) {

				(*paintersToExtractMetal)->ExtractMetalScrap(dt);
				App->audio->PlayFx(App->audio->walkingUnit2_sound);

			}
			paintersToExtractMetal++;
		}

		// Extract titanium 
		list<Entity*>::iterator extractTitanium = activeBuildings.begin();
		while (extractTitanium != activeBuildings.end()) {

			// We try to extract and it will return if it can't
			if ((*extractTitanium)->entityType == ENTITY_TYPE_TITANIUM_EXTRACTOR) {

				(*extractTitanium)->ExtractTitanium(dt);
				App->audio->PlayFx(App->audio->walkingUnit2_sound);

			}
			extractTitanium++;
		}





		// Enemies pathfinding Logic
		list<Entity*>::iterator enemiesToMove = activeUnits.begin(); 
		while (enemiesToMove != activeUnits.end()) {

			// We only want enemies
			if (!(*enemiesToMove)->isEntityFromPlayer && (*enemiesToMove)->target == nullptr) {

				uint minimumDistance = 999;

				// We'll sweep through all ALLY units and target the closest one within range
				list<Entity*>::iterator allOtherUnits = activeUnits.begin();
				while (allOtherUnits != activeUnits.end()) {

					// We only want allies here
					if ((*allOtherUnits)->isEntityFromPlayer) {

						// Distance between this enemy and this ally
						int i = App->pathfinding->DistanceTo((*enemiesToMove)->currentTile, (*allOtherUnits)->currentTile);

						// Check if the ally is in range
						if (i <= (*enemiesToMove)->aggroRange) {

							// Check if this ally is closer to this enemy than all previous allies
							if (i < minimumDistance) {

								// We'll set it as the current one to beat, and if there are no others, set it as target
								minimumDistance = i;
								(*enemiesToMove)->target = (*allOtherUnits);
							}
						}
					}

					allOtherUnits++;
				}
			}

			enemiesToMove++;
		}





		// Change destination for units selected on right-click
		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN && !unitsSelected.empty()) {

			fPoint mouseWorldPosition = App->input->GetMouseWorldPosition();

			bool attacking = false;

			list<Entity*>::iterator subjects = unitsSelected.begin();
			while (subjects != unitsSelected.end()) {

				(*subjects)->target = nullptr;
				subjects++;
			}
			subjects = unitsSelected.begin();

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
							(*unitsToRedirect)->CalculateMovementLogic();
						}

					}

					unitsToRedirect++;
				}
			}
		}

		

		// Turrets targetting system
		list<Entity*>::iterator turretsToTarget = activeBuildings.begin();
		while (turretsToTarget != activeBuildings.end()) {

			// Only turrets here
			if ((*turretsToTarget)->entityType == ENTITY_TYPE_TURRET) {

				(*turretsToTarget)->target = nullptr;
				int minimumDistance = 999;

				// Cycle throw enemies
				list<Entity*>::iterator enemyUnits = activeUnits.begin();
				while (enemyUnits != activeUnits.end()) {
				
					if (!(*enemyUnits)->isEntityFromPlayer) {

						if (App->pathfinding->DistanceTo((*turretsToTarget)->currentTile, (*enemyUnits)->currentTile) <= (*turretsToTarget)->attackRadius) {

							if (App->pathfinding->DistanceTo((*turretsToTarget)->currentTile, (*enemyUnits)->currentTile) < minimumDistance) {

								minimumDistance = App->pathfinding->DistanceTo((*turretsToTarget)->currentTile, (*enemyUnits)->currentTile);
								(*turretsToTarget)->target = (*enemyUnits);
							}
						}
					}

					enemyUnits++;
				}
			}

			turretsToTarget++;
		}



		// Attacking Logic
		list<Entity*>::iterator entitiessToAttackLogic = activeEntities.begin();
		while (entitiessToAttackLogic != activeEntities.end()) {

			// First, we will get the units that need to AttackLogic
			if ((*entitiessToAttackLogic)->target != nullptr) {

				// Checking if the unit is in range to attack
				// If it's in range, we'll move it
				if (App->pathfinding->DistanceTo((*entitiessToAttackLogic)->currentTile, (*entitiessToAttackLogic)->target->currentTile) <= (*entitiessToAttackLogic)->attackRadius) {

					(*entitiessToAttackLogic)->Attack((*entitiessToAttackLogic)->target, dt);
					AttackQuestDone = true;
					std::list<Entity*>::iterator checkAttackAnimation = activeUnits.begin();
					while (checkAttackAnimation != activeUnits.end()) {

						if ((*checkAttackAnimation)->entityType == ENTITY_TYPE_WARRIOR) {

							if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_NORTH) {

								(*checkAttackAnimation)->currentAnimation = &warriorAttackNorth;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_NORTH_EAST) {

								(*checkAttackAnimation)->currentAnimation = &warriorAttackNorthEast;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_EAST) {

								(*checkAttackAnimation)->currentAnimation = &warriorAttackEast;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

								(*checkAttackAnimation)->currentAnimation = &warriorAttackSouthEast;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_SOUTH) {

								(*checkAttackAnimation)->currentAnimation = &warriorAttackSouth;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

								(*checkAttackAnimation)->currentAnimation = &warriorAttackSouthWest;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_WEST) {

								(*checkAttackAnimation)->currentAnimation = &warriorAttackWest;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_NORTH_WEST) {

								(*checkAttackAnimation)->currentAnimation = &warriorAttackNorthWest;
							}
						}


						else if ((*checkAttackAnimation)->entityType == ENTITY_TYPE_RANGER) {

							if ((*checkAttackAnimation)->currentTile.x < (*checkAttackAnimation)->target->currentTile.x) {

								if ((*checkAttackAnimation)->currentTile.y < (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &rangerAttackSouth;
								}
								else if ((*checkAttackAnimation)->currentTile.y > (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &rangerAttackEast;
								}
								else {

									(*checkAttackAnimation)->currentAnimation = &rangerAttackSouthEast;
								}
							}

							else if ((*checkAttackAnimation)->currentTile.x > (*checkAttackAnimation)->target->currentTile.x) {

								if ((*checkAttackAnimation)->currentTile.y < (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &rangerAttackWest;
								}
								else if ((*checkAttackAnimation)->currentTile.y > (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &rangerAttackNorth;
								}
								else {

									(*checkAttackAnimation)->currentAnimation = &rangerAttackNorthWest;
								}
							}

							else if ((*checkAttackAnimation)->currentTile.x == (*checkAttackAnimation)->target->currentTile.x) {

								if ((*checkAttackAnimation)->currentTile.y < (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &rangerAttackSouthWest;
								}
								else if ((*checkAttackAnimation)->currentTile.y > (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &rangerAttackNorthEast;
								}
								else {

									(*checkAttackAnimation)->currentAnimation = &rangerAttackSouth;
								}
							}
						}

						else if ((*checkAttackAnimation)->entityType == ENTITY_TYPE_KNIGHT) {

							if ((*checkAttackAnimation)->currentTile.x < (*checkAttackAnimation)->target->currentTile.x) {

								if ((*checkAttackAnimation)->currentTile.y < (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &knightAttackSouth;
								}
								else if ((*checkAttackAnimation)->currentTile.y > (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &knightAttackEast;
								}
								else {

									(*checkAttackAnimation)->currentAnimation = &knightAttackSouthEast;
								}
							}

							else if ((*checkAttackAnimation)->currentTile.x > (*checkAttackAnimation)->target->currentTile.x) {

								if ((*checkAttackAnimation)->currentTile.y < (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &knightAttackWest;
								}
								else if ((*checkAttackAnimation)->currentTile.y > (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &knightAttackNorth;
								}
								else {

									(*checkAttackAnimation)->currentAnimation = &knightAttackNorthWest;
								}
							}

							else if ((*checkAttackAnimation)->currentTile.x == (*checkAttackAnimation)->target->currentTile.x) {

								if ((*checkAttackAnimation)->currentTile.y < (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &knightAttackSouthWest;
								}
								else if ((*checkAttackAnimation)->currentTile.y > (*checkAttackAnimation)->target->currentTile.y) {

									(*checkAttackAnimation)->currentAnimation = &knightAttackNorthEast;
								}
								else {

									(*checkAttackAnimation)->currentAnimation = &knightAttackSouth;
								}
							}
						}

						// TODO: keep changing these (Also warrior)!!!
						else if ((*checkAttackAnimation)->entityType == ENTITY_TYPE_RIDER) {

							if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_NORTH) {

								(*checkAttackAnimation)->currentAnimation = &riderAttackNorth;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_NORTH_EAST) {

								(*checkAttackAnimation)->currentAnimation = &riderAttackNorthEast;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_EAST) {
	
								(*checkAttackAnimation)->currentAnimation = &riderAttackEast;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

								(*checkAttackAnimation)->currentAnimation = &riderAttackSouthEast;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_SOUTH) {

								(*checkAttackAnimation)->currentAnimation = &riderAttackSouth;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

								(*checkAttackAnimation)->currentAnimation = &riderAttackSouthWest;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_WEST) {

								(*checkAttackAnimation)->currentAnimation = &riderAttackWest;
							}

							else if ((*checkAttackAnimation)->previousOrientation == UNIT_ORIENTATION_NORTH_WEST) {

								(*checkAttackAnimation)->currentAnimation = &riderAttackNorthWest;
							}
						}
					
						checkAttackAnimation++;
					}
				}

				// If not, move closer and we'll continue to check until it can attack
				else {

					// First we'll create a path to the target's position
					int map;
					map = App->pathfinding->CreatePath((*entitiessToAttackLogic)->currentTile, (*entitiessToAttackLogic)->target->currentTile, true);
					(*entitiessToAttackLogic)->currentPath = *App->pathfinding->GetLastPath();
					
					bool isInRange = false;
					int i = 0;
					
					// We are looking for the closest tile that is in range to attack the target
					while (!isInRange) {

						if (App->pathfinding->DistanceTo((*entitiessToAttackLogic)->currentPath.at(i), (*entitiessToAttackLogic)->target->currentTile) <= (*entitiessToAttackLogic)->attackRadius) {

							isInRange = true;

							(*entitiessToAttackLogic)->SetDestination((*entitiessToAttackLogic)->currentPath.at(i));
							destinations.push_back((*entitiessToAttackLogic)->currentPath.at(i));
							(*entitiessToAttackLogic)->CalculateMovementLogic();

							//map = App->pathfinding->CreatePath((*unitsToAttackLogic)->currentTile, (*unitsToAttackLogic)->currentPath.at(i));
							//(*unitsToAttackLogic)->currentPath = *App->pathfinding->GetLastPath();

							break;
						}

						i++;

						if (i >= (*entitiessToAttackLogic)->currentPath.size())
							break;
					}
				}
			}

			entitiessToAttackLogic++;
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





		// Update Particles
		std::list<Entity*>::iterator particleToUpdate = activeEntities.begin();
		while (particleToUpdate != activeEntities.end()) {

			if ((*particleToUpdate)->entityType == ENTITY_TYPE_RANGER) {

				if ((*particleToUpdate)->particles.size() > 0) {

					particles = (*particleToUpdate)->particles;

					std::list<Particles*>::iterator particle = particles.begin();
					while (particle != particles.end()) {

						if ((*particle)->isAlive) {

							if ((*particleToUpdate)->target == nullptr) {

								float ang = atan((((*particle)->target.y + (*particle)->targetSize.y / 2) - (*particle)->pos.y) / (((*particle)->target.x + (*particle)->targetSize.x / 2) - (*particle)->pos.x));

								(*particle)->speed.x = 500 * cos(ang);
								(*particle)->speed.y = 500 * sin(ang);

								(*particle)->Update(dt, { ((*particle)->target.x + ((*particle)->targetSize.x / 2)), ((*particle)->target.y + ((*particle)->targetSize.y / 2)) });
							}

							else {

								float ang = atan((((*particleToUpdate)->target->pos.y + (*particleToUpdate)->target->GetSize().y / 2) - (*particle)->pos.y) / (((*particleToUpdate)->target->pos.x + (*particleToUpdate)->target->GetSize().x / 2) - (*particle)->pos.x));

								(*particle)->target.x = (*particleToUpdate)->target->pos.x;
								(*particle)->target.y = (*particleToUpdate)->target->pos.y;
								(*particle)->targetSize.x = (*particleToUpdate)->target->GetSize().x;
								(*particle)->targetSize.y = (*particleToUpdate)->target->GetSize().y;

								(*particle)->speed.x = 500 * cos(ang);
								(*particle)->speed.y = 500 * sin(ang);

								if ((*particle)->Update(dt, { ((*particleToUpdate)->target->pos.x + ((*particleToUpdate)->target->GetSize().x / 2)), ((*particleToUpdate)->target->pos.y + ((*particleToUpdate)->target->GetSize().y / 2)) }) == false) {

									(*particleToUpdate)->particles.erase(particle);
									(*particleToUpdate)->target->ApplyDamage((*particleToUpdate)->attackDamage);
									delete(*particle);
								}
							}
						}

						particle++;
					}
				}


			}
			else if ((*particleToUpdate)->entityType == ENTITY_TYPE_RANGER || (*particleToUpdate)->entityType == ENTITY_TYPE_TURRET) {

				if ((*particleToUpdate)->particles.size() > 0) {

					particles = (*particleToUpdate)->particles;

					std::list<Particles*>::iterator particle = particles.begin();
					while (particle != particles.end()) {

						if ((*particle)->isAlive) {

							if ((*particleToUpdate)->target == nullptr) {

								float ang = atan((((*particle)->target.y + (*particle)->targetSize.y / 2) - (*particle)->pos.y) / (((*particle)->target.x + (*particle)->targetSize.x / 2) - (*particle)->pos.x));

								(*particle)->speed.x = 500 * cos(ang);
								(*particle)->speed.y = 500 * sin(ang);

								(*particle)->Update(dt, { ((*particle)->target.x + ((*particle)->targetSize.x / 2)), ((*particle)->target.y + ((*particle)->targetSize.y / 2)) });
							}

							else {

								float ang = atan((((*particleToUpdate)->target->pos.y + (*particleToUpdate)->target->GetSize().y / 2) - (*particle)->pos.y) / (((*particleToUpdate)->target->pos.x + (*particleToUpdate)->target->GetSize().x / 2) - (*particle)->pos.x));

								(*particle)->target.x = (*particleToUpdate)->target->pos.x;
								(*particle)->target.y = (*particleToUpdate)->target->pos.y;
								(*particle)->targetSize.x = (*particleToUpdate)->target->GetSize().x;
								(*particle)->targetSize.y = (*particleToUpdate)->target->GetSize().y;

								(*particle)->speed.x = 500 * cos(ang);
								(*particle)->speed.y = 500 * sin(ang);

								if ((*particle)->Update(dt, { ((*particleToUpdate)->target->pos.x + ((*particleToUpdate)->target->GetSize().x / 2)), ((*particleToUpdate)->target->pos.y + ((*particleToUpdate)->target->GetSize().y / 2)) }) == false) {

									(*particleToUpdate)->particles.erase(particle);
									(*particleToUpdate)->target->ApplyDamage((*particleToUpdate)->attackDamage);
									delete(*particle);
								}
							}
						}

						particle++;
					}
				}


			}

			else if ((*particleToUpdate)->entityType == ENTITY_TYPE_SLIME || (*particleToUpdate)->entityType == ENTITY_TYPE_CHROMA_KING) {

				if ((*particleToUpdate)->particles.size() > 0) {

					particles = (*particleToUpdate)->particles;

					std::list<Particles*>::iterator particle = particles.begin();
					while (particle != particles.end()) {

						if ((*particle)->isAlive) {

							if ((*particleToUpdate)->target == nullptr) {

								float ang = atan((((*particle)->target.y + (*particle)->targetSize.y / 2) - (*particle)->pos.y) / (((*particle)->target.x + (*particle)->targetSize.x / 2) - (*particle)->pos.x));

								(*particle)->speed.x = 250 * cos(ang);
								(*particle)->speed.y = 250 * sin(ang);

								(*particle)->Update(dt, { ((*particle)->target.x + ((*particle)->targetSize.x / 2)), ((*particle)->target.y + ((*particle)->targetSize.y / 2)) });
							}

							else {

								float ang = atan((((*particleToUpdate)->target->pos.y + (*particleToUpdate)->target->GetSize().y / 2) - (*particle)->pos.y) / (((*particleToUpdate)->target->pos.x + (*particleToUpdate)->target->GetSize().x / 2) - (*particle)->pos.x));

								(*particle)->target.x = (*particleToUpdate)->target->pos.x;
								(*particle)->target.y = (*particleToUpdate)->target->pos.y;
								(*particle)->targetSize.x = (*particleToUpdate)->target->GetSize().x;
								(*particle)->targetSize.y = (*particleToUpdate)->target->GetSize().y;

								(*particle)->speed.x = 250 * cos(ang);
								(*particle)->speed.y = 250 * sin(ang);

								if ((*particle)->Update(dt, { ((*particleToUpdate)->target->pos.x + ((*particleToUpdate)->target->GetSize().x / 2)), ((*particleToUpdate)->target->pos.y + ((*particleToUpdate)->target->GetSize().y / 2)) }) == false) {

									(*particleToUpdate)->particles.erase(particle);
									(*particleToUpdate)->target->ApplyDamage((*particleToUpdate)->attackDamage);
									delete(*particle);
								}
							}
						}

						particle++;
					}
				}

			}
			particleToUpdate++;
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

	// Fog of war update (for active entities)

	list<Entity*>::iterator entitiesFoW = activeEntities.begin();
	while (entitiesFoW != activeEntities.end()) {

		(*entitiesFoW)->fow_entity->is_visible = (*entitiesFoW)->visible;

		if ((*entitiesFoW)->isEntityFromPlayer) {
			(*entitiesFoW)->fow_entity->SetPos((*entitiesFoW)->currentTile);
		}

		entitiesFoW++;

	}


	//if (App->PAUSE_ACTIVE == true) {

		// Sort Active Entities
	
		activeEntities.sort(customLess);
		

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
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_METAL_GATHERER) {
					(*entitiesToDraw)->Draw(metalGathererTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_TITANIUM_EXTRACTOR) {
					(*entitiesToDraw)->Draw(titaniumExtractorTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_HOUSE) {
					(*entitiesToDraw)->Draw(houseTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_BARRACKS) {
					(*entitiesToDraw)->Draw(barracksTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_TURRET) {
					(*entitiesToDraw)->Draw(turretTexture);
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
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_RANGER) {
					(*entitiesToDraw)->Draw(rangerTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_SPAWNER) {
					(*entitiesToDraw)->Draw(spawnerTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_SLIME) {
					(*entitiesToDraw)->Draw(slimeTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_RIDER) {
					(*entitiesToDraw)->Draw(riderTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_CHROMA_KING) {
					(*entitiesToDraw)->Draw(chromaKingTexture);
				}
				else if ((*entitiesToDraw)->entityType == ENTITY_TYPE_EXPLOSIVE_BLOB) {
					(*entitiesToDraw)->Draw(explosiveBlobTexture);
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


	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP) {

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

				if ((*checkForSelectedEntities)->isEntityFromPlayer) {

					if (mouseMapCoordinates.x < (*checkForSelectedEntities)->pos.x + (*checkForSelectedEntities)->GetSize().x && mouseMapCoordinates.x >(*checkForSelectedEntities)->pos.x &&
						mouseMapCoordinates.y < (*checkForSelectedEntities)->pos.y + (*checkForSelectedEntities)->GetSize().y && mouseMapCoordinates.y >(*checkForSelectedEntities)->pos.y) {

						if (!(*checkForSelectedEntities)->isSelected)
							SelectEntity(*checkForSelectedEntities, controlWasPressed);

						isSomethingSelected = true;

						if ((*checkForSelectedEntities)->entityType == ENTITY_TYPE::ENTITY_TYPE_EXPLORER)
							ExplorerQuestDone = true;

						break;
					}
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

			activeUnits.erase(checkForDeadUnits);
		}
		checkForDeadUnits++;
	}

	list<Entity*>::iterator checkForDeadBuildings = activeBuildings.begin();
	while (checkForDeadBuildings != activeBuildings.end()) {

		if ((*checkForDeadBuildings)->GetCurrLife() <= 0 || !(*checkForDeadBuildings)->isAlive) {

			if ((*checkForDeadBuildings)->entityType == ENTITY_TYPE_SPAWNER) {

				spawnersDestroyed++;
				if (spawnersDestroyed == 4)
					isChromaKingAwakening = true;
			}
			activeBuildings.erase(checkForDeadBuildings);
		}
		checkForDeadBuildings++;
	}

	list<Entity*>::iterator checkForDeadEntities = activeEntities.begin();
	while (checkForDeadEntities != activeEntities.end()) {

		if ((*checkForDeadEntities)->GetCurrLife() <= 0 || !(*checkForDeadEntities)->isAlive) {

			(*checkForDeadEntities)->isAlive = false;
			App->fow->DestroyFOWEntity((*checkForDeadEntities)->fow_entity);
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

	LOG("CREATING ENTITY AT: (%d, %d)", tile.x, tile.y);
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

	else if (entityType == ENTITY_TYPE_TITANIUM_EXTRACTOR) {

		TitaniumExtractor* titaniumExtractor = new TitaniumExtractor(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)titaniumExtractor);
			activeBuildings.push_back((Entity*)titaniumExtractor);
			titaniumExtractor->isAlive = true;
			titaniumExtractor->CreateEntityCollider(titaniumExtractor->pos, (Entity*)titaniumExtractor);
		}

		else
			spawningEntities.push_back((Entity*)titaniumExtractor);

		// Change the walkability to non walkable
		App->pathfinding->ChangeWalkability(tile, false, titaniumExtractor->entitySize);

		return (Entity*)titaniumExtractor;
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

	else if (entityType == ENTITY_TYPE_METAL_GATHERER) {

		MetalGatherer* metalGatherer = new MetalGatherer(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)metalGatherer);
			activeBuildings.push_back((Entity*)metalGatherer);
			metalGatherer->isAlive = true;
			metalGatherer->CreateEntityCollider(metalGatherer->pos, (Entity*)metalGatherer);
		}

		else
			spawningEntities.push_back((Entity*)metalGatherer);

		// Change the walkability to non walkable
		App->pathfinding->ChangeWalkability(tile, false, metalGatherer->entitySize);

		// Change to Wood the 4 directly adjacent tiles
		App->pathfinding->ChangeToMetal(tile);

		return (Entity*)metalGatherer;
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

	else if (entityType == ENTITY_TYPE_TURRET) {

		Turret* turret = new Turret(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)turret);
			activeBuildings.push_back((Entity*)turret);
			turret->isAlive = true;
			turret->CreateEntityCollider(turret->pos, (Entity*)turret);
		}

		else
			spawningEntities.push_back((Entity*)turret);

		// Change the walkability to non walkable
		App->pathfinding->ChangeWalkability(tile, false, turret->entitySize);

		return (Entity*)turret;
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
		WarriorQuestDone = true;
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
			knight->currentAnimation = &knightIdle; 
		}

		else
			spawningEntities.push_back((Entity*)knight);

		return (Entity*)knight;
	}

	else if (entityType == ENTITY_TYPE_EXPLORER) {

		Explorer* explorer = new Explorer(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)explorer);
			activeUnits.push_back((Entity*)explorer);
			explorer->isAlive = true;
			explorer->CreateEntityCollider(explorer->pos, (Entity*)explorer);
			explorer->currentAnimation = &explorerIdle;
		}

		else
			spawningEntities.push_back((Entity*)explorer);

		return (Entity*)explorer;
	}

	else if (entityType == ENTITY_TYPE_RANGER) {

		Ranger* ranger = new Ranger(tile, damage, this, creator);

		if (spawnAutomatically) {

			activeEntities.push_back((Entity*)ranger);
			activeUnits.push_back((Entity*)ranger);
			ranger->isAlive = true;
			ranger->CreateEntityCollider(ranger->pos, (Entity*)ranger);
			ranger->currentAnimation = &rangerIdle;
		}

		else
			spawningEntities.push_back((Entity*)ranger);

		return (Entity*)ranger;
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

	else if (entityType == ENTITY_TYPE_RIDER) {

		Rider* rider = new Rider(tile, damage, this);
		activeEntities.push_back((Entity*)rider);
		activeUnits.push_back((Entity*)rider);
		rider->isAlive = true;
		rider->CreateEntityCollider(rider->pos, (Entity*)rider);

		return (Entity*)rider;
	}

	else if (entityType == ENTITY_TYPE_EXPLOSIVE_BLOB) {

		ExplosiveBlob* explosiveBlob = new ExplosiveBlob(tile, damage, this);
		activeEntities.push_back((Entity*)explosiveBlob);
		activeUnits.push_back((Entity*)explosiveBlob);
		explosiveBlob->isAlive = true;
		explosiveBlob->CreateEntityCollider(explosiveBlob->pos, (Entity*)explosiveBlob);

		return (Entity*)explosiveBlob;
	}

	else if (entityType == ENTITY_TYPE_CHROMA_KING) {

		ChromaKing* chromaKing = new ChromaKing(tile, damage, this);
		activeEntities.push_back((Entity*)chromaKing);
		activeUnits.push_back((Entity*)chromaKing);
		chromaKing->isAlive = true;
		chromaKing->CreateEntityCollider(chromaKing->pos, (Entity*)chromaKing);

		return (Entity*)chromaKing;
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
	   App->transition_manager->CreateExpandingBars(SCENES::WIN_SCENE, 0.5f, true); 
	}

}

void j1EntityManager::LoadEntityTextures()
{
	debug_tex = App->tex->Load("maps/path2.png");

		// Allies
	/// Buildings
	townHallTexture = App->tex->Load("textures/entity_building_townHall.png");
	paintExtractorTexture = App->tex->Load("textures/entity_building_paintExtractor.png");
	woodProducerTexture = App->tex->Load("textures/entity_building_woodProducer.png");
	houseTexture = App->tex->Load("textures/entity_building_house.png");
	barracksTexture = App->tex->Load("textures/entity_building_barracks.png");
	metalGathererTexture = App->tex->Load("textures/entity_building_metal_gatherer.png");
	titaniumExtractorTexture = App->tex->Load("textures/entity_building_titanium_extractor.png");
	turretTexture = App->tex->Load("textures/entity_building_turret.png");

	/// Units
	warriorTexture = App->tex->Load("textures/entity_units_warrior_spritesheet.png");
	painterTexture = App->tex->Load("textures/entity_units_painter_spritesheet.png");
	knightTexture = App->tex->Load("textures/entity_units_knight_spritesheet.png");
	explorerTexture = App->tex->Load("textures/entity_units_explorer_spritesheet.png");
	rangerTexture = App->tex->Load("textures/entity_units_ranger_spritesheet.png");

		// Enemies
	/// Buildings
	spawnerTexture = App->tex->Load("textures/entity_building_spawner.png");

	/// Units
	slimeTexture = App->tex->Load("textures/entity_enemy_slime_spritesheet.png");
	riderTexture = App->tex->Load("textures/entity_enemy_rider_spritesheet.png");
	chromaKingTexture = App->tex->Load("textures/entity_enemy_chromaKing_spritesheet.png");
	explosiveBlobTexture = App->tex->Load("textures/entity_enemy_explosiveBlob_spritesheet.png");

	buildingTexture = App->tex->Load("textures/entity_building_construction.png");

	fullLifeTexture = App->tex->Load("textures/UI/UI_lifebar_full.png");
	zeroLifeTexture = App->tex->Load("textures/UI/UI_lifebar_empty.png");
	progressTexture = App->tex->Load("textures/UI/UI_progressBar_full.png");
	zeroProgressTexture=App->tex->Load("textures/UI/UI_progressBar_empty.png");

	WarriorSprites();
	PainterSprites();
	KnightSprites();
	RangerSprites();
	ExplorerSprites();
	RiderSprites();
	SlimeSprites();
	ChromaKingSprites();
	ExplosiveBlobSprites();


	
}

void j1EntityManager::UpdateAnimations() {

	std::list<Entity*>::iterator checkMovingAnimation = activeUnits.begin();
	while (checkMovingAnimation != activeUnits.end()) {

		if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_WARRIOR) {

			if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingNorth;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);

			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingNorthEast;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingEast;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingSouthEast;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingSouth;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingSouthWest;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingWest;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &warriorMovingNorthWest;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}
		}

		else if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_PAINTER) {

			if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingNorth;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingNorthEast;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingEast;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingSouthEast;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingSouth;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingSouthWest;
				App->audio->PlayFx(App->audio->walkingUnit2_sound); (-1, App->audio->walkingUnit2_sound, 0);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingWest;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &painterMovingNorthWest;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}
		}

		else if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_KNIGHT) {

			if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

				(*checkMovingAnimation)->currentAnimation = &knightMovingNorth;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &knightMovingNorthEast;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}
	
			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

				(*checkMovingAnimation)->currentAnimation = &knightMovingEast;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &knightMovingSouthEast;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

				(*checkMovingAnimation)->currentAnimation = &knightMovingSouth;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &knightMovingSouthWest;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

				(*checkMovingAnimation)->currentAnimation = &knightMovingWest;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &knightMovingNorthWest;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}
		}

		else if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_RANGER) {

			if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

				(*checkMovingAnimation)->currentAnimation = &rangerMovingNorth;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &rangerMovingNorthEast;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

				(*checkMovingAnimation)->currentAnimation = &rangerMovingEast;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &rangerMovingSouthEast;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

				(*checkMovingAnimation)->currentAnimation = &rangerMovingSouth;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &rangerMovingSouthWest;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

				(*checkMovingAnimation)->currentAnimation = &rangerMovingWest;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &rangerMovingNorthWest;
				App->audio->PlayFx(App->audio->walkingUnit1_sound);
			}
		}

		else if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_EXPLORER) {

			if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

				(*checkMovingAnimation)->currentAnimation = &explorerMovingNorth;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &explorerMovingNorthEast;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

				(*checkMovingAnimation)->currentAnimation = &explorerMovingEast;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

				(*checkMovingAnimation)->currentAnimation = &explorerMovingSouthEast;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}
	
			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

				(*checkMovingAnimation)->currentAnimation = &explorerMovingSouth;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &explorerMovingSouthWest;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

				(*checkMovingAnimation)->currentAnimation = &explorerMovingWest;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}

			else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

				(*checkMovingAnimation)->currentAnimation = &explorerMovingNorthWest;
				App->audio->PlayFx(App->audio->walkingUnit2_sound);
			}


			else if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_RIDER) {

				if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

					(*checkMovingAnimation)->currentAnimation = &riderMovingNorth;
					App->audio->PlayFx(App->audio->walkingUnit1_sound);

				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &riderMovingNorthEast;
					App->audio->PlayFx(App->audio->walkingUnit1_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

					(*checkMovingAnimation)->currentAnimation = &riderMovingEast;
					App->audio->PlayFx(App->audio->walkingUnit1_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &riderMovingSouthEast;
					App->audio->PlayFx(App->audio->walkingUnit1_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

					(*checkMovingAnimation)->currentAnimation = &riderMovingSouth;
					App->audio->PlayFx(App->audio->walkingUnit1_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &riderMovingSouthWest;
					App->audio->PlayFx(App->audio->walkingUnit1_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

					(*checkMovingAnimation)->currentAnimation = &riderMovingWest;
					App->audio->PlayFx(App->audio->walkingUnit1_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &riderMovingNorthWest;
					App->audio->PlayFx(App->audio->walkingUnit1_sound);
				}
			}


			else if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_SLIME) {

				if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

					(*checkMovingAnimation)->currentAnimation = &slimeMovingNorth;
					App->audio->PlayFx(App->audio->enemy_sound);

				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &slimeMovingNorthEast;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

					(*checkMovingAnimation)->currentAnimation = &slimeMovingEast;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &slimeMovingSouthEast;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

					(*checkMovingAnimation)->currentAnimation = &slimeMovingSouth;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &slimeMovingSouthWest;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

					(*checkMovingAnimation)->currentAnimation = &slimeMovingWest;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {
	
					(*checkMovingAnimation)->currentAnimation = &slimeMovingNorthWest;
					App->audio->PlayFx(App->audio->enemy_sound);
				}
			}


			else if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_CHROMA_KING) {
	
				if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

					(*checkMovingAnimation)->currentAnimation = &chromaKingMovingNorth;
					App->audio->PlayFx(App->audio->enemy_sound);

				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &chromaKingMovingNorthEast;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

					(*checkMovingAnimation)->currentAnimation = &chromaKingMovingEast;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &chromaKingMovingSouthEast;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

					(*checkMovingAnimation)->currentAnimation = &chromaKingMovingSouth;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &chromaKingMovingSouthWest;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

					(*checkMovingAnimation)->currentAnimation = &chromaKingMovingWest;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &chromaKingMovingNorthWest;
					App->audio->PlayFx(App->audio->enemy_sound);
				}
			}

			else if ((*checkMovingAnimation)->entityType == ENTITY_TYPE_EXPLOSIVE_BLOB) {

				if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH) {

					(*checkMovingAnimation)->currentAnimation = &explosiveBlobMovingNorth;
					App->audio->PlayFx(App->audio->enemy_sound);

				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &explosiveBlobMovingNorthEast;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_EAST) {

					(*checkMovingAnimation)->currentAnimation = &explosiveBlobMovingEast;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

					(*checkMovingAnimation)->currentAnimation = &explosiveBlobMovingSouthEast;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH) {

					(*checkMovingAnimation)->currentAnimation = &explosiveBlobMovingSouth;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &explosiveBlobMovingSouthWest;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_WEST) {

					(*checkMovingAnimation)->currentAnimation = &explosiveBlobMovingWest;
					App->audio->PlayFx(App->audio->enemy_sound);
				}

				else if ((*checkMovingAnimation)->unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

					(*checkMovingAnimation)->currentAnimation = &explosiveBlobMovingNorthWest;
					App->audio->PlayFx(App->audio->enemy_sound);
				}
			}
		}

		checkMovingAnimation++;
	}
}

bool j1EntityManager::Load(pugi::xml_node& save)
{
	
	//DOESNT WORK BECAUSE POSITIONS ARE NOT RIGHT
	CleanUp();

	float x, y;
	int damage;
	//iPoint size;
	int size_x;
	int size_y;
	const char* entityType;

	int numEntities = save.child("num_entities").attribute("value").as_int();

	pugi::xml_node entities_node = save.child("active_entities").child("entity");
	
	

	 App->scenes->WhichMapToLoad = save.child("saved_map").attribute("SavedMap").as_string();


	
	//pugi::xml_node entities = save.child("entities").child("warrior");
	for (int i = 0; i < numEntities; i++) {

		

		x = entities_node.attribute("position_x").as_float();
		y = entities_node.attribute("position_y").as_float();
		damage = entities_node.attribute("missing_hp").as_int();
		size_x = entities_node.attribute("size_x").as_int();
		size_y = entities_node.attribute("size_y").as_int();

		entityType = entities_node.attribute("entity_type").as_string();

		
		int positionX = static_cast<int>(x);
		int positionY= static_cast<int>(y);
		
		if( strcmp(entityType, "townhall") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_TOWN_HALL, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "paintextractor") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_PAINT_EXTRACTOR, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "titaniumextractor") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_TITANIUM_EXTRACTOR, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "woodproducer") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_WOOD_PRODUCER, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "metalgatherer") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_METAL_GATHERER, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "house") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_HOUSE, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "barracks") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_BARRACKS, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "titaniumextractor") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_TITANIUM_EXTRACTOR, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "metalgatherer") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_METAL_GATHERER, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "turret") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_TURRET, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "painter") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_PAINTER, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "warrior") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_WARRIOR, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "knight") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_KNIGHT, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "explorer") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_EXPLORER, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "ranger") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_RANGER, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "spawner") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_SPAWNER, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "slime") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_SLIME, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "chromaking") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_CHROMA_KING, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "rider") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_RIDER, { positionX,positionY }, App->entities, nullptr, 0, true);
		}
		else if (strcmp(entityType, "explosiveblob") == 0) {
			App->entities->AddEntity(ENTITY_TYPE_EXPLOSIVE_BLOB, { positionX,positionY }, App->entities, nullptr, 0, true);

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

			entity.append_attribute("entity_type") =  "painter";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_WARRIOR) {

			entity.append_attribute("entity_type") = "warrior";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_TOWN_HALL) {

			entity.append_attribute("entity_type") = "townhall";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {

			entity.append_attribute("entity_type") = "paintextractor";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_TITANIUM_EXTRACTOR) {

			entity.append_attribute("entity_type") = "titaniumextractor";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_WOOD_PRODUCER) {

			entity.append_attribute("entity_type") = "woodproducer";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_METAL_GATHERER) {

			entity.append_attribute("entity_type") = "metalgatherer";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_HOUSE) {

			entity.append_attribute("entity_type") = "house";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_BARRACKS) {

			entity.append_attribute("entity_type") = "barracks";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_TITANIUM_EXTRACTOR) {

			entity.append_attribute("entity_type") = "titaniumextractor";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_METAL_GATHERER) {

			entity.append_attribute("entity_type") = "metalgatherer";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_TURRET) {

			entity.append_attribute("entity_type") = "turret";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_KNIGHT) {

			entity.append_attribute("entity_type") = "knight";
			entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
			entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
			entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
			entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
			entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_EXPLORER) {

		entity.append_attribute("entity_type") = "explorer";
		entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
		entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
		entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
		entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
		entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_RANGER) {

		entity.append_attribute("entity_type") = "ranger";
		entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
		entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
		entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
		entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
		entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_SPAWNER) {

		entity.append_attribute("entity_type") = "spawner";
		entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
		entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
		entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
		entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
		entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_SLIME) {

		entity.append_attribute("entity_type") = "slime";
		entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
		entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
		entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
		entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
		entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_CHROMA_KING) {

		entity.append_attribute("entity_type") = "chromaking";
		entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
		entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
		entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
		entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
		entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_RIDER) {

		entity.append_attribute("entity_type") = "rider";
		entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
		entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
		entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
		entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
		entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}

		else if ((*entitiesToSave)->entityType == ENTITY_TYPE_EXPLOSIVE_BLOB) {

		entity.append_attribute("entity_type") = "explosiveblob";
		entity.append_attribute("position_x") = (*entitiesToSave)->currentTile.x;
		entity.append_attribute("position_y") = (*entitiesToSave)->currentTile.y;
		entity.append_attribute("missing_hp") = (*entitiesToSave)->GetMaxLife() - (*entitiesToSave)->GetCurrLife();
		entity.append_attribute("size_x") = (*entitiesToSave)->GetSize().x;
		entity.append_attribute("size_y") = (*entitiesToSave)->GetSize().y;
		}




		entitiesToSave++;
	}


	pugi::xml_node currentmap = save.append_child("active_map");

	if (App->scenes->Map_Forest_Active == true) {

		currentmap.append_attribute("SavedMap") = "forest";

	}
	else if (App->scenes->Map_Snow_Active == true) {
		currentmap.append_attribute("SavedMap") = "snow";
	}
	else if (App->scenes->Map_Volcano_Active == true) {
		currentmap.append_attribute("SavedMap") = "volcano";
	}
	

	return true;
}