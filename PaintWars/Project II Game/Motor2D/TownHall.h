#ifndef __TownHall_H__
#define __TownHall_H__


#include "Entity.h"

class TownHall : public Entity
{
public:

	TownHall(fPoint pos, int currLife, j1Module* listener);
	~TownHall();

	void SpawnEntity() override;

public:

private:

	bool startTimer = true;

};

#endif //__TownHall_H__