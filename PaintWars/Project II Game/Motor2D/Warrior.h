#ifndef __Warrior_H__
#define __Warrior_H__


#include "Entity.h"

class Warrior : public Entity
{
public:

	Warrior(fPoint pos, int currLife, j1Module* listener);
	~Warrior();
	//void Move(iPoint destination)override;
public:

private:

	bool startTimer = true;

};

#endif //__Warrior_H__