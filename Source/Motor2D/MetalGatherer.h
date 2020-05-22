#ifndef __MetalGatherer_H__
#define __MetalGatherer_H__


#include "Entity.h"

class MetalGatherer : public Entity
{
public:

	MetalGatherer(iPoint tile, int damage, j1Module* listener, Entity* creator);
	~MetalGatherer();

public:

private:

	bool startTimer = true;

};

#endif //__MetalGatherer_H__