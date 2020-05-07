#include "DummyEnemy.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "Fow.h"

DummyEnemy::DummyEnemy() : j2Entity(ENTITY_TYPE::ENEMY)
{
}

DummyEnemy::~DummyEnemy()
{
}

bool DummyEnemy::Start()
{
	entity_rect = {0,0,32,32};
	entity_tex = App->tex->Load("textures/pipo-airship2.png");

	// TODO 2: Create a new fow_entity that will be linked to this entity. (search for a method in fow.cpp)
	// keep the pointer of the new entity at the fow_entity pointer. 
	fow_entity = App->fow->CreateFOWEntity(position,true);

	return true;
}

bool DummyEnemy::Update(float dt, bool do_logic)
{
	// TODO 3: Update the state of visibility; sync this entity's visibility with it's fow_entity visibility.
	// We are doing this because the FowManager is already taking care of the fow_entity visibility, here we are just updating the entity state.

	visible = fow_entity->is_visible;

	return true;
}

bool DummyEnemy::CleanUp()
{
	App->tex->UnLoad(entity_tex);
	return true;
}

void DummyEnemy::Draw()
{
	App->render->Blit(entity_tex, position.x -16, position.y -64, &entity_rect);
}
