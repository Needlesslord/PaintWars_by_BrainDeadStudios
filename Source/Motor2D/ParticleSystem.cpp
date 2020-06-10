#include "ParticleSystem.h"
#include "j1ParticleManager.h"
#include "j1App.h"
#include "j1Textures.h"
#include "random.h"
#include "j1Render.h"
#include "p2Log.h"

#define CANNON_BALLS_SPEED 30

ParticleSystem::ParticleSystem(PARTICLE_TYPES _type, p2Point<float> location, int index, float _timer)
{
	systemProps.Location = location;
	systemType = _type;
	timer = _timer;
	toDelete = false;

	awakeningCounter = 0;
	allParticlesAwake = false;

	if (_timer == 0)
		timeActive = false;
	else
		timeActive = true;

	loadSystem();
	activateSystem(index);
}

ParticleSystem::~ParticleSystem()
{
	deactivateAllParticles();
}

void ParticleSystem::loadSystem()
{
	systemProps.type = systemType;
	float random = rand() % -2 - 1;

	if (systemProps.type == PARTICLE_TYPES::CLOUD)
	{
		systemProps.Velocity = { -2.0, 0 };
		systemProps.lifetime = 60;
		systemProps.Acceleration = { 0, 0 };
		systemProps.rect = { 0, 0, 200, 121 };
		systemProps.lifetimeSubstraction = 0;
		systemProps.tex = App->pmanager->cloudTexture;
		numberOfParticles = 1;
	}
	else if (systemProps.type == PARTICLE_TYPES::SMOKE)
	{
		systemProps.lifetime = 255;
		systemProps.Acceleration = { 0, (-0.0015f) };
		systemProps.rect = { 0, 0, 7, 7 };
		systemProps.lifetimeSubstraction = 0.5;
		systemProps.tex = App->pmanager->smokeTexture;
		numberOfParticles = 6;
		systemProps.AwakeningDelay = 1;

	}
	else if (systemProps.type == PARTICLE_TYPES::FIRE)
	{
		systemProps.lifetime = 255;
		systemProps.Acceleration = { 0, (-0.001f) };
		systemProps.rect = { 0, 0, 7, 7 };
		systemProps.lifetimeSubstraction = 1.;
		systemProps.tex = App->pmanager->fireTexture;
		numberOfParticles = 6;
		systemProps.AwakeningDelay = 1;
	}
	else if (systemProps.type == PARTICLE_TYPES::EXPLOSION)
	{
		systemProps.lifetime = 255;
		systemProps.Acceleration = { 0, 0.01 };
		systemProps.rect = { 0, 0, 7, 7 };
		systemProps.lifetimeSubstraction = 3;
		systemProps.tex = App->pmanager->explosionTexture;
		numberOfParticles = 20;
	}
	else if (systemProps.type == PARTICLE_TYPES::DUST)
	{
		systemProps.lifetime = 255;
		systemProps.Acceleration = { 0, -0.0005 };
		systemProps.rect = { 0, 0, 25, 20 };
		systemProps.lifetimeSubstraction = 1;
		systemProps.tex = App->pmanager->dustTexture;
		numberOfParticles = 1;
	}
	else if (systemProps.type == PARTICLE_TYPES::CANNONBALL)
	{
		systemProps.lifetime = 255;
		systemProps.Acceleration = { 0, 0 };
		systemProps.rect = { 0, 0, 7, 7 };
		systemProps.lifetimeSubstraction = 0;
		systemProps.tex = App->pmanager->projectileTexture;
		numberOfParticles = 50;
	}
	else if (systemProps.type == PARTICLE_TYPES::SNOW)
	{
		systemProps.Velocity = { -5, 2 };
		systemProps.lifetime = 120;
		systemProps.Acceleration = { 0, 0 };
		systemProps.rect = { 0, 0, 7, 7 };
		systemProps.lifetimeSubstraction = 0;
		systemProps.tex = App->pmanager->smokeTexture;
		numberOfParticles = 40;
	}
	else
	{
		systemProps.lifetime = 255;
		systemProps.Acceleration = { 0, 0.01 };
		systemProps.rect = { 0, 0, 7, 7 };
		systemProps.lifetimeSubstraction = 3;
	}
}

