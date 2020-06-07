#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#define MAX_PARTICLE_LIFESPAN 255

#include "j1App.h"
#include "SDL/include/SDL.h"
#include <vector>
#include "p2Point.h"

class SDL_Texture;
using namespace std;

enum class PARTICLE_TYPES
{
	NONE,
	TEST,
	SMOKE,
	FIRE,
	EXPLOSION,
	WIND,
	CLOUD,
	DUST,
	CANNONBALL
};

struct ParticleProps
{
	p2Point<float>	Location = { 0,0 };
	p2Point<float>	Velocity = { 0,0 };
	p2Point<float>	Acceleration = { 0,0 };
	SDL_Rect		rect = { 0,0,20,20 };
	SDL_Texture* tex = nullptr;
	PARTICLE_TYPES	type = PARTICLE_TYPES::TEST;
	float			lifetime = 255;
	float			lifetimeSubstraction = 0;
	float			AwakeningDelay = 0;
	p2Point<float>	Destination = { 0,0 };
};

class Particle
{
public:

	Particle();

	void			Update(float dt);
	bool			Draw();
	void			switchParticleState();
	void			loadProperties(ParticleProps properties);

	SDL_Rect		pRect;
	p2Point<float>	pLocation;
	p2Point<float>	pVelocity;
	p2Point<float>	pAcceleration;
	PARTICLE_TYPES	pType;
	SDL_Texture* pTexture;
	fPoint			pDestination;

	float			lifespan;
	float			remainingLifetime;
	float			pLifetimeSubstraction;
	bool			active;
	bool			awake;
	ParticleProps	Props;
};

#endif