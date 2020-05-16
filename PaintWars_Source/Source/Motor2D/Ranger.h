#ifndef __Ranger_H__
#define __Ranger_H__

#include <vector>
#include "Entity.h"

class Ranger : public Entity
{
public:

	Ranger(iPoint tile, int damage, j1Module* listener, Entity* creator = nullptr);
	~Ranger();
	void Attack(Entity* target, float dt);
	void Draw(SDL_Texture* sprites) override;

private:

public:

private:

	bool startTimer = true;

};

#endif //__Ranger_H__