bool ParticleSystem::activateSystem(int index)
{
	Particle* pReference = nullptr;
	int counter = 0;
	int newIndex = index;

	while (counter < numberOfParticles)
	{
		if (App->pmanager->particlePool[newIndex].active == true || newIndex >= 1499)
		{
			if (App->pmanager->updateIndex())
				newIndex = App->pmanager->getIndex();
		}

		pReference = &(App->pmanager->particlePool[newIndex]);
		pReference->loadProperties(systemProps);
		pReference->switchParticleState();

		if (systemProps.AwakeningDelay == 0 && systemType != PARTICLE_TYPES::CANNONBALL)
		{
			pReference->awake = true;
		}

		*(referencesArray + counter) = pReference; //asigno la referencia de la particula cargada al lugar que le corresponde de 

		newIndex++;
		counter++;
	}

	if (systemProps.AwakeningDelay == 0)
	{
		allParticlesAwake = true;
	}

	App->pmanager->updateIndex();

	return true;
}

void ParticleSystem::Update(float dt)
{
	if (systemType != PARTICLE_TYPES::CANNONBALL)
	{
		if (timeActive == true)
		{
			timer -= dt;

			if (timer <= 0)
			{
				toDelete = true;
			}
		}

		if (allParticlesAwake != true && systemProps.AwakeningDelay != 0)
		{
			systemProps.AwakeningDelay -= dt;

			if (systemProps.AwakeningDelay <= 0)
			{
				if (awakeningCounter < numberOfParticles)
				{
					Particle* particle = *(referencesArray + awakeningCounter);
					particle->awake = true;
					//LOG("particle active");

					awakeningCounter++;
				}
				else
					allParticlesAwake = true;

				systemProps.AwakeningDelay = 1;
			}
		}
	}
	else
	{
		Particle* particle = nullptr;
		for (int i = 0; i < numberOfParticles; i++)
		{
			particle = *(referencesArray + i);
			if (particle->awake == true)
			{
				if (particle->pVelocity.x >= 0) //Positive x destination
				{
					if (particle->pLocation.x >= particle->pDestination.x) //check if the x position is bigger than the destination
					{
						if (particle->pVelocity.y >= 0) //Positive y destination
						{
							if (particle->pLocation.y >= particle->pDestination.y) //check if the y position is bigger than the destination
							{
								particle->awake = false;
							}
						}
						else //negative y destination
						{
							if (particle->pLocation.y < particle->pDestination.y) //check if the y position is smaller than the destination
							{
								particle->awake = false;
							}
						}
					}
				}
				else //negative x destination
				{
					if (particle->pLocation.x < particle->pDestination.x) //check if the x position is smaller than the destination
					{
						if (particle->pVelocity.y >= 0) //Positive y destination
						{
							if (particle->pLocation.y >= particle->pDestination.y) //check if the y position is bigger than the destination
							{
								particle->awake = false;
							}
						}
						else //negative y destination
						{
							if (particle->pLocation.y < particle->pDestination.y) //check if the y position is smaller than the destination
							{
								particle->awake = false;
							}
						}
					}
				}
			}
		}
	}
}

void ParticleSystem::deactivateAllParticles()
{
	Particle* particle = nullptr;
	for (int i = 0; i < numberOfParticles; i++)
	{
		particle = *(referencesArray + i);
		particle->switchParticleState();
	}
}

void ParticleSystem::changePosition(fPoint location)
{
	Particle* particle = nullptr;
	for (int i = 0; i < numberOfParticles; i++)
	{
		particle = *(referencesArray + i);
		particle->Props.Location = location;
	}
}

void ParticleSystem::shootCannonBall(fPoint pos1, fPoint pos2)
{
	if (systemType == PARTICLE_TYPES::CANNONBALL)
	{
		Particle* particle = nullptr;
		for (int i = 0; i < numberOfParticles; i++)
		{
			particle = *(referencesArray + i);

			if (particle->awake == false)
			{
				particle->pLocation = pos1;
				particle->pDestination = pos2;
				particle->pVelocity = { (float)((pos2.x - pos1.x) / CANNON_BALLS_SPEED), (float)((pos2.y - pos1.y) / CANNON_BALLS_SPEED) };
				particle->awake = true;
				//LOG("cannon ball number:%d shoot", i);
				break;
			}
		}
	}
}