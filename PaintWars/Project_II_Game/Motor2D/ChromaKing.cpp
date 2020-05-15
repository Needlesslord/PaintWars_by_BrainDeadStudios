#include "ChromaKing.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

ChromaKing::ChromaKing(iPoint tile, int damage, j1Module* listener) : Entity(tile, damage, listener, nullptr) {

	// Handle data and initialize the Warrior
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_CHROMA_KING;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_MEDIUM;

	maxLife = 500;
	currLife = maxLife - damage;

	size = { 20, 20 }; //has to be changed

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	speed = 80;

	spawningTime = 1.0f;

	destination = currentTile;

	isEntityFromPlayer = false;
}

ChromaKing::~ChromaKing() {}

bool ChromaKing::goToTownHall() {

	bool ret = true;

	fPoint positionTownHallForest = { 0,0 };
	fPoint positionTownHallVolcano = { 0,0 };
	fPoint positionTownHallSnow = { 0,0 };

	if (CanAttackTownHall())
		ret = false;
	else
	{
		//direction towards TH 
		ret = true;
	}

	return ret;

}


bool ChromaKing::CanAttackTownHall() {

	bool ret = false;

	if (/*pos CK is next to the tiles of the TH*/ret)
	{
		ret = true;
	}

	return ret;

}


bool ChromaKing::attackingTownHall() {

	bool ret = false;

	if (CanAttackTownHall())
	{
		ret = true;

		//make damage to the TH

	}

	return ret;

}