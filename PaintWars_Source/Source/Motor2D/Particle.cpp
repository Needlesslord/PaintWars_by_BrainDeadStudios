#include "j1App.h"
#include <vector>
#include "Particle.h"
#include "j1Render.h"
#include "random.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "Entity.h"

using namespace std;

Particle::Particle()
{
	active = false;
	pTexture = nullptr;
}

void Particle::Update(float dt)
{
	
	pRect.x = pLocation.x;
	pRect.y = pLocation.y;

	remainingLifetime -= pLifetimeSubstraction;

	if (remainingLifetime < 0)
	{
		loadProperties(Props);
		remainingLifetime = lifespan;
	}
	Draw();
}

void Particle::loadProperties(ParticleProps properties)
{
	pLocation = properties.Location;
	pAcceleration = properties.Acceleration;
	pVelocity = properties.Velocity;
	lifespan = properties.lifetime;
	pRect = properties.rect;
	pTexture = properties.tex;
	pType = properties.type;
	remainingLifetime = lifespan;
	pLifetimeSubstraction = properties.lifetimeSubstraction;
	Props = properties;

	if (pType == PARTICLE_TYPES::CLOUD)
		pLocation = { (pLocation.x + (float)(100 * (Random::Randomize() - 0.5))), (pLocation.y + (float)(100 * (Random::Randomize() - 0.5))) };


	if (pType == PARTICLE_TYPES::EXPLOSION)
		pVelocity = { (float)((Random::Randomize() - 0.5)), (float)((Random::Randomize()) * (-1)) };

	if (pType == PARTICLE_TYPES::SMOKE || pType == PARTICLE_TYPES::FIRE)
		pVelocity = { (float)(0.3*(Random::Randomize() - 0.5)), (float)(0.3 * (Random::Randomize() - 0.5)) };

	if (pType == PARTICLE_TYPES::DUST)
		pVelocity = { (float)(0.5 * (Random::Randomize() - 0.5)), (float)(-0.2 * (Random::Randomize())) };
}

void Particle::switchParticleState()
{
	if (active)
	{
		active = false;
	}
	else
	{
		active = true;
	}
}

bool Particle::Draw()
{
	if (pTexture != nullptr)
		App->render->RenderQueue(10, pTexture, pLocation.x, pLocation.y, { 0, 0, pRect.w, pRect.h });

	else
		App->render->RenderQueue(10, nullptr, pLocation.x, pLocation.y, pRect, false, 0.0f, 255, 130, 0, remainingLifetime);

	return true;
}