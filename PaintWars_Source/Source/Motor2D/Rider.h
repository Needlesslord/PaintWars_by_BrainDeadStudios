#ifndef __Rider_H__
#define __Rider_H__


#include "Entity.h"

class Rider : public Entity
{
public:

	Rider(iPoint tile, int damage, j1Module* listener);
	~Rider();

	void Attack(Entity* target, float dt);

};

#endif //__Rider_H__