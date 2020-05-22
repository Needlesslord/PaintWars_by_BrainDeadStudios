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
#include "Brofiler/Brofiler.h"


Entity::Entity(iPoint tile, int damage, j1Module* listeners, Entity* creator) : currentTile(tile), currLife(maxLife - damage), listener(listener), spawnedBy(creator)
{
	if (this->currLife == 0)
		this->currLife = this->maxLife;

	isOnTheMove = false;
	isAlive = true;
	spawningProgress = 0;

	fow_entity = App->fow->CreateFOWEntity(currentTile, true);

}

Entity::~Entity() {
	if (entityCollider != nullptr)
		entityCollider->to_delete = true;
}

void Entity::Draw(SDL_Texture* sprites) {
	if (sprites != nullptr)
		App->render->RenderQueue(1, sprites, pos.x, pos.y, { 0, 0, size.x, size.y });
}

void Entity::DebugDrawSelected()
{
}

void Entity::OnCollision(Collider* c1, Collider* c2) {

  
}

void Entity::CalculateMovementLogic() {
	BROFILER_CATEGORY("Calculate Movement Logic--Entities();", Profiler::Color::Red);

	// If he's at the destination he doesn't have to move so we exit
	if (destination == currentTile) {

		isOnTheMove = false;
		*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;
		return;
	}

	/*if (App->pathfinding->IsSpawner(destination)) {

		for (int i = 0; i < App->pathfinding->FindClosestDestination(destination).size(); i++) {

			if (App->pathfinding->IsWalkable(App->pathfinding->FindClosestDestination(destination).at(i))) {

				target = destination;
				destination = App->pathfinding->FindClosestDestination(destination).at(0);
				break;
			}
		}
	}*/

	int map;
	map = App->pathfinding->CreatePath(currentTile, destination);
	currentPath = *App->pathfinding->GetLastPath();
	pathIterator = 1;
	nextTile = currentPath.at(pathIterator);
	

	if (map != -1) {

		isOnTheMove = true;
	}

	else {
		*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;
		isOnTheMove = false;
		destination = currentTile;
	}
}

void Entity::MovementLogic() {
	BROFILER_CATEGORY("Movement Logic--Entities();", Profiler::Color::OrangeRed);

	if (currentTile.x < nextTile.x) {

		if (currentTile.y < nextTile.y) {
			previousOrientation = unitOrientation;
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_SOUTH;
		}
		else if (currentTile.y > nextTile.y) {
			previousOrientation = unitOrientation;
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_EAST;
		}
		else {
			previousOrientation = unitOrientation;
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_SOUTH_EAST;
		}
	}

	else if (currentTile.x > nextTile.x) {

		if (currentTile.y < nextTile.y) {
			previousOrientation = unitOrientation;
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_WEST;
		}
		else if (currentTile.y > nextTile.y) {
			previousOrientation = unitOrientation;
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NORTH;
		}
		else {
			previousOrientation = unitOrientation;
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NORTH_WEST;
		}
	}

	else if (currentTile.x == nextTile.x) {

		if (currentTile.y < nextTile.y) {
			previousOrientation = unitOrientation;
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_SOUTH_WEST;
		}
		else if (currentTile.y > nextTile.y) {
			previousOrientation = unitOrientation;
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NORTH_EAST;
		}
		else {
			previousOrientation = unitOrientation;
			isOnTheMove = false;
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;
		}
	}
}

