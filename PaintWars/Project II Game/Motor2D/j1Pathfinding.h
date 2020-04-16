#ifndef __j1PATHFINDING_H__
#define __j1PATHFINDING_H__

#include "j1Module.h"
#include "p2Point.h"
#include <list>
#include <vector>
#include "Entity.h"

#define DEFAULT_PATH_LENGTH 50
#define INVALID_WALK_CODE 255
#define PAINT_WALK_CODE 254
#define WOOD_WALK_CODE 253
#define SPAWNER_WALK_CODE 252


//WALKABILITY
#define OCCUPIED 2
#define WALKABLE 1
#define NON_WALKABLE 0


// ----------------------------------------------------------------------
// Recommended reading:
// Intro: http://www.raywenderlich.com/4946/introduction-to-a-pathfinding
// Details: http://theory.stanford.edu/~amitp/GameProgramming/
// ----------------------------------------------------------------------

enum ENTITY_SIZE;

class j1PathFinding : public j1Module
{
public:

	j1PathFinding();

	// Destructor
	~j1PathFinding();

	// Called before quitting
	bool CleanUp();

	// Sets up the walkability map
	void SetMap(uint width, uint height, uchar* data);

	// Main function to request a path from A to B
	int CreatePath(const iPoint& origin, const iPoint& destination);

	// To request all tiles involved in the last generated path
	const std::vector<iPoint>* GetLastPath() const;

	// Utility: return true if pos is inside the map boundaries
	bool CheckBoundaries(const iPoint& pos) const;

	// Utility: returns true is the tile is walkable			OR PAINT...
	bool IsWalkable(const iPoint& pos) const;

	// Utility: returns true is the tile is buildable
	bool IsBuildable(const iPoint& pos) const;

	// Utility: returns true if the tile is paint
	bool IsPaint(const iPoint& pos) const;

	// Utility: returns true if the tile is wood
	bool IsWood(const iPoint& pos) const;

	// Utility: returns true if the tile has a spawner
	bool IsSpawner(const iPoint& pos) const;

	// Utility: changes the walkability of a tile to paint
	void ChangeToPaint(const iPoint& pos) const;
	
	// Utility: changes the walkability of a tile to wood
	void ChangeToWood(const iPoint& pos) const;
	
	// Utility: changes the walkability of a tile to a spawner-container tile
	void ChangeToSpawner(const iPoint& pos) const;

	// Utility: return the walkability value of a tile
	uchar GetTileAt(const iPoint& pos) const;

	void ChangeWalkability(const iPoint& pos, bool isBecomingWalkable, ENTITY_SIZE size = ENTITY_SIZE_SMALL);

	std::vector<iPoint> FindClosestDestination(iPoint destination);

private:

	// size of the map
	uint width;
	uint height;

	// Number of tiles in the map!!!		all map walkability values [0..255]
	uchar* map;
	
	// we store the created path here
	std::vector<iPoint> lastPath;
};

// forward declaration
struct PathList;

// ---------------------------------------------------------------------
// Pathnode: Helper struct to represent a node in the path creation
// ---------------------------------------------------------------------
struct PathNode
{
	// Convenient constructors
	PathNode();
	PathNode(int g, int h, const iPoint& pos, const PathNode* parent, const bool diagonal);
	PathNode(const PathNode& node);

	// Fills a list (PathList) of all valid adjacent pathnodes
	uint FindWalkableAdjacents(PathList& listToFill) const;
	// Calculates this tile score
	int Score() const;
	// Calculate the F for a specific destination tile
	int CalculateF(const iPoint& destination);

	// -----------
	float g;
	float h;
	iPoint pos;
	const PathNode* parent; // needed to reconstruct the path in the end
	bool diagonal = false;
};

// ---------------------------------------------------------------------
// Helper struct to include a list of path nodes
// ---------------------------------------------------------------------
struct PathList
{
	PathList() {}
	// Looks for a node in this list and returns it's list node or NULL
	const PathNode* Find(const iPoint& point) const;

	// Returns the Pathnode with lowest score in this list or NULL if empty
	const PathNode* GetNodeLowestScore() const;

	// -----------
	// The list itself, note they are not pointers!
	std::list<PathNode> list;

};



#endif // __j1PATHFINDING_H__