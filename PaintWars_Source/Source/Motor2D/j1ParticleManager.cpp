#include "j1ParticleManager.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "random.h"
#include "j1Window.h"
#include "j1Textures.h"

#define CLOUD_MAX_TIME 3

j1ParticleManager::j1ParticleManager()
{
	particlePool.resize(1500);	// Allocate dynamicaly a lot of particles for later use
	Index = 0;
	CloudsActive = true;
	CloudTimer = CLOUD_MAX_TIME;
	cloudVariableX = 0;
	cloudVariableY = 0;
	smokeTexture = nullptr;
}

j1ParticleManager::~j1ParticleManager()
{
	deleteAllParticles();
	deleteAllSystems();
}

bool j1ParticleManager::Start()
{
	smokeTexture = App->tex->Load("textures/Smoke_Texture_7x7px.png");
	cloudTexture = App->tex->Load("textures/particle_cloud.png");
	//fireTexture = App->tex->Load("textures/Fire_Texture_7x7px.png");
	//explosionTexture = App->tex->Load("textures/Explosion_Texture_2_7x7px.png");
	//dustTexture = App->tex->Load("textures/Dust_Texture_25x20px.png");

	return true;
}

bool j1ParticleManager::Update(float dt)
{
	////////////////////PARTICLES UPDATE

	int counter = 0;

	while (counter != particlePool.size())
	{
		vector<Particle>::iterator particle = particlePool.begin();

		particle += counter;
		for (; particle != particlePool.end(); particle++)
		{
			if (particle->active)
				particle->Update(dt);

			counter++;
		}
	}

	////////////////////PARTICLE SYSTEMS UPDATE

	counter = 0;

	while (counter != systems.size())
	{
		vector<ParticleSystem*>::iterator system = systems.begin();

		system += counter;
		for (; system != systems.end(); system++)
		{
			if ((*system)->toDelete == true)
			{
				quickDeleteSystem(system);
				break;
			}
			else
				(*system)->Update(dt);

			counter++;
		}
	}

	//////////////////////DEBUG ("O" TO ACTIVATE/DEACTIVATE CLOUDS & "P" TO START AN EXPLOSION AT THE MOUSE COORDS)

	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	{
		if (CloudsActive == false)
			CloudsActive = true;
		else
		{
			CloudsActive = false;
			CloudTimer = CLOUD_MAX_TIME;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		fPoint test;
		test = App->input->GetMouseWorldPosition();
		//test.x -= App->render->camera.x / App->win->GetScale();
		//test.y -= App->render->camera.y / App->win->GetScale();

		App->pmanager->createSystem(PARTICLE_TYPES::SMOKE, { (float)test.x, (float)test.y }, 0);
		//LOG("CLOUD CREATED AT  X:%.2f Y:%.2f", (float)test.x, (float)test.y);
	}

	///////////////////////CLOUDS SPAWN PARAMETERS

	if (CloudsActive == true)
	{
		CloudTimer -= dt;

		if (CloudTimer <= 0)
		{
			cloudVariableY = (3200 * (2 * (Random::Randomize() - 0.5)));

			if (cloudVariableY < 0)
				cloudVariableX = -cloudVariableY;
			else
				cloudVariableX = cloudVariableY;

			iPoint pos = { 6300 - cloudVariableX, 3200 + cloudVariableY };
			App->render->ScreenToWorld(pos.x, pos.y);

			fPoint fpos = { (float)pos.x,  (float)pos.y };
			App->pmanager->createSystem(PARTICLE_TYPES::CLOUD, fpos, 300);
			//LOG("CLOUD CREATED AT  X:%.2f Y:%.2f", fpos.x, fpos.y);

			CloudTimer = CLOUD_MAX_TIME;
		}

	}

	return true;
}

bool j1ParticleManager::CleanUp()
{
	particlePool.clear();
	return true;
}

void j1ParticleManager::deleteAllParticles()
{
	while (particlePool.size() != 0)
	{
		particlePool.erase(particlePool.begin(), particlePool.begin() + 1);
		particlePool.shrink_to_fit();
	}
}

///////////////////ParticleSystems methods

ParticleSystem* j1ParticleManager::createSystem(PARTICLE_TYPES type, p2Point<float> location, float timer)
{
	ParticleSystem* newSystem = new ParticleSystem(type, location, Index, timer);
	systems.push_back(newSystem);
	return newSystem;
}

void j1ParticleManager::deleteSystem(ParticleSystem* system_)
{
	if (systems.size() != 0)
		for (auto system = systems.begin(); system != systems.end(); system++)
		{
			if ((*system) == system_)
			{
				delete (*system);
				systems.erase(system, system + 1);
				systems.shrink_to_fit();
				break;
			}
		}
}

void j1ParticleManager::quickDeleteSystem(std::vector<ParticleSystem*>::iterator& system)
{
	delete (*system);
	systems.erase(system, system + 1);
	if (systems.size() <= systems.capacity() / 2)
		systems.shrink_to_fit();
}


void j1ParticleManager::deleteAllSystems()
{
	while (systems.size() != 0)
	{
		delete (*systems.begin());
		systems.erase(systems.begin(), systems.begin() + 1);
		systems.shrink_to_fit();
	}
}

////////////////////Index Methods
bool j1ParticleManager::updateIndex()
{
	bool ret = true;
	int newIndex = Index;

	for (int counter = 0; particlePool[newIndex].active != false; counter++)
	{
		newIndex++;

		if (newIndex == 1499) //in case we arrive to the particle number 1499(the last one), we go back to the beggining to check if there are any particles free.
			newIndex = 0;

		if (counter == 1500)
		{
			LOG("The unexpected happened. We ran out of particles");
			ret = false;
			break;
		}
	}

	Index = newIndex;
	//LOG("New Index: %d", Index);
	return ret;
}

int j1ParticleManager::getIndex()
{
	return Index;
}

void j1ParticleManager::changeIndex(int newIndex)
{
	Index = newIndex;
}
