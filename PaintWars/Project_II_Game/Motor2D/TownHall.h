#ifndef __TownHall_H__
#define __TownHall_H__


#include "Entity.h"

class TownHall : public Entity
{
public:

	TownHall(iPoint tile, int damage, j1Module* listener, Entity* creator = nullptr);
	~TownHall();

	void SpawnEntity(iPoint pos) override;

public:

private:

	bool startTimer = true;

};

#endif //__TownHall_H__