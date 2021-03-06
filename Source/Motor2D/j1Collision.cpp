#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "Entity.h"


j1Collision::j1Collision()
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_ALLY_UNIT][COLLIDER_ALLY_UNIT] = true;
	matrix[COLLIDER_ALLY_UNIT][COLLIDER_ALLY_BUILDING] = false;

}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

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

	return true;
}

// Called before render is available
bool j1Collision::Update(float dt) {
	
	return true;
}

bool j1Collision::PostUpdate() {
	DebugDraw();

	return true;
}

void j1Collision::DebugDraw() {

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE:				// white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_ALLY_BUILDING:	// Blue
			App->render->DrawQuad(colliders[i]->rect,   0,   0, 255, alpha);
			break;
		case COLLIDER_ALLY_UNIT:		// Green
			App->render->DrawQuad(colliders[i]->rect,   0, 255,   0, alpha);
			break;
		case COLLIDER_ENEMY_BUILDING:	// Red
			App->render->DrawQuad(colliders[i]->rect, 255,   0,   0, alpha);
			break;
		case COLLIDER_ENEMY_UNIT:		// Red
			App->render->DrawQuad(colliders[i]->rect, 255,   0,   0, alpha);
			break;
		case COLLIDER_NEUTRAL:			// Grey
			App->render->DrawQuad(colliders[i]->rect, 192, 192, 192, alpha);
			break;
		case COLLIDER_UI:
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha, true, true, false);
			break;
		}
	}
}

// Called before quitting
bool j1Collision::CleanUp() {

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

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Entity* entity, j1Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, entity, callback);
			break;
		}
	}

	return ret;
}


// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w && rect.x + rect.w > r.x && rect.y < r.y + r.h && rect.h + rect.y > r.y);
}
