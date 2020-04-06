#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Input.h"
#include <math.h>
#include <thread>         
#include <chrono>   
#include <time.h>


j1Player::j1Player() : j1Module()
{
	name.create("player");
}

// Destructor
j1Player::~j1Player()
{}

bool j1Player::Awake(pugi::xml_node& config)
{
	bool ret = true;

	pos.x = config.child("position").attribute("x").as_int();
	pos.y = config.child("position").attribute("y").as_int();

	speed = config.child("speed").attribute("value").as_int();

	return ret;
}

bool j1Player::Start()
{
	srand(time(NULL));
	is_dead = false;
	score = 0;
	c_state = STOP;

	pos.x = ((rand() % 22) * 32) + 34;
	pos.y = ((rand() % 22) * 32) + 34;


	hitbox = { pos.x, pos.y, 28, 28 };

	return true;
}

bool j1Player::PreUpdate()
{

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		is_dead = false;
		LOG("REVIVE");

	}
	else if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)) && !(pos.y == 34))
	{
		MoveU();
	}
	else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)) && pos.y != 738)
	{
		MoveD();
	}
	else if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)) && pos.x != 34)
	{
		MoveL();
	}
	else if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)) && pos.x != 738)
	{
		MoveR();
	}

	return true;
}

bool j1Player::Update(float dt)
{

	hitbox.x = pos.x;
	hitbox.y = pos.y;

	App->render->DrawQuad(hitbox, 0, 255, 255, 255);

	//LOG("%d,%d", pos.x, pos.y);
	return true;
}

bool j1Player::PostUpdate()
{


	return true;
}

bool j1Player::CleanUp()
{
	return true;
}




void j1Player::MoveU()
{
	pos.y -= 32;

}
void j1Player::MoveD()
{
	pos.y += 32;

}
void j1Player::MoveL()
{
	pos.x -= 32;

}
void j1Player::MoveR()
{
	pos.x += 32;

}

p2Point<int> j1Player::getPos() const
{
	return pos;
}