#ifndef __Rider_H__
#define __Rider_H__


#include "Entity.h"

class Rider : public Entity
{
public:

	Rider(iPoint tile, int damage, j1Module* listener);
	~Rider();

public:

private:

	bool startTimer = true;

};

#endif //__Rider_H__