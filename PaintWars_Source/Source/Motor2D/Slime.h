#ifndef __Slime_H__
#define __Slime_H__


#include "Entity.h"

class Slime : public Entity
{
public:

	Slime(iPoint tile, int damage, j1Module* listener);
	~Slime();
	void Draw(SDL_Texture* sprites) override;
	void Attack(Entity* target, float dt);

};

#endif //__Slime_H__