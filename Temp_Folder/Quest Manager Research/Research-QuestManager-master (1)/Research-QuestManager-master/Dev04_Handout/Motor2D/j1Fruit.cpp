#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Fruit.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Collision.h"
#include "j1Scene.h"
#include <time.h>
#include <list>


j1Fruit::j1Fruit() : j1Module()
{}

j1Fruit::~j1Fruit()
{}

j1Fruit bowl[MAX_FRUITS];

bool j1Fruit::Start()
{
	srand(time(NULL));

	for (int i = 0; i < MAX_FRUITS; i++)
	{
		bowl[i].type = static_cast<f_type>(rand() % NONE);
		bowl[i].f_pos.x = ((rand() % 22) * 32) + 34;
		bowl[i].f_pos.y = ((rand() % 22) * 32) + 34;

		bowl[i].f_hitbox = { bowl[i].f_pos.x, bowl[i].f_pos.y, 28, 28 };
		
	}
	
	return true;
}

bool j1Fruit::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		LOG("debug");
	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		Restart();
	}
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		c_points++;
		LOG("CHERRY");
	}
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		b_points++;
		LOG("BANANA");
	}
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		o_points++;
		LOG("ORANGE");
	}
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		w_points++;
		LOG("WATERMELON");
	}
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		m_points++;
		LOG("MANGO");
	}


	CheckCollision();
	

	return true;
}

bool j1Fruit::Update(float dt)
{
	for (int i = 0; i < MAX_FRUITS; i++)
	{
		switch (bowl[i].type)
		{
		case CHERRY:
			App->render->DrawQuad(bowl[i].f_hitbox, 150, 9, 21, 255);
			break;
		case BANANA:
			App->render->DrawQuad(bowl[i].f_hitbox, 247, 225, 79, 255);
			break;
		case ORANGE:
			App->render->DrawQuad(bowl[i].f_hitbox, 245, 105, 24, 255);
			break;
		case WATERMELON:
			App->render->DrawQuad(bowl[i].f_hitbox, 235, 14, 14, 255);
			break;
		case MANGO:
			App->render->DrawQuad(bowl[i].f_hitbox, 255, 215, 0, 255);
			break;
		}
	}
	
	UpdateScoreboard();

	return true;
}

bool j1Fruit::PostUpdate()
{
	return true;
}

bool j1Fruit::CleanUp()
{
	return true;
}

void j1Fruit::Spawn() {

	type = static_cast<f_type>(rand() % NONE);

	f_pos.x = ((rand() % 22) * 32) + 34;
	f_pos.y = ((rand() % 22) * 32) + 34;

	f_hitbox = { f_pos.x, f_pos.y, 28, 28 };

	
}

void j1Fruit::Eaten() {

	//App->player->score += points;
	Spawn();
}

//updates the checkboard depending on how many fruits of each type you have and triggers and event when you complete a whole set 
void j1Fruit::UpdateScoreboard()
{
	//cherry
	switch (c_points)
	{
	case 0:
		break;
	case 1:
		App->render->DrawQuad(c1, 150, 9, 21, 255);
		break;
	case 2:
		App->render->DrawQuad(c1, 150, 9, 21, 255);
		App->render->DrawQuad(c2, 150, 9, 21, 255);
		break;
	case 3:
		App->render->DrawQuad(c1, 150, 9, 21, 255);
		App->render->DrawQuad(c2, 150, 9, 21, 255);
		App->render->DrawQuad(c3, 150, 9, 21, 255);
		break;
	case 4:
		App->render->DrawQuad(c1, 150, 9, 21, 255);
		App->render->DrawQuad(c2, 150, 9, 21, 255);
		App->render->DrawQuad(c3, 150, 9, 21, 255);
		App->render->DrawQuad(c4, 150, 9, 21, 255);
		break;
	case 5:
		App->render->DrawQuad(c1, 150, 9, 21, 200);
		App->render->DrawQuad(c2, 150, 9, 21, 200);
		App->render->DrawQuad(c3, 150, 9, 21, 200);
		App->render->DrawQuad(c4, 150, 9, 21, 200);
		App->render->DrawQuad(c5, 150, 9, 21, 200);
		App->render->DrawQuad(c_check, 0, 255, 0, 255);
		App->scene->cherry = true;
		break;
	default:
		App->render->DrawQuad(c1, 150, 9, 21, 200);
		App->render->DrawQuad(c2, 150, 9, 21, 200);
		App->render->DrawQuad(c3, 150, 9, 21, 200);
		App->render->DrawQuad(c4, 150, 9, 21, 200);
		App->render->DrawQuad(c5, 150, 9, 21, 200);
		App->render->DrawQuad(c_check, 0, 255, 0, 255);
		break;
	}

	//banana
	switch (b_points)
	{
	case 0:
		break;
	case 1:
		App->render->DrawQuad(b1, 247, 225, 79, 255);
		break;
	case 2:
		App->render->DrawQuad(b1, 247, 225, 79, 255);
		App->render->DrawQuad(b2, 247, 225, 79, 255);
		break;
	case 3:
		App->render->DrawQuad(b1, 247, 225, 79, 255);
		App->render->DrawQuad(b2, 247, 225, 79, 255);
		App->render->DrawQuad(b3, 247, 225, 79, 255);
		break;
	case 4:
		App->render->DrawQuad(b1, 247, 225, 79, 255);
		App->render->DrawQuad(b2, 247, 225, 79, 255);
		App->render->DrawQuad(b3, 247, 225, 79, 255);
		App->render->DrawQuad(b4, 247, 225, 79, 255);
		break;
	case 5:
		App->render->DrawQuad(b1, 247, 225, 79, 200);
		App->render->DrawQuad(b2, 247, 225, 79, 200);
		App->render->DrawQuad(b3, 247, 225, 79, 200);
		App->render->DrawQuad(b4, 247, 225, 79, 200);
		App->render->DrawQuad(b5, 247, 225, 79, 200);
		App->render->DrawQuad(b_check, 0, 255, 0, 255);
		App->scene->banana = true;
		break;
	default:
		App->render->DrawQuad(b1, 247, 225, 79, 200);
		App->render->DrawQuad(b2, 247, 225, 79, 200);
		App->render->DrawQuad(b3, 247, 225, 79, 200);
		App->render->DrawQuad(b4, 247, 225, 79, 200);
		App->render->DrawQuad(b5, 247, 225, 79, 200);
		App->render->DrawQuad(b_check, 0, 255, 0, 255);
		break;
	}

	//orange
	switch (o_points)
	{
	case 0:
		break;
	case 1:
		App->render->DrawQuad(o1, 245, 105, 24, 255);
		break;
	case 2:
		App->render->DrawQuad(o1, 245, 105, 24, 255);
		App->render->DrawQuad(o2, 245, 105, 24, 255);
		break;
	case 3:
		App->render->DrawQuad(o1, 245, 105, 24, 255);
		App->render->DrawQuad(o2, 245, 105, 24, 255);
		App->render->DrawQuad(o3, 245, 105, 24, 255);
		break;
	case 4:
		App->render->DrawQuad(o1, 245, 105, 24, 255);
		App->render->DrawQuad(o2, 245, 105, 24, 255);
		App->render->DrawQuad(o3, 245, 105, 24, 255);
		App->render->DrawQuad(o4, 245, 105, 24, 255);
		break;
	case 5:
		App->render->DrawQuad(o1, 245, 105, 24, 200);
		App->render->DrawQuad(o2, 245, 105, 24, 200);
		App->render->DrawQuad(o3, 245, 105, 24, 200);
		App->render->DrawQuad(o4, 245, 105, 24, 200);
		App->render->DrawQuad(o5, 245, 105, 24, 200);
		App->render->DrawQuad(o_check, 0, 255, 0, 255);
		App->scene->orange = true;
		break;
	default:
		App->render->DrawQuad(o1, 245, 105, 24, 200);
		App->render->DrawQuad(o2, 245, 105, 24, 200);
		App->render->DrawQuad(o3, 245, 105, 24, 200);
		App->render->DrawQuad(o4, 245, 105, 24, 200);
		App->render->DrawQuad(o5, 245, 105, 24, 200);
		App->render->DrawQuad(o_check, 0, 255, 0, 255);
		break;
	}

	//watermelon
	switch (w_points)
	{
	case 0:
		break;
	case 1:
		App->render->DrawQuad(w1, 235, 14, 14, 255);
		break;
	case 2:
		App->render->DrawQuad(w1, 235, 14, 14, 255);
		App->render->DrawQuad(w2, 235, 14, 14, 255);
		break;
	case 3:
		App->render->DrawQuad(w1, 235, 14, 14, 255);
		App->render->DrawQuad(w2, 235, 14, 14, 255);
		App->render->DrawQuad(w3, 235, 14, 14, 255);
		break;
	case 4:
		App->render->DrawQuad(w1, 235, 14, 14, 255);
		App->render->DrawQuad(w2, 235, 14, 14, 255);
		App->render->DrawQuad(w3, 235, 14, 14, 255);
		App->render->DrawQuad(w4, 235, 14, 14, 255);
		break;
	case 5:
		App->render->DrawQuad(w1, 235, 14, 14, 200);
		App->render->DrawQuad(w2, 235, 14, 14, 200);
		App->render->DrawQuad(w3, 235, 14, 14, 200);
		App->render->DrawQuad(w4, 235, 14, 14, 200);
		App->render->DrawQuad(w5, 235, 14, 14, 200);
		App->render->DrawQuad(w_check, 0, 255, 0, 255);
		App->scene->watermelon = true;
		break;
	default:
		App->render->DrawQuad(w1, 235, 14, 14, 200);
		App->render->DrawQuad(w2, 235, 14, 14, 200);
		App->render->DrawQuad(w3, 235, 14, 14, 200);
		App->render->DrawQuad(w4, 235, 14, 14, 200);
		App->render->DrawQuad(w5, 235, 14, 14, 200);
		App->render->DrawQuad(w_check, 0, 255, 0, 255);
		break;
	}

	//mango
	switch (m_points)
	{
	case 0:
		break;
	case 1:
		App->render->DrawQuad(m1, 255, 215, 0, 255);
		break;
	case 2:
		App->render->DrawQuad(m1, 255, 215, 0, 255);
		App->render->DrawQuad(m2, 255, 215, 0, 255);
		break;
	case 3:
		App->render->DrawQuad(m1, 255, 215, 0, 255);
		App->render->DrawQuad(m2, 255, 215, 0, 255);
		App->render->DrawQuad(m3, 255, 215, 0, 255);
		break;
	case 4:
		App->render->DrawQuad(m1, 255, 215, 0, 255);
		App->render->DrawQuad(m2, 255, 215, 0, 255);
		App->render->DrawQuad(m3, 255, 215, 0, 255);
		App->render->DrawQuad(m4, 255, 215, 0, 255);
		break;
	case 5:
		App->render->DrawQuad(m1, 255, 215, 0, 200);
		App->render->DrawQuad(m2, 255, 215, 0, 200);
		App->render->DrawQuad(m3, 255, 215, 0, 200);
		App->render->DrawQuad(m4, 255, 215, 0, 200);
		App->render->DrawQuad(m5, 255, 215, 0, 200);
		App->render->DrawQuad(m_check, 0, 255, 0, 255);
		App->scene->mango = true;
		break;
	default:
		App->render->DrawQuad(m1, 255, 215, 0, 200);
		App->render->DrawQuad(m2, 255, 215, 0, 200);
		App->render->DrawQuad(m3, 255, 215, 0, 200);
		App->render->DrawQuad(m4, 255, 215, 0, 200);
		App->render->DrawQuad(m5, 255, 215, 0, 200);
		App->render->DrawQuad(m_check, 0, 255, 0, 255);
		break;
	}
}

void j1Fruit::CheckCollision()
{
	for (int i = 0; i < MAX_FRUITS; i++)
	{
		if (bowl[i].f_pos == App->player->getPos())
		{
			switch (bowl[i].type)
			{
			case CHERRY:
				c_points++;
				break;
			case BANANA:
				b_points++;
				break;
			case ORANGE:
				o_points++;
				break;
			case WATERMELON:
				w_points++;
				break;
			case MANGO:
				m_points++;
				break;

			}
			bowl[i].Spawn();
		}
	}
}

void j1Fruit::Restart()
{
	c_points = 0;
	b_points = 0;
	o_points = 0;
	w_points = 0;
	m_points = 0;

	App->scene->cherry = false;
	App->scene->banana = false;
	App->scene->orange = false;
	App->scene->watermelon = false;
	App->scene->mango = false;

	LOG("RESTART");

}