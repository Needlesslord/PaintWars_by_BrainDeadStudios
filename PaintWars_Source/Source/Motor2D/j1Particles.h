#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "p2Point.h"
#include <list>

#define MAX_ACTIVE_PARTICLES 30

struct SDL_Texture;

enum PARTICLE_TYPE {

	PARTICLE_RANGER,
	PARTICLE_SLIME
};

class Particles
{
public:

	Particles();
	~Particles();
	
	bool Update(float dt, fPoint targetPos);
	bool Draw();

private:

public:

	fPoint pos;
	fPoint speed;
	PARTICLE_TYPE particleType;
	bool isAlive;

	fPoint target;
	fPoint targetSize;

private:

	SDL_Texture* rangerParticleTexture = nullptr;
	SDL_Texture* slimeParticleTexture = nullptr;

};

Particles* AddParticle(PARTICLE_TYPE type, fPoint pos, fPoint v0);

#endif // __MODULEPARTICLES_H__
