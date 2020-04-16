#include "p2Log.h"
#include <vector>

#include "Entity.h"

#include "j1App.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Map.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "j1Player.h"

Entity::Entity(iPoint tile, int damage, j1Module* listeners, Entity* creator) : currentTile(tile), currLife(maxLife - damage), listener(listener), spawnedBy(creator)
{
	if (this->currLife == 0)
		this->currLife = this->maxLife;

	isOnTheMove = false;
	isAlive = true;
	spawningProgress = 0;

}

Entity::~Entity() {
	if (entityCollider != nullptr)
		entityCollider->to_delete = true;
}

void Entity::Draw(SDL_Texture* sprites) {
	if (sprites != nullptr)
		App->render->AddBlitEvent(1, sprites, pos.x, pos.y, { 0, 0, size.x, size.y });
}

void Entity::DebugDrawSelected()
{
}

void Entity::OnCollision(Collider* c1, Collider* c2, CollisionState collisionState) {


  
}

void Entity::CalculateMovementLogic(int p) {

	iPoint cameraW = App->map->WorldToMap(App->render->camera.x, App->render->camera.y);
	iPoint map_coordinates = App->map->WorldToMap(pos.x - cameraW.x /*+ App->map->data.tile_width / 2*/, pos.y - cameraW.y + App->map->data.tile_height / 2);

	iPoint mapPos = App->map->WorldToMap(pos.x, pos.y);
	fPoint worldDestination = App->map->MapToWorld(destination.x, destination.y);

	map_coordinates = currentTile;
	// If he's at the destination he doesn't have to move so we exit
	if (destination == map_coordinates) {

		isOnTheMove = false;
		return;
	}

	if (App->pathfinding->IsSpawner(destination)) {

		for (int i = 0; i < App->pathfinding->FindClosestDestination(destination).size(); i++) {

			if (App->pathfinding->IsWalkable(App->pathfinding->FindClosestDestination(destination).at(i))) {

				target = destination;
				destination = App->pathfinding->FindClosestDestination(destination).at(0);
				break;
			}
		}
	}

	int map;
	map = App->pathfinding->CreatePath(map_coordinates, destination);
	currentPath = *App->pathfinding->GetLastPath();

	

	if (map != -1) {

		if (p > 0) {

			if (p <= App->pathfinding->FindClosestDestination(destination).size()) {

				if (App->pathfinding->IsWalkable(App->pathfinding->FindClosestDestination(destination).at(p - 1))) {

					iPoint closestDestination = App->pathfinding->FindClosestDestination(destination).at(p - 1);
					destination = closestDestination;
				}
			}

			//else { // This can never be for now because the maximum of units selected is 9 so p will never be 9 or greater
			//	// We store the 8 closest in a vector
			//	std::vector<iPoint> closestDestinationList;
			//	for (int i = 0; i < 8; i++) {
			//		closestDestinationList.push_back(App->pathfinding->FindClosestDestination(destination).at(i));
			//	}
			//	
			//	iPoint cD2cD;
			//	bool exit = false;
			//	for (int i = 0; i < 8; i++) {
			//		if (exit) break;
			//		cD2cD = App->pathfinding->FindClosestDestination(closestDestinationList.at(p - 9)).at(i);
			//		for (int j = 0; j < 8; j++) {
			//			if (cD2cD != closestDestinationList.at(j)) {
			//				destination = cD2cD;

			//				exit = true;
			//				break;
			//			}
			//		}
			//	}
			//}
		}


		if (map_coordinates.x < destination.x) {

			if (map_coordinates.y < destination.y) {
				*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_SOUTH;
			}
			else if (map_coordinates.y > destination.y) {
				*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_EAST;
			}
			else {
				*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_SOUTH_EAST;
			}
		}

		else if (map_coordinates.x > destination.x) {

			if (map_coordinates.y < destination.y) {
				*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_WEST;
			}
			else if (map_coordinates.y > destination.y) {
				*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NORTH;
			}
			else {
				*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NORTH_WEST;
			}
		}

		else if (map_coordinates.x == destination.x) {

			if (map_coordinates.y < destination.y) {
				*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_SOUTH_WEST;
			}
			else if (map_coordinates.y > destination.y) {
				*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NORTH_EAST;
			}
			else {
				*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;
			}
		}

		isOnTheMove = true;
	}

	else {
		*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;
		isOnTheMove = false;
	}
}

