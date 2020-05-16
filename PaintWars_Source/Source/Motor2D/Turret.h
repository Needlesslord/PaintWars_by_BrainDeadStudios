#ifndef __Turret_H__
#define __Turret_H__


#include "Entity.h"

class Turret : public Entity
{
public:

	Turret(iPoint tile, int damage, j1Module* listener, Entity* creator);
	~Turret();

	void Attack(Entity* target, float dt);


public:

private:

	bool startTimer = true;

};

#endif //__Turret_H__