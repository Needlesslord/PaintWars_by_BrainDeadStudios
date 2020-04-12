#ifndef __Warrior_H__
#define __Warrior_H__

#include <vector>
#include "Entity.h"

class Warrior : public Entity
{
public:

	Warrior(iPoint tile, int damage, j1Module* listener, Entity* creator = nullptr);
	~Warrior();

private:

public:

private:

	bool startTimer = true;

};

#endif //__Warrior_H__