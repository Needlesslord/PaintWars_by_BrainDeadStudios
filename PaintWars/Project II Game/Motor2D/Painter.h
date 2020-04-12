#ifndef __Painter_H__
#define __Painter_H__


#include "Entity.h"

class Painter : public Entity
{
public:

	Painter(iPoint tile, int damage, j1Module* listener, Entity* creator = nullptr);
	~Painter();
	void SpawnEntity(iPoint pos) override;

public:

private:

	bool startTimer = true;

};

#endif //__Painter_H__