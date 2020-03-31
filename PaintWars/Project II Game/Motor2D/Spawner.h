#ifndef __Spawner_H__
#define __Spawner_H__


#include "Entity.h"

class Spawner : public Entity
{
public:

	Spawner(fPoint pos, int currLife, j1Module* listener);
	~Spawner();

public:

private:

	bool startTimer = true;

};

#endif //__Spawner_H__