#ifndef __Slime_H__
#define __Slime_H__


#include "Entity.h"

class Slime : public Entity
{
public:

	Slime(fPoint pos, int currLife, j1Module* listener);
	~Slime();
	//void Move(iPoint destination)override;
public:

private:

	bool startTimer = true;

};

#endif //__Slime_H__