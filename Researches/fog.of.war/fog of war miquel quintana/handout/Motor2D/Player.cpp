#include "Player.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "Fow.h"
#include "j1Window.h"

Player::Player() : j2Entity(ENTITY_TYPE::PLAYER)
{
}

Player::~Player()
{
}

bool Player::Start()
{
	//App->win->GetWindowSize(win_width, win_height);

	entity_rect = { 0,0,32,32 };
	entity_tex = App->tex->Load("textures/pipo-balloon.png");

	// TODO 2: Create the fow entity for the player. 
	// Remember the player will be providing visibility.

	// TODO 5: Create a first sight quad (createsightquad in fow.cpp). This is gonna store the tile id's nearby to the emitting visibility entity.
	// Store the pointer at fow_entity->frontier
	// Once we have it done, fulfill the tile types with fulfillSight. This is called the Line of Sight. (LOS)
	
	return true;
}

bool Player::Update(float dt, bool do_logic)
{
	iPoint last_pos = position;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		position.y -= 1;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		position.y += 1;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		position.x -= 1;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		position.x += 1;
	
	Camera_Control(dt);

	// TODO 3: Update the state of visibility; sync this entity's visibility with it's fow_entity visibility.
	// We are doing this because the FowManager is already taking care of the fow_entity visibility, here we are just updating the entity state.

	// TODO 4: Update the fow_entity position from this position. 
	// If we don't do this, our providing visibility entity won't be synced with the sight emitted.
	

	return true;
}

bool Player::CleanUp()
{
	App->tex->UnLoad(entity_tex);
	return true;
}

void Player::Draw()
{
	App->render->Blit(entity_tex, position.x - 16, position.y -64, &entity_rect);
}

void Player::Camera_Control(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		App->render->camera.x += camera_speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		App->render->camera.x -= camera_speed;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		App->render->camera.y += camera_speed;
	}
	
	
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		App->render->camera.y -= camera_speed;
	}
}