#ifndef __ExplosiveBlob_H__
#define __ExplosiveBlob_H__


#include "Entity.h"

class ExplosiveBlob : public Entity
{
public:

	ExplosiveBlob(iPoint tile, int damage, j1Module* listener);
	~ExplosiveBlob();
	void hasExploded();

};

#endif //__ExplosiveBlob_H__