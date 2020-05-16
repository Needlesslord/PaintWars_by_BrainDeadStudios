#ifndef __Spawner_H__
#define __Spawner_H__


#include "Entity.h"

class Spawner : public Entity
{
public:

	Spawner(iPoint tile, int damage, j1Module* listener);
	~Spawner();

};

#endif //__Spawner_H__