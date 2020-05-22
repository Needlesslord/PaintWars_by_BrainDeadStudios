#include "j1App.h"
#include <vector>

#include "j1Particles.h"

#include "j1Render.h"
#include "random.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "Entity.h"

Particles::Particles() {
	rangerParticleTexture = App->tex->Load("textures/particle_ranger.png");
	slimeParticleTexture = App->tex->Load("textures/particle_slime.png");
}

Particles::~Particles()
{}

bool Particles::Update(float dt, fPoint targetPos) {

	if (pos.x + 3.5 > targetPos.x + targetSize.x / 2) {

		if (speed.x > 0)
			speed.x *= (-1);
	}
	if (pos.y + 3.5 > targetPos.y + targetSize.y / 2) {

		if (speed.y > 0)
			speed.y *= (-1);
	}

	pos.x += speed.x * dt; 
	pos.y += speed.y * dt;

	// Going Right
	if (speed.x > 0) {

		// Going Up & Right
		if (speed.y < 0) {

			if (pos.x > targetPos.x && pos.y < targetPos.y) {
				isAlive = false;
				return false;
			}
		}

		// Going Down & Right
		else if (speed.y > 0) {

			if (pos.x > targetPos.x && pos.y > targetPos.y) {
				isAlive = false;
				return false;
			}
		}

		// Straight Right
		else if (speed.y = 0) {

			if (pos.x > targetPos.x) {
				isAlive = false;
				return false;
			}
		}
	}

	// Going Left
	else if (speed.x < 0) {

		// Going Up & Left
		if (speed.y < 0) {

			if (pos.x < targetPos.x && pos.y < targetPos.y) {
				isAlive = false;
				return false;
			}
		}

		// Going Down & Left
		else if (speed.y > 0) {

			if (pos.x < targetPos.x && pos.y > targetPos.y) {
				isAlive = false;
				return false;
			}
		}

		// Straight Left
		else if (speed.y = 0) {

			if (pos.x < targetPos.x) {
				isAlive = false;
				return false;
			}
		}
	}
	
	// Not moving
	else if (speed.x = 0) {

		// Going Up
		if (speed.y < 0) {

			if (pos.y < targetPos.y) {
				isAlive = false;
				return false;
			}
		}

		// Going Down
		else if (speed.y > 0) {

			if (pos.y > targetPos.y) {
				isAlive = false;
				return false;
			}
		}
	}
	
	Draw();

	return true;
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
		App->render->RenderQueue(10, slimeParticleTexture, pos.x, pos.y, { 0, 0, 15, 15 });
	}

	else
		return false;
}