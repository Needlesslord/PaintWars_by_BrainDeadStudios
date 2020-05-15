#ifndef __Painter_H__
#define __Painter_H__


#include "Entity.h"
#include "j1Timer.h"
class Painter : public Entity
{
public:

	Painter(iPoint tile, int damage, j1Module* listener, Entity* creator = nullptr);
	~Painter();
	void ExtractPaint(float dt) override;
	void ExtractWood(float dt) override;
	void ExtractMetalScrap(float dt) override;
	void Draw(SDL_Texture* sprites) override;
	void OnCollision(Collider* c1, Collider* c2) override;

public:

private:

	bool startTimer = true;
	j1Timer Extaction_Timer;
};

#endif //__Painter_H__