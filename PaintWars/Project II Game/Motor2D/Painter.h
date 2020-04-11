#ifndef __Painter_H__
#define __Painter_H__


#include "Entity.h"

class Painter : public Entity
{
public:

	Painter(fPoint pos, int currLife, j1Module* listener, Entity* creator);
	~Painter();
	void SpawnEntity(iPoint pos) override;

public:

private:

	bool startTimer = true;

};

#endif //__Painter_H__