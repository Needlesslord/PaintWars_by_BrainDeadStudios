#ifndef __Knight_H__
#define __Knight_H__

#include <vector>
#include "Entity.h"

class Knight : public Entity
{
public:

	Knight(iPoint tile, int damage, j1Module* listener, Entity* creator = nullptr);
	~Knight();
	void Attack(Entity* target, float dt);
	void Draw(SDL_Texture* sprites) override;

};

#endif //__Knight_H__