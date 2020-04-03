#include "p2Defs.h"
#include "p2Log.h"
#include <vector>

#include "Warrior.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"
#include "j1Render.h"

Warrior::Warrior(fPoint pos, int damage, j1Module* listener) : Entity(pos, damage, listener) {

	// Handle data and initialize the Warrior
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_WARRIOR;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_MINI;
	*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;
	maxLife = 30;
	this->currLife = maxLife - damage;
	this->pos = pos;

	speed = 100;

	iPoint mapPos = App->map->WorldToMap(pos.x, pos.y);
	destination = mapPos;

	size = { 62, 118 };
	isEntityFromPlayer = true;
	CreateEntityCollider(pos);
}

Warrior::~Warrior() {}

void Warrior::CalculateMovementLogic() {
	iPoint mapPos = App->map->WorldToMap(pos.x, pos.y);

	// If he's at the destination he doesn't have to move so we exit
	if (destination == mapPos) {
		nextTile = destination;
		isOnTheMove = false;
		return;
	}

	App->pathfinding->CreatePath(mapPos, destination);
	currentPath = *App->pathfinding->GetLastPath();

	nextTile = currentPath.at(1);

	if (mapPos.x < nextTile.x) {
		*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_EAST;

		if (mapPos.y < nextTile.y) {
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_SOUTH_EAST;
		}
		else if (mapPos.y > nextTile.y) {
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NORTH_EAST;
		}
	}

	else if (mapPos.x > nextTile.x) {
		*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_WEST;

		if (mapPos.y < nextTile.y) {
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_SOUTH_WEST;
		}
		else if (mapPos.y > nextTile.y) {
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NORTH_WEST;
		}
	}

	else if (mapPos.x == nextTile.x) {
		*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NONE;

		if (mapPos.y < nextTile.y) {
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_SOUTH;
		}
		else if (mapPos.y > nextTile.y) {
			*(UNIT_ORIENTATION*)&unitOrientation = UNIT_ORIENTATION_NORTH;
		}
	}

	isOnTheMove = true;
	
}

void Warrior::Move(float dt) {
	fPoint worldDestination = App->map->MapToWorld(destination.x, destination.y);
	iPoint mapPos = App->map->WorldToMap(pos.x, pos.y);
	if (unitOrientation == UNIT_ORIENTATION_NONE) {
		return;
	}
	else if (unitOrientation == UNIT_ORIENTATION_NORTH) {
		pos.y -= speed * dt;
		//if (pos.y < worldDestination.y) pos.y = worldDestination.y;
	}
	else if (unitOrientation == UNIT_ORIENTATION_NORTH_EAST) {
		pos.y -= speed * dt / 2;
		pos.x += speed * dt / 2;
	}
	else if (unitOrientation == UNIT_ORIENTATION_EAST) {
		pos.x += speed * dt;
	}
	else if (unitOrientation == UNIT_ORIENTATION_SOUTH_EAST) {
		pos.y += speed * dt / 2;
		pos.x += speed * dt / 2;
		//if (pos.y > worldDestination.y) { pos.y = worldDestination.y; destination = mapPos; }
		//if (pos.x > worldDestination.x) { pos.x = worldDestination.x; destination = mapPos; }
	}
	else if (unitOrientation == UNIT_ORIENTATION_SOUTH) {
		pos.y += speed * dt;
	}
	else if (unitOrientation == UNIT_ORIENTATION_SOUTH_WEST) {
		pos.y += speed * dt / 2;
		pos.x -= speed * dt / 2;
	}
	else if (unitOrientation == UNIT_ORIENTATION_WEST) {
		pos.x -= speed * dt;
	}
	else if (unitOrientation == UNIT_ORIENTATION_NORTH_WEST) {
		pos.y -= speed * dt / 2;
		pos.x -= speed * dt / 2;
		//if (pos.y < worldDestination.y) pos.y = worldDestination.y;
		//if (pos.x < worldDestination.x) pos.x = worldDestination.x;
	}
}

void Warrior::SetDestination(iPoint des) {
	this->destination = des;
}
