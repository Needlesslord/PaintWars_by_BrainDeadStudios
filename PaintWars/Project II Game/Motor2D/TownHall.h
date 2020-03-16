#ifndef __TownHall_H__
#define __TownHall_H__


#include "Entity.h"

struct TownHallInfo
{
	uint TownHallLevel = 1;
	int townHallMaxLife = 0;
	int constructionTime = 0;
	int constructionSpeed = 0;
	iPoint size{ 0,0 };
	uint life = 0;
};

class TownHall : public Entity
{
public:

	TownHall(fPoint pos, iPoint size, int currLife, uint maxLife, const TownHallInfo& townHallInfo, j1Module* listener);
	~TownHall();

public:
	TownHallInfo townHallInfo;

private:
	EntitiesEvent entityEvent = EntitiesEvent_NONE;

	bool startTimer = true;

};

#endif //__TownHall_H__