void Entity::Move(float dt) {
	
	fPoint fDestination= App->map->MapToWorld(destination.x, destination.y);
	fPoint worldDestination;

	worldDestination.x = fDestination.x + App->map->data.tile_width / 2 - size.x / 2;
	worldDestination.y = fDestination.y + App->map->data.tile_height / 2 - size.y;
	
	if (unitOrientation == UNIT_ORIENTATION_NONE) {
		return;
	}
	else if (unitOrientation == UNIT_ORIENTATION_NORTH) {

		pos.y -= speed * dt;
		
		if (pos.y < worldDestination.y) {
			pos.y = worldDestination.y;
		}

		if (pos.x < worldDestination.x) {

			pos.x += speed * dt / 2;

			if (pos.x >= worldDestination.x) {
				pos.x = worldDestination.x;
			}
		}

		else if (pos.x > worldDestination.x) {

			pos.x -= speed * dt / 2;

			if (pos.x <= worldDestination.x) {
				pos.x = worldDestination.x;
			}
		}
	}

	else if (unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

		pos.x += speed * dt / 2;
		pos.y -= speed * dt / 2;

		if (pos.x >= worldDestination.x) {
			pos.x = worldDestination.x;
		}
		if (pos.y < worldDestination.y) {
			pos.y = worldDestination.y;
		}
	}

	else if (unitOrientation == UNIT_ORIENTATION_EAST) {

		pos.x += speed * dt;

		if (pos.x >= worldDestination.x) {
			pos.x = worldDestination.x;
		}

		if (pos.y < worldDestination.y) {

			pos.y += speed * dt / 2;

			if (pos.y >= worldDestination.y) {
				pos.y = worldDestination.y;
			}
		}

		else if (pos.y > worldDestination.y) {

			pos.y -= speed * dt / 2;

			if (pos.y <= worldDestination.y) {
				pos.y = worldDestination.y;
			}
		}
	}
	else if (unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

		pos.x += speed * dt / 2;
		pos.y += speed * dt / 2;

		if (pos.x >= worldDestination.x) {
			pos.x = worldDestination.x;
		}
		if (pos.y > worldDestination.y) {
			pos.y = worldDestination.y;
		}
	}
	else if (unitOrientation == UNIT_ORIENTATION_SOUTH) {

		pos.y += speed * dt;
		
		if (pos.y > worldDestination.y) {
			pos.y = worldDestination.y;
		}

		if (pos.x <= worldDestination.x) {

			pos.x += speed * dt / 2;

			if (pos.x >= worldDestination.x) {
				pos.x = worldDestination.x;
			}
		}

		else if (pos.x >= worldDestination.x) {

			pos.x -= speed * dt / 2;

			if (pos.x <= worldDestination.x) {
				pos.x = worldDestination.x;
			}

		}
	}
	else if (unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

		pos.x -= speed * dt / 2;
		pos.y += speed * dt / 2;

		if (pos.x <= worldDestination.x) {
			pos.x = worldDestination.x;
		}
		if (pos.y > worldDestination.y) {
			pos.y = worldDestination.y;
		}
	}
	else if (unitOrientation == UNIT_ORIENTATION_WEST) {

		pos.x -= speed * dt;

		if (pos.x < worldDestination.x) {
			pos.x = worldDestination.x;
		}
		// TODO HERE
		if (pos.y < worldDestination.y) {

			pos.y += speed * dt / 2;

			if (pos.y >= worldDestination.y) {
				pos.y = worldDestination.y;
			}
		}

		else if (pos.y > worldDestination.y) {

			pos.y -= speed * dt / 2;

			if (pos.y <= worldDestination.y) {
				pos.y = worldDestination.y;
			}
		}
	}
	else if (unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

		pos.x -= speed * dt / 2;
		pos.y -= speed * dt / 2;

		if (pos.x < worldDestination.x) {
			pos.x = worldDestination.x;
		}
		if (pos.y < worldDestination.y) {
			pos.y = worldDestination.y;
		}
	}
	/*if (currentTile == destination)
		isOnTheMove = false;*/
}

void Entity::SetDestination(iPoint des) {
	this->destination = des;
}

void Entity::SpawnEntity(iPoint pos) {}

void Entity::ExtractPaint(float dt) {}

void Entity::ExtractWood(float dt) {}

void Entity::Attack(Entity* target, float dt) {}

// -------------------------------------------------------------

// Position and size
void Entity::SetPos(fPoint pos)
{
	this->pos = pos;
}

fPoint Entity::GetPos() const
{
	return pos;
}

iPoint Entity::GetSize() const
{
	return size; 
}

iPoint Entity::GetOffsetSize() const
{
	return offsetSize;
}

void Entity::SetMaxLife(int life)
{
	maxLife = life;
}

// Life and damage
float Entity::GetMaxLife() const
{
	return maxLife;
}

void Entity::SetCurrLife(int currLife)
{
	this->currLife = currLife;
}

float Entity::GetCurrLife() const
{
	return currLife;
}

void Entity::ApplyDamage(float damage)
{
	currLife -= damage;
	if (currLife < 0)
		currLife = 0;
}

void Entity::ApplyHealth(float health) 
{
	if (currLife + health >= maxLife)
		currLife = maxLife;
	else
		currLife += health;

}

// Collision
Collider* Entity::GetEntityCollider() const
{
	return entityCollider;
}

bool Entity::CreateEntityCollider(fPoint pos) {

		// Allies
	/// Buildings
	if (entityType == ENTITY_TYPE_TOWN_HALL) {
		COLLIDER_TYPE collType = COLLIDER_ALLY_BUILDING;
		SDL_Rect rect = { pos.x, pos.y, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);

		return true;
	}

	else if (entityType == ENTITY_TYPE_PAINT_EXTRACTOR) {
		COLLIDER_TYPE collType = COLLIDER_ALLY_BUILDING;
		SDL_Rect rect = { pos.x, pos.y, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);

		return true;
	}

	else if (entityType == ENTITY_TYPE_WOOD_PRODUCER) {
		COLLIDER_TYPE collType = COLLIDER_ALLY_BUILDING;
		SDL_Rect rect = { pos.x, pos.y, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);

		return true;
	}

	else if (entityType == ENTITY_TYPE_HOUSE) {
		COLLIDER_TYPE collType = COLLIDER_ALLY_BUILDING;
		SDL_Rect rect = { pos.x, pos.y, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);

		return true;
	}

	else if (entityType == ENTITY_TYPE_BARRACKS) {
		COLLIDER_TYPE collType = COLLIDER_ALLY_BUILDING;
		SDL_Rect rect = { pos.x, pos.y, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);

		return true;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_PAINTER) {
		COLLIDER_TYPE collType = COLLIDER_ALLY_UNIT;
		SDL_Rect rect = { pos.x, pos.y, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);

		return true;
	}

	else if (entityType == ENTITY_TYPE_WARRIOR) {
		COLLIDER_TYPE collType = COLLIDER_ALLY_UNIT;
		SDL_Rect rect = { pos.x, pos.y, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);

		return true;
	}
		
		// Enemies
	/// Buildings
	else if (entityType == ENTITY_TYPE_SPAWNER) {
		COLLIDER_TYPE collType = COLLIDER_ENEMY_BUILDING;
		SDL_Rect rect = { pos.x, pos.y, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);

		return true;
	}

	/// Units
	else if (entityType == ENTITY_TYPE_SLIME) {
		COLLIDER_TYPE collType = COLLIDER_ENEMY_UNIT;
		SDL_Rect rect = { pos.x, pos.y, GetSize().x, GetSize().y };
		entityCollider = App->col->AddCollider(rect, collType, App->entities);

		return true;
	}

	else
		return false;
}

void Entity::ShowHealthBar() {
	if (GetCurrLife() != GetMaxLife()) {
		App->render->AddBlitEvent(1, App->entities->zeroLifeTexture, pos.x, pos.y - 20 - GetSize().y / 4, { 0, 0, GetSize().x, 10 });
	}
	App->render->AddBlitEvent(1, App->entities->fullLifeTexture, pos.x, pos.y - 20 - GetSize().y / 4, { 0, 0, (int)((currLife/maxLife)*GetSize().x), 10 });
}

void Entity::ShowUI() {

	if (entityType == ENTITY_TYPE_TOWN_HALL) {

		if (App->entities->spawnEntityUIButton == nullptr) { // To spawn a painter
			App->entities->spawnEntityUIButton = App->col->AddCollider({ 200, 800, 50, 50 }, COLLIDER_UI, App->entities);
		}

		App->render->AddBlitEventforUI(2, App->entities->fullLifeTexture, 200, 800, { 0,0,50,50 }, false, false, 0);
	}
	
	else if (entityType == ENTITY_TYPE_BARRACKS) {

		if (App->entities->spawnEntityUIButton == nullptr) { // To spawn a warrior
			App->entities->spawnEntityUIButton = App->col->AddCollider({ 200, 800, 50, 50 }, COLLIDER_UI, App->entities);
		}

		App->render->AddBlitEventforUI(2, App->entities->fullLifeTexture, 200, 800, { 0,0,50,50 }, false, false, 0);
	}

	else if (entityType == ENTITY_TYPE_PAINTER) {

		if (App->entities->buildEntityUIButton == nullptr) { // To build a TH
			App->entities->buildEntityUIButton = App->col->AddCollider({ 200, 800, 50, 50 }, COLLIDER_UI, App->entities);
		}

		App->render->AddBlitEventforUI(2, App->entities->fullLifeTexture, 200, 800, { 0,0,50,50 }, false, false, 0);
	}
}