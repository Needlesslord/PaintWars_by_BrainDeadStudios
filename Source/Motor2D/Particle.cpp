#include "j1App.h"
#include <vector>
#include "Particle.h"
#include "j1Render.h"
#include "random.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1SceneManager.h"

using namespace std;

Particle::Particle()
{
	awake = false;
	active = false;
	pTexture = nullptr;
}

void Particle::Update(float dt)
{
	pVelocity += pAcceleration;
	pLocation += pVelocity;

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
	pDestination = properties.Destination;
	Props = properties;

	if (pType == PARTICLE_TYPES::CLOUD)
		pLocation = { (pLocation.x + (float)(100 * (Random::Randomize() - 0.5))), (pLocation.y + (float)(100 * (Random::Randomize() - 0.5))) };

	if (pType == PARTICLE_TYPES::EXPLOSION)
		pVelocity = { (float)((Random::Randomize() - 0.5)), (float)((Random::Randomize()) * (-1)) };

	if (pType == PARTICLE_TYPES::SMOKE || pType == PARTICLE_TYPES::FIRE)
		pVelocity = { (float)(0.3 * (Random::Randomize() - 0.5)), (float)(0.3 * (Random::Randomize() - 0.5)) };

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
	//if (App->scenes->In_Main_Menu == false)
	//{
		if (pTexture != nullptr)
			App->render->RenderQueue(2, pTexture, pLocation.x, pLocation.y + 16, { 0, 0, pRect.w, pRect.h }, false, 0.0f, 0, 0, 0, remainingLifetime);

		else
			App->render->RenderQueue(2, nullptr, pLocation.x, pLocation.y, pRect, false, 0.0f, 255, 130, 0, remainingLifetime);

	//}

	return true;
}