#pragma once
#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include<vector>
#include "j1Module.h"
#include "Particle.h"
#include "ParticleSystem.h"

class SDL_Texture;
enum class PARTICLE_TYPES;

class j1ParticleManager : public j1Module
{
public:

	j1ParticleManager();
	~j1ParticleManager();

	bool		Start();
	bool		Update(float dt);
	bool		CleanUp();

	bool		updateIndex();
	void		changeIndex(int newIndex);
	int			getIndex();

	ParticleSystem* createSystem(PARTICLE_TYPES type, p2Point<float> location, float timer);
	void		deleteSystem(ParticleSystem* system_);
	void		quickDeleteSystem(std::vector<ParticleSystem*>::iterator& entity);
	void		deleteAllSystems();

	void		deleteAllParticles();

	Particle*	AddParticle(PARTICLE_TYPES type, fPoint location, fPoint velocity);


	std::vector<Particle> particlePool;
	std::vector<ParticleSystem*> systems;
	SDL_Texture* smokeTexture;
	SDL_Texture* cloudTexture;
	SDL_Texture* fireTexture;
	SDL_Texture* explosionTexture;
	SDL_Texture* dustTexture;

	SDL_Texture* rangerParticleTexture = nullptr;
	SDL_Texture* slimeParticleTexture = nullptr;

private:

	int	 Index;
	bool CloudsActive;
	float CloudTimer;
	int cloudVariableY;
	int cloudVariableX;

};

#endif // __PARTICLESYSTEM_H__