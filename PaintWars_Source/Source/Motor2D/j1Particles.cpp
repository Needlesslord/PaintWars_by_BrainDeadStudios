#include "j1App.h"
#include <vector>

#include "j1Particles.h"

#include "j1Render.h"
#include "random.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "Entity.h"

Particles::Particles() {
	rangerParticleTexture = App->tex->Load("textures/Smoke_Texture_7x7px.png");
}

Particles::~Particles()
{}

void Particles::Update(float dt) {

	pos.x += speed.x * dt; 
	pos.y += speed.y * dt;

	Draw();
}


Particles* AddParticle(PARTICLE_TYPE type, fPoint pos, fPoint v0) {

	Particles* ret = new Particles();
	ret->particleType = type;
	ret->pos = pos;
	ret->speed = v0;
	
	ret->isAlive = true;

	return ret;
}

bool Particles::Draw() {

	if (particleType == PARTICLE_RANGER) {
		App->render->RenderQueue(10, rangerParticleTexture, pos.x, pos.y, { 0, 0, 15, 15 });
	}

	else if (particleType == PARTICLE_SLIME) {

	}

	else
		return false;
}