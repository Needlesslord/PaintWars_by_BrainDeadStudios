#ifndef __Explorer_H__
#define __Explorer_H__


#include "Entity.h"
#include "j1Timer.h"
class Explorer : public Entity
{
public:

	Explorer(iPoint tile, int damage, j1Module* listener, Entity* creator = nullptr);
	~Explorer();
	void Draw(SDL_Texture* sprites) override;

};

#endif //__Explorer_H__