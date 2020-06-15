#ifndef __ChromaKing_H__
#define __ChromaKing_H__


#include "Entity.h"

class ChromaKing : public Entity
{
public:

	ChromaKing(iPoint tile, int damage, j1Module* listener);
	~ChromaKing();

	void Draw(SDL_Texture* sprites) override;
	void Attack(Entity* target, float dt);
};

#endif //__ChromaKing_H__