void Entity::Move(float dt) {

	if (App->entities->spacePressed)
		return;

	BROFILER_CATEGORY("Move--Entities();", Profiler::Color::PaleVioletRed);
	fPoint fNextTile = App->map->MapToWorld(nextTile.x, nextTile.y);
	fPoint nextTilePos;
	
	nextTilePos.x = fNextTile.x + App->map->data.tile_width / 2 - size.x / 2;
	nextTilePos.y = fNextTile.y + App->map->data.tile_height / 2 - size.y;

	if (unitOrientation == UNIT_ORIENTATION_NONE) {
		return;
	}
	else if (unitOrientation == UNIT_ORIENTATION_NORTH) {

		pos.y -= speed * dt;

		if (pos.y < nextTilePos.y) {
			pos.y = nextTilePos.y;
		}

		if (pos.x < nextTilePos.x) {

			pos.x += speed * dt;

			if (pos.x > nextTilePos.x) {
				pos.x = nextTilePos.x;
			}
		}

		else if (pos.x > nextTilePos.x) {

			pos.x -= speed * dt;

			if (pos.x < nextTilePos.x) {
				pos.x = nextTilePos.x;
			}
		}
	}

	else if (unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {

		pos.x += speed * dt;
		pos.y -= speed * dt / 2;

		if (pos.x > nextTilePos.x) {
			pos.x = nextTilePos.x;
		}
		if (pos.y < nextTilePos.y) {
			pos.y = nextTilePos.y;
		}
	}

	else if (unitOrientation == UNIT_ORIENTATION_EAST) {

		pos.x += speed * dt;

		if (pos.x > nextTilePos.x) {
			pos.x = nextTilePos.x;
		}

		if (pos.y < nextTilePos.y) {

			pos.y += speed * dt / 2;

			if (pos.y > nextTilePos.y) {
				pos.y = nextTilePos.y;
			}
		}

		else if (pos.y > nextTilePos.y) {

			pos.y -= speed * dt / 2;

			if (pos.y < nextTilePos.y) {
				pos.y = nextTilePos.y;
			}
		}
	}
	else if (unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {

		pos.x += speed * dt;
		pos.y += speed * dt / 2;

		if (pos.x > nextTilePos.x) {
			pos.x = nextTilePos.x;
		}
		if (pos.y > nextTilePos.y) {
			pos.y = nextTilePos.y;
		}
	}
	else if (unitOrientation == UNIT_ORIENTATION_SOUTH) {

		pos.y += speed * dt;

		if (pos.y > nextTilePos.y) {
			pos.y = nextTilePos.y;
		}

		if (pos.x < nextTilePos.x) {

			pos.x += speed * dt;

			if (pos.x > nextTilePos.x) {
				pos.x = nextTilePos.x;
			}
		}

		else if (pos.x > nextTilePos.x) {

			pos.x -= speed * dt;

			if (pos.x < nextTilePos.x) {
				pos.x = nextTilePos.x;
			}

		}
	}
	else if (unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {

		pos.x -= speed * dt;
		pos.y += speed * dt / 2;

		if (pos.x < nextTilePos.x) {
			pos.x = nextTilePos.x;
		}
		if (pos.y > nextTilePos.y) {
			pos.y = nextTilePos.y;
		}
	}
	else if (unitOrientation == UNIT_ORIENTATION_WEST) {

		pos.x -= speed * dt;

		if (pos.x < nextTilePos.x) {
			pos.x = nextTilePos.x;
		}
		
		if (pos.y < nextTilePos.y) {

			pos.y += speed * dt / 2;

			if (pos.y > nextTilePos.y) {
				pos.y = nextTilePos.y;
			}
		}

		else if (pos.y > nextTilePos.y) {

			pos.y -= speed * dt / 2;

			if (pos.y < nextTilePos.y) {
				pos.y = nextTilePos.y;
			}
		}
	}
	else if (unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {

		pos.x -= speed * dt;
		pos.y -= speed * dt / 2;

		if (pos.x < nextTilePos.x) {
			pos.x = nextTilePos.x;
		}
		if (pos.y < nextTilePos.y) {
			pos.y = nextTilePos.y;
		}
	}
	iPoint mapPosition = App->map->WorldToMap(pos.x - App->map->data.tile_width / 2 + GetSize().x / 2, pos.y - App->map->data.tile_height / 2 + GetSize().y);
	currentTile.x = mapPosition.x + 1;
	currentTile.y = mapPosition.y;

	//mapPosition = App->map->WorldToMap(nextTilePos.x - App->map->data.tile_width / 2 + GetSize().x / 2, nextTilePos.y - App->map->data.tile_height / 2 + GetSize().y);
	//nextTile.x = mapPosition.x + 1;
	//nextTile.y = mapPosition.y;

	if (currentTile == nextTile) {
		if (currentTile != destination)
			pathIterator++;
	}

	if (pathIterator < currentPath.size()) {
		nextTile = currentPath.at(pathIterator);
	}

	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	/*pos.x == tileWorldPosition.x + App->map->data.tile_width / 2 - GetSize().x / 2 &&
	pos.y == tileWorldPosition.y + App->map->data.tile_height / 2 - GetSize().y*/

	if (currentTile == destination && pos.x == tileWorldPosition.x + App->map->data.tile_width / 2 - GetSize().x / 2 &&
		pos.y == tileWorldPosition.y + App->map->data.tile_height / 2 - GetSize().y) {
		
		isOnTheMove = false;
		previousOrientation = unitOrientation;
		*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;
	}
}


void Entity::SetDestination(iPoint des) {
	this->destination = des;
}

void Entity::SpawnEntity(ENTITY_TYPE type) {}

void Entity::ExtractPaint(float dt) {}

void Entity::ExtractWood(float dt) {}

void Entity::ExtractTitanium(float dt) {}

void Entity::ExtractMetalScrap(float dt) {}

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

bool Entity::CreateEntityCollider(fPoint pos, Entity* entity) {
	BROFILER_CATEGORY("Create Entity Collider--Entities();", Profiler::Color::IndianRed);

	COLLIDER_TYPE collType = COLLIDER_ALLY_BUILDING;
	SDL_Rect rect = { pos.x, pos.y, GetSize().x, GetSize().y };
	entityCollider = App->col->AddCollider(rect, collType, entity, App->entities);

	return true;
}

void Entity::ShowHealthBar() {

	if (isAlive) {
		if (GetCurrLife() != GetMaxLife()) {
			App->render->RenderQueue(1, App->entities->zeroLifeTexture, pos.x, pos.y - 20 - GetSize().y / 4, { 0, 0, GetSize().x, 10 });
		}
		App->render->RenderQueue(1, App->entities->fullLifeTexture, pos.x, pos.y - 20 - GetSize().y / 4, { 0, 0, (int)((currLife / maxLife)*GetSize().x), 10 });
	}
}

void Entity::ShowProgressBar() {

	if (entityCategory == ENTITY_CATEGORY_STATIC_ENTITY) {

		App->render->RenderQueue(1, App->entities->zeroProgressTexture, pos.x, pos.y - 20 - GetSize().y / 4, { 0, 0, GetSize().x, 30 });
		App->render->RenderQueue(1, App->entities->progressTexture, pos.x, pos.y - 20 - GetSize().y / 4, { 0, 0, (int)((constructionProgress / constructionTime) * GetSize().x), 30 });
	}
	else if (entityCategory == ENTITY_CATEGORY_DYNAMIC_ENTITY) {

		App->render->RenderQueue(1, App->entities->zeroProgressTexture, spawnedBy->pos.x, spawnedBy->pos.y - 20 - spawnedBy->GetSize().y / 4, { 0, 0, spawnedBy->GetSize().x, 30 });
		App->render->RenderQueue(1, App->entities->progressTexture, spawnedBy->pos.x, spawnedBy->pos.y - 20 - spawnedBy->GetSize().y / 4, { 0, 0, (int)((spawningProgress / spawningTime) * spawnedBy->GetSize().x), 30 });
	}
}