#pragma once
#include "p2Point.h"
#include "Particle.h"

class ParticleSystem
{
public:
	ParticleSystem(PARTICLE_TYPES type, p2Point<float>, int index, float timer);
	~ParticleSystem();

	void loadSystem(); //maybe we should load each effect properties from an xml
	bool activateSystem(int index);
	void Update(float dt);
	void deactivateParticle(Particle* particle);
	void deactivateAllParticles();
	void changePosition(fPoint location);

	float timer;
	float countDown;
	bool timeActive;
	bool toDelete;

	ParticleProps systemProps;

private:
	PARTICLE_TYPES systemType;
	Particle* referencesArray[20];
	int numberOfParticles;
};