#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "p2Log.h"
#include "j1Player.h"

j1Collision::j1Collision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_DEATH] = false;
	matrix[COLLIDER_WALL][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLATFORM] = false;
	matrix[COLLIDER_WALL][COLLIDER_CAMERASTAY] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_DEATH] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLATFORM] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_CAMERASTAY] = true;

	matrix[COLLIDER_DEATH][COLLIDER_WALL] = false;
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DEATH][COLLIDER_DEATH] = false;
	matrix[COLLIDER_DEATH][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_DEATH][COLLIDER_PLATFORM] = false;
	matrix[COLLIDER_DEATH][COLLIDER_CAMERASTAY] = false;

	matrix[COLLIDER_FLOOR][COLLIDER_WALL] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_DEATH] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLATFORM] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_CAMERASTAY] = false;

	matrix[COLLIDER_PLATFORM][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLATFORM][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PLATFORM][COLLIDER_DEATH] = false;
	matrix[COLLIDER_PLATFORM][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_PLATFORM][COLLIDER_PLATFORM] = false;
	matrix[COLLIDER_PLATFORM][COLLIDER_CAMERASTAY] = false;
	
}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

bool j1Collision::Update(float dt)
{
	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	DebugDraw();

	return true;
}

bool j1Collision::PostUpdate(float dt)
{
	DebugDraw();

	return true;
}

void j1Collision::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		debug = !debug;
	}

	if (debug == false)
		return;

	Uint8 alpha = 180;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		if (colliders[i]->activeC){

			switch (colliders[i]->type)
			{
			case COLLIDER_NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case COLLIDER_WALL: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case COLLIDER_PLAYER: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case COLLIDER_DEATH: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case COLLIDER_FRUIT: // blue
				App->render->DrawQuad(colliders[i]->rect, 65, 105, 225, alpha);
				break;
			case COLLIDER_PLATFORM: // yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case COLLIDER_CAMERASTAY: // color
				App->render->DrawQuad(colliders[i]->rect, 195, 0, 254, alpha);
				break;

			}
		}
	}
}

bool j1Collision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	
	return (rect.x < r.x + r.w && rect.x + rect.w > r.x && rect.y < r.y + r.h && rect.h + rect.y > r.y);

}