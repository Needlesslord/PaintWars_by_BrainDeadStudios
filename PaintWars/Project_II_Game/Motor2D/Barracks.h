#ifndef __Barracks_H__
#define __Barracks_H__


#include "Entity.h"

class Barracks : public Entity
{
public:

	Barracks(iPoint tile, int damage, j1Module* listener, Entity* creator = nullptr);
	~Barracks();

	void SpawnEntity() override;

public:

private:

	bool startTimer = true;

};

#endif //__Barracks_H__