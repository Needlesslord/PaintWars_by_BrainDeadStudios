#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"
#include "j1Map.h"
#include <vector>
#include "Entity.h"

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), lastPath(DEFAULT_PATH_LENGTH),width(0), height(0)
{
	name = ("pathfinding");
}

// Destructor
j1PathFinding::~j1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	lastPath.clear();
	
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void j1PathFinding::SetMap(uint width, uint height, uchar* data) {
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool j1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
			pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable		OR PAINT
bool j1PathFinding::IsWalkable(const iPoint& pos) const {

	//App->map->data.tilesets.
	uchar t = GetTileAt(pos);
	return t > 0 && ((t != INVALID_WALK_CODE && t != SPAWNER_WALK_CODE) || t == PAINT_WALK_CODE || t == WOOD_WALK_CODE);
}

// Utility: returns true is the tile is paint
bool j1PathFinding::IsPaint(const iPoint& pos) const {

	uchar u = GetTileAt(pos);
	return u > 0 && u == PAINT_WALK_CODE;
}

// Utility: returns true is the tile is wood
bool j1PathFinding::IsWood(const iPoint& pos) const {

	uchar u = GetTileAt(pos);
	return u > 0 && u == WOOD_WALK_CODE;
}

// Utility: returns true is the tile is a spawner
bool j1PathFinding::IsSpawner(const iPoint& pos) const {

	uchar v = GetTileAt(pos);
	return v > 0 && v == SPAWNER_WALK_CODE;
}

// Utility: changes the walkability of a tile to paint
void j1PathFinding::ChangeToPaint(const iPoint& pos) const {

	map[(pos.y*width) + pos.x] = PAINT_WALK_CODE;
}

// Utility: changes the walkability of a tile to wood
void j1PathFinding::ChangeToWood(const iPoint& pos) const {

	iPoint adjacentPos1;
	iPoint adjacentPos2;
	iPoint adjacentPos3;
	iPoint adjacentPos4;

	adjacentPos1.x = pos.x + 1;	adjacentPos1.y = pos.y;
	adjacentPos2.x = pos.x - 1;	adjacentPos2.y = pos.y;
	adjacentPos3.x = pos.x;	adjacentPos3.y = pos.y + 1;
	adjacentPos4.x = pos.x;	adjacentPos4.y = pos.y - 1;

	if (IsWalkable(adjacentPos1)) 
		map[(adjacentPos1.y*width) + adjacentPos1.x] = WOOD_WALK_CODE;

	if (IsWalkable(adjacentPos2))
		map[(adjacentPos2.y*width) + adjacentPos2.x] = WOOD_WALK_CODE;

	if (IsWalkable(adjacentPos3))
		map[(adjacentPos3.y*width) + adjacentPos3.x] = WOOD_WALK_CODE;

	if (IsWalkable(adjacentPos4))
		map[(adjacentPos4.y*width) + adjacentPos4.x] = WOOD_WALK_CODE;
}

// Utility: changes the walkability of a tile to a spawner-container tile
void j1PathFinding::ChangeToSpawner(const iPoint& pos) const {

	map[(pos.y*width) + pos.x] = SPAWNER_WALK_CODE;
	map[((pos.y - 1)*width) + (pos.x - 1)] = SPAWNER_WALK_CODE;
	map[((pos.y - 1)*width) + pos.x] = SPAWNER_WALK_CODE;
	map[(pos.y*width) + (pos.x - 1)] = SPAWNER_WALK_CODE;
}

// Utility: return the walkability value of a tile
uchar j1PathFinding::GetTileAt(const iPoint& pos) const
{
	if(CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

void j1PathFinding::ChangeWalkability(const iPoint& pos, bool isBecomingWalkable, ENTITY_SIZE size) {

	if (size == ENTITY_SIZE_SMALL) {

		if (isBecomingWalkable)
			map[(pos.y*width) + pos.x] = 1;

		else
			map[(pos.y*width) + pos.x] = INVALID_WALK_CODE;
	}

	else if (size == ENTITY_SIZE_MEDIUM) {
	
		if (isBecomingWalkable) {

			map[(pos.y*width) + pos.x] = 1;
			map[((pos.y - 1)*width) + (pos.x - 1)] = 1;
			map[((pos.y - 1)*width) + pos.x] = 1;
			map[(pos.y*width) + (pos.x - 1)] = 1;
		}
		else {

			map[(pos.y*width) + pos.x] = INVALID_WALK_CODE;
			map[((pos.y - 1)*width) + (pos.x - 1)] = INVALID_WALK_CODE;
			map[((pos.y - 1)*width) + pos.x] = INVALID_WALK_CODE;
			map[(pos.y*width) + (pos.x - 1)] = INVALID_WALK_CODE;
		}
	}

	else if (size == ENTITY_SIZE_BIG) {

		if (isBecomingWalkable) {

			map[(pos.y*width) + pos.x] = 1;
			map[((pos.y - 1)*width) + (pos.x - 1)] = 1;
			map[((pos.y - 1)*width) + pos.x] = 1;
			map[(pos.y*width) + (pos.x - 1)] = 1;
			map[((pos.y - 2)*width) + (pos.x - 2)] = 1;
			map[((pos.y - 2)*width) + pos.x] = 1;
			map[(pos.y*width) + (pos.x - 2)] = 1;
			map[((pos.y - 2)*width) + (pos.x - 1)] = 1;
			map[((pos.y - 1)*width) + (pos.x - 2)] = 1;
		}
		else {

			map[(pos.y*width) + pos.x] = INVALID_WALK_CODE;
			map[((pos.y - 1)*width) + (pos.x - 1)] = INVALID_WALK_CODE;
			map[((pos.y - 1)*width) + pos.x] = INVALID_WALK_CODE;
			map[(pos.y*width) + (pos.x - 1)] = INVALID_WALK_CODE;
			map[((pos.y - 2)*width) + (pos.x - 2)] = INVALID_WALK_CODE;
			map[((pos.y - 2)*width) + pos.x] = INVALID_WALK_CODE;
			map[(pos.y*width) + (pos.x - 2)] = INVALID_WALK_CODE;
			map[((pos.y - 2)*width) + (pos.x - 1)] = INVALID_WALK_CODE;
			map[((pos.y - 1)*width) + (pos.x - 2)] = INVALID_WALK_CODE;
		}
	}
}

// To request all tiles involved in the last generated path
const std::vector<iPoint>* j1PathFinding::GetLastPath() const
{
	return &lastPath;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
const PathNode* PathList::Find(const iPoint& point) const {
	 std::list<PathNode>::const_iterator item = list.begin();

	 while (item != list.end())
	 {
		 if ((*item).pos == point)
			 return &(*item);
		 item++;
	 }
	 return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
const PathNode* PathList::GetNodeLowestScore() const {
	const PathNode* ret = NULL;
	int min = 65535;

	// This loop should go from end to begin. Make a tmp list with std::reverse list?
	for (std::list<PathNode>::const_reverse_iterator item = list.rbegin(); item != list.rend(); item++)
	{
		if (item->Score() < min)
		{
			min = item->Score();
			ret = &(*item);
		}
	}

	 return ret;
 }

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent, const bool diagonal = false) : g(g), h(h), pos(pos), parent(parent), diagonal(diagonal)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& listToFill) const {
	iPoint cell;

	// north
	cell.create(pos.x, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		listToFill.list.push_back(PathNode(-1, -1, cell, this));

	// north east
	cell.create(pos.x + 1, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		listToFill.list.push_back(PathNode(-1, -1, cell, this, true));

	// north west
	cell.create(pos.x - 1, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		listToFill.list.push_back(PathNode(-1, -1, cell, this, true));

	// south
	cell.create(pos.x, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		listToFill.list.push_back(PathNode(-1, -1, cell, this));


	// south east
	cell.create(pos.x + 1, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		listToFill.list.push_back(PathNode(-1, -1, cell, this, true));

	// south west
	cell.create(pos.x - 1, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		listToFill.list.push_back(PathNode(-1, -1, cell, this, true));

	// east
	cell.create(pos.x + 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		listToFill.list.push_back(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x - 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
		listToFill.list.push_back(PathNode(-1, -1, cell, this));


	return listToFill.list.size();
}


// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	if (this->diagonal)
		g = parent->g + 1.7f;
	h = pos.DistanceNoSqrt(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int j1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination) {

	int ret = 1;

	// If origin or destination are not walkable, return -1
	if (IsWalkable(destination) == false || origin == destination) {
		return -1;
	}

	// We declare the lists needed to create the path 
	PathList open, closed, adjacent;

	// We add the origin to the open/frontier list 
	open.list.push_back(PathNode(0, 0, origin, NULL));

	// We iterate until no element is left in frontier/open list 
	while (open.list.size() > 0) {
		// We delete the lowest score tile from open and move it to closed, frontier-->visited 
		PathNode* lowest = (PathNode*)open.GetNodeLowestScore();
		closed.list.push_back(*lowest);

		std::list<PathNode>::iterator it = open.list.begin();

		while (it != open.list.end()) {
			if (&(*it) == &(*lowest)) {
				open.list.erase(it);
				break;
			}
			it++;
		}

		// If we find the destination we do backtracking and create the path, breaking the loop 
		if (closed.list.back().pos == destination) {
			lastPath.clear();

			// Backtrack to create the final path
			for (PathNode it = closed.list.back(); it.parent != NULL; it = *closed.Find(it.parent->pos))
			{
				lastPath.push_back(it.pos);
			}

			lastPath.push_back(closed.list.front().pos);

			std::reverse(lastPath.begin(), lastPath.end());
			break;
		}

		// If we have not found the destination we proceed to find the current tile's neighbors 

		// Fill a list with all adjacent nodes
		adjacent.list.clear();
		closed.list.back().FindWalkableAdjacents(adjacent);

		std::list<PathNode>::iterator item = adjacent.list.begin();

		// While we have neighbors left to check ... iterate! 
		for (; item != adjacent.list.end(); item++) {
			// If we find it in the closed list we do not want to continue
			if (closed.Find((*item).pos) == NULL) {
				PathNode adjacentInOpen;

				// If we do not find the neighbor in the open/frontier list we calculate its cost (F) and add it to the list 
				if (open.Find((*item).pos) == NULL)	{
					(*item).CalculateF(destination);
					open.list.push_back(*item);
				}

				// If we have found it in open/frontier list ... 
				else {
					adjacentInOpen = *open.Find((*item).pos);

					// We compare walkable cost and if the neighbor's is bigger than current + offset we know this is a better path and update neighbor's parent and F
					if (adjacentInOpen.diagonal == false) {
						if (adjacentInOpen.g > (*item).g + 1) {
							adjacentInOpen.parent = (*item).parent;
							adjacentInOpen.CalculateF(destination);
						}
					}
				}
			}
		}
	}

	return ret;
}

std::vector<iPoint> j1PathFinding::FindClosestDestination(iPoint destination) {

	std::vector<iPoint> ret;

	PathList closestDestinations;

	PathNode destinationNode;

	destinationNode.pos.x = destination.x;
	destinationNode.pos.y = destination.y;

	destinationNode.FindWalkableAdjacents(closestDestinations);

	while (closestDestinations.list.size() > 0) {
		ret.push_back(closestDestinations.list.back().pos);
		closestDestinations.list.pop_back();
	}

	/*while (ret.size() < 8) {
		ret.push_back({ -1, -1 });
	}*/

	return ret;
}