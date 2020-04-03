#ifndef __Warrior_H__
#define __Warrior_H__

#include <vector>
#include "Entity.h"

class Warrior : public Entity
{
public:

	Warrior(fPoint pos, int currLife, j1Module* listener);
	~Warrior();

	void CalculateMovementLogic() override;
	void Move(float dt) override;
	void SetDestination(iPoint des) override;

public:

	iPoint destination;
	iPoint nextTile;

private:

	std::vector<iPoint>currentPath;

	bool startTimer = true;

};

#endif //__Warrior_H__