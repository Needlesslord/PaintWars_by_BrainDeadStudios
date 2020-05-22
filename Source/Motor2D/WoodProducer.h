#ifndef __WoodProducer_H__
#define __WoodProducer_H__


#include "Entity.h"

class WoodProducer : public Entity
{
public:

	WoodProducer(iPoint tile, int damage, j1Module* listener, Entity* creator);
	~WoodProducer();

};

#endif //__WoodProducer_H__