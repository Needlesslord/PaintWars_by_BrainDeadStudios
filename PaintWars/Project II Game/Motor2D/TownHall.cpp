#include "p2Defs.h"
#include "p2Log.h"

#include "TownHall.h"

#include "j1Player.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"

TownHall::TownHall(fPoint pos, iPoint size, int currLife, uint maxLife, const TownHallInfo& townHallInfo, j1Module* listener) : Entity(pos, size, currLife, maxLife, listener), townHallInfo(townHallInfo) {
	// Handle data and initialize the TH
	CreateEntityCollider(true, true);
}

TownHall::~TownHall() {}