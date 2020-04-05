#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include "j1Module.h"
#include "j1Render.h"

#define MAX_COLLIDERS 400

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_DEATH,
	COLLIDER_FLOOR,
	COLLIDER_PLATFORM,
	COLLIDER_CAMERASTAY,
	COLLIDER_FRUIT,
	
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	bool activeC = true;
	COLLIDER_TYPE type;

	j1Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) : rect(rectangle), type(type), callback(callback) {}

	Collider() : rect({ 0, 0, 0, 0 }), type(COLLIDER_NONE),	callback(nullptr) {}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	void SetSize(int w, int h)
	{
		rect.w = w;
		rect.h = h;
	}

	void ColliderType(COLLIDER_TYPE CollType) { type = CollType; }

	bool CheckCollision(const SDL_Rect& r) const;
};

class j1Collision : public j1Module
{
public:

	j1Collision();
	~j1Collision();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
	
	void DebugDraw();
	bool debug = false;



private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];

};

#endif // __ModuleCollision_H__
