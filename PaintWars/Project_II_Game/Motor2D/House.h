#ifndef __House_H__
#define __House_H__


#include "Entity.h"

class House : public Entity
{
public:

	House(iPoint tile, int damage, j1Module* listener, Entity* creator);
	~House();

public:

private:

	bool startTimer = true;

};

#endif //__House_H__