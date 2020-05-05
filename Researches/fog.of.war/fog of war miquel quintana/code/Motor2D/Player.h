#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j2Entity.h"
#include "p2Point.h"

class Player : public j2Entity
{
public:
	Player();
	~Player();

	bool Start();

	bool Update(float dt, bool do_logic);

	bool CleanUp();

	void Draw();

private:

	void Camera_Control(float dt);

	int camera_speed = 2;
	int camera_offset = 10;
};

#endif
