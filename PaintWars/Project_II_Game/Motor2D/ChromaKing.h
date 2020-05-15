#ifndef __ChromaKing_H__
#define __ChromaKing_H__


#include "Entity.h"

class ChromaKing : public Entity
{
public:

	ChromaKing(iPoint tile, int damage, j1Module* listener);
	~ChromaKing();

	bool goToTownHall();
	bool CanAttackTownHall();
	void attack(Entity* target, float dt);

	
public:

private:

	bool startTimer = true;

};

#endif //__ChromaKing_H__