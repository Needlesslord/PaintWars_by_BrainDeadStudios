#ifndef __Barracks_H__
#define __Barracks_H__


#include "Entity.h"

class Barracks : public Entity
{
public:

	Barracks(iPoint tile, int damage, j1Module* listener, Entity* creator = nullptr);
	~Barracks();

	void SpawnEntity(ENTITY_TYPE type) override;

};

#endif //__Barracks_H__