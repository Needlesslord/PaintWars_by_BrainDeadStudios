#ifndef __j1Entities_H__
#define __j1Entities_H__

#include "p2Point.h"
#include "p2Log.h"
#include "j1App.h"
#include "SDL/include/SDL.h"

#include "j1Render.h"
#include "Color.h"

struct SDL_Texture;

enum class Orientation
{
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST
};

enum class Entity_Type
{
	BOAT,
	BOATHOUSE,
	NONE
};

struct storage
{
	int wood;
	int cotton;
	int stone;
	int metal;

	int maxweight;
};
///////////////////////////////////////////////CLASSES//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Entity
{
public:

	Entity() { selected = false; to_delete = false; }

	virtual void Update(float dt) {};
	virtual void CleanUp() {};

	bool to_delete;

	void Damage(int damage, Entity* target)
	{
		target->health -= damage;
		if (target->health < 0)
			target->health = 0;
	}

	int team;

	int health;
	int max_health;
	iPoint position;
	Entity_Type type;
	bool selected;
	int level;
	storage load;

	SDL_Rect rect; //probably will be the future current_animation
	SDL_Texture* texture;

protected:

	void  ShowHPbar(int extra_width, int height)
	{
		if (!showing_hpbar)
		{
			showing_hpbar = true;

			SDL_Rect health_rect = { rect.x - extra_width, rect.y - 20, rect.w + extra_width * 2, height };
			Color health_color(96u, 96u, 96u);

			App->render->AddBlitEvent(2, nullptr, 0, 0, health_rect, false, false, 0.0f, health_color.r, health_color.g, health_color.b, health_color.a);

			float hrw = health_rect.w;
			hrw /= max_health;
			hrw *= health;
			health_rect.w = hrw;
			health_color.SetColor(0u, 204u, 0u);

			App->render->AddBlitEvent(2, nullptr, 0, 0, health_rect, false, false, 0.0f, health_color.r, health_color.g, health_color.b, health_color.a);
		}
	}

	bool showing_hpbar;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Unit : public Entity
{
public:

	int speed;
	int range;
	Orientation looking;
	iPoint destination;

protected:

	iPoint past_frame_dest;
	//void Path_to(fPoint); Add when pathfinding is done
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Structure : public Entity
{
public:

	iPoint tile;

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Resource : public Entity
{
public:

	int amount;

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Boat : public Unit
{
public:
	Boat(int x = 0, int y = 0, int level = 1, int team = 0);
	~Boat();

	void Update(float);
	void CleanUp();

	Entity* target;

private:

	void Move();
	void SetDestination();
	void Attack();
	void FindTarget();

	Color color;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BoatHouse : public Structure
{
public:
	BoatHouse(int team = 0, iPoint tile = {0, 0});
	~BoatHouse();

	void Update(float);
	void CleanUp();

	bool placed;

	Color color;
};
#endif // __j1Entities_H__