#ifndef __Slime_H__
#define __Slime_H__


#include "Entity.h"

class Slime : public Entity
{
public:

	Slime(iPoint tile, int damage, j1Module* listener);
	~Slime();

public:

private:

	bool startTimer = true;

};

#endif //__Slime